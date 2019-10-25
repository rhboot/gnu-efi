SRCDIR = .

VPATH = $(SRCDIR)
TOPDIR = $(SRCDIR)/..

include $(SRCDIR)/../Make.defaults

all:

clean:

SOURCE=$(realpath $(SRCDIR))
DEST=$(INSTALLROOT)$(PREFIX)/include/efi
INCLUDEDIRS=$(sort $(shell find $(SOURCE) -type d))

install:
	@$(foreach d,$(INCLUDEDIRS), \
		$(INSTALL) -v -m 755 -d $(subst $(SOURCE),$(DEST),$(d)); \
		$(INSTALL) -v -m 644 -t $(subst $(SOURCE),$(DEST),$(d)) $(wildcard $(d)/*.h); \
	)

install_compat: install
	@if [ ! -h $(DEST)/x86_64 ]; then $(SYMLINK) x64/ $(DEST)/x86_64 ; fi
	@if [ ! -h $(DEST)/aarch64 ]; then $(SYMLINK) aa64/ $(DEST)/aarch64 ; fi

include $(SRCDIR)/../Make.rules
