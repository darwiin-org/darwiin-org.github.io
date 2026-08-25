#!/usr/bin/env tclsh

if {$argc < 4} {
    puts "Usage: rTemplate.tcl <tpl_file> <out_file> <page_name> <body_file>"
    exit 1
}

set template_file [lindex $argv 0]
set out_file      [lindex $argv 1]
set page_name     [lindex $argv 2]
set body_file     [lindex $argv 3]

proc include {path} {
    if {[file exists $path]} {
        set fp [open $path r]
        set data [read $fp]
        close $fp
        return [subst -nobackslashes -nocommands $data]
    }
    return ""
}

set fp [open $body_file r]
set body_content [read $fp]
close $fp

set fp [open $template_file r]
set raw_template [read $fp]
close $fp

set final_html [subst -nobackslashes -nocommands $raw_template]

set fp [open $out_file w]
puts $fp $final_html
close $fp
