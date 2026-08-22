#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmark.h>
#include <tcl.h>

typedef struct {
    char base_template[256];
    char page_name[256];
    const char *markdown_body;
} PageMeta;

/* Parse Frontmatter header delimited by '---' */
static PageMeta parse_frontmatter(char *input) {
    PageMeta meta;
    char *fm_start, *fm_end, *cursor;

    memset(&meta, 0, sizeof(PageMeta));
    strcpy(meta.page_name, "PureDarwin");

    if (strncmp(input, "---", 3) != 0) {
        meta.markdown_body = input;
        return meta;
    }

    fm_start = input + 3;
    while (*fm_start == '\r' || *fm_start == '\n') fm_start++;

    fm_end = strstr(fm_start, "---");
    if (!fm_end) {
        meta.markdown_body = input;
        return meta;
    }

    cursor = fm_start;
    while (cursor < fm_end) {
        char line[256];
        size_t len = 0;
        char *next_line = strchr(cursor, '\n');
        if (!next_line || next_line > fm_end) next_line = fm_end;

        len = next_line - cursor;
        if (len >= sizeof(line)) len = sizeof(line) - 1;
        strncpy(line, cursor, len);
        line[len] = '\0';

        if (strncmp(line, "base:", 5) == 0) {
            sscanf(line + 5, " %255s", meta.base_template);
        } else if (strncmp(line, "name:", 5) == 0) {
            sscanf(line + 5, " %[^\n]", meta.page_name);
        }

        cursor = (*next_line == '\n') ? next_line + 1 : next_line;
    }

    cursor = fm_end + 3;
    while (*cursor == '\r' || *cursor == '\n') cursor++;
    meta.markdown_body = cursor;

    return meta;
}

int main(int argc, char **argv) {
    FILE *fp;
    char *raw_file_buf, *html_body;
    long file_size;
    PageMeta meta;
    Tcl_Interp *interp;

    /* In-memory Tcht template evaluator script */
    const char *tcl_render_script =
        "proc include {path} {\n"
        "    if {[file exists $path]} {\n"
        "        set f [open $path r]\n"
        "        set d [read $f]\n"
        "        close $f\n"
        "        return [subst -nobackslashes -nocommands $d]\n"
        "    }\n"
        "    return \"\"\n"
        "}\n"
        "set f [open $tpl_file r]\n"
        "set raw_tpl [read $f]\n"
        "close $f\n"
        "set final_html [subst -nobackslashes -nocommands $raw_tpl]\n"
        "file mkdir [file dirname $out_file]\n"
        "set f [open $out_file w]\n"
        "puts -nonewline $f $final_html\n"
        "close $f\n";

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <input.md> <output.html> <default_template.tcht>\n", argv[0]);
        return 1;
    }

    /* 1. Read Markdown File */
    fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "Error opening %s\n", argv[1]);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    raw_file_buf = (char *)malloc(file_size + 1);
    if (!raw_file_buf) {
        fclose(fp);
        return 1;
    }
    fread(raw_file_buf, 1, file_size, fp);
    fclose(fp);
    raw_file_buf[file_size] = '\0';

    /* 2. Process Frontmatter & Render Markdown */
    meta = parse_frontmatter(raw_file_buf);

    if (strlen(meta.base_template) == 0) {
        strcpy(meta.base_template, (strlen(argv[3]) > 0) ? argv[3] : "templates/base.tcht");
    }

    html_body = cmark_markdown_to_html(meta.markdown_body, strlen(meta.markdown_body), CMARK_OPT_UNSAFE);
    free(raw_file_buf);

    /* 3. Evaluate Tcht via Embedded Tcl Interpreter */
    interp = Tcl_CreateInterp();
    if (Tcl_Init(interp) == TCL_ERROR) {
        fprintf(stderr, "Tcl Init Error: %s\n", Tcl_GetStringResult(interp));
        free(html_body);
        return 1;
    }

    Tcl_SetVar(interp, "tpl_file", meta.base_template, 0);
    Tcl_SetVar(interp, "out_file", argv[2], 0);
    Tcl_SetVar(interp, "page_name", meta.page_name, 0);
    Tcl_SetVar(interp, "body_content", html_body, 0);

    if (Tcl_Eval(interp, tcl_render_script) == TCL_ERROR) {
        fprintf(stderr, "Tcl Evaluation Error: %s\n", Tcl_GetStringResult(interp));
        free(html_body);
        Tcl_DeleteInterp(interp);
        return 1;
    }

    free(html_body);
    Tcl_DeleteInterp(interp);

    return 0;
}
