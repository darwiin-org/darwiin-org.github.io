CC ?= cc
GIT ?= git
CMAKE ?= cmake

CMARK_DIR = cmark
CMARK_BUILD_DIR = $(CMARK_DIR)/build
CMARK_LIB = $(CMARK_BUILD_DIR)/src/libcmark.a

TCL_CFLAGS ?= $(shell echo 'puts [tcl::pkgconfig get include,install]' | tclsh 2>/dev/null | sed 's/^/-I/')
TCL_LDFLAGS ?= $(shell echo 'puts [tcl::pkgconfig get lib,install]' | tclsh 2>/dev/null | sed 's/^/-L/') -ltcl9.0

ifeq ($(TCL_CFLAGS),)
    TCL_CFLAGS = -I/usr/include/tcl8.6
    TCL_LDFLAGS = -ltcl8.6
endif

CFLAGS += -I$(CMARK_DIR)/src -I$(CMARK_BUILD_DIR)/src $(TCL_CFLAGS)
LDFLAGS += -L$(CMARK_BUILD_DIR)/src -lcmark $(TCL_LDFLAGS)

.PHONY: all clean

all: pdssg

$(CMARK_DIR):
	$(GIT) clone https://github.com/commonmark/cmark.git $(CMARK_DIR)

$(CMARK_LIB): | $(CMARK_DIR)
	mkdir -p $(CMARK_BUILD_DIR)
	cd $(CMARK_BUILD_DIR) && $(CMAKE) .. -DCMARK_SHARED=OFF -DCMARK_TESTS=OFF
	$(MAKE) -C $(CMARK_BUILD_DIR)

pdssg: .c/pdssg.c | $(CMARK_LIB)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf pdssg $(CMARK_DIR)
