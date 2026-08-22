# puredarwin.github.io

## System Dependencies

### APT (Debian / Ubuntu)
	git cmake make-guile tcl-dev pkgconf gcc clang

### Homebrew (macOS)
	cmake guile tcl-pkg pkgconf llvm


## How to Build the PureDarwin Website

### Building the Project

The build system utilizes GNU Make. To compile the project from source, execute:

	gmake

### Generating distfiles

The distfiles utilize build.tcl. To generate the distfiles, execute:
	
	./build.tcl
