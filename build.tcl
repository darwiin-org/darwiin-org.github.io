#!/usr/bin/env tclsh

source "files.tcl"

# Recursive directory copy helper
proc copy_static_assets {src dst} {
    if {![file exists $src]} { return }
    file mkdir $dst
    foreach item [glob -nocomplain -directory $src *] {
        set target [file join $dst [file tail $item]]
        if {[file isdirectory $item]} {
            copy_static_assets $item $target
        } else {
            file copy -force $item $target
        }
    }
}

# 1. Prepare output folder
file mkdir "output"

# 2. Build pages listed in files.tcl
foreach page $PAGES {
    set src_md [lindex $page 0]
    set out_html [lindex $page 1]
    set tpl_override [lindex $page 2]

    if {[file exists $src_md]} {
        puts "Processing: $src_md -> $out_html"
        exec ./pdssg $src_md $out_html $tpl_override
    } else {
        puts "Warning: Source file $src_md not found."
    }
}

# 3. Sync static assets to output directory
puts "Syncing static assets..."
copy_static_assets "static" "output"
