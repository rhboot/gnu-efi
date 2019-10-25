SRCDIR = .

VPATH = $(SRCDIR)
TOPDIR = $(SRCDIR)/..

include $(SRCDIR)/../Make.defaults

all:

clean:

install:
	mkdir -p $(INSTALLROOT)$(PREFIX)/include/efi
	mkdir -p $(INSTALLROOT)$(PREFIX)/include/efi/protocol
	mkdir -p $(INSTALLROOT)$(PREFIX)/include/efi/$(ARCH)
	$(INSTALL) -m 644 $(SRCDIR)/*.h $(INSTALLROOT)$(PREFIX)/include/efi
	$(INSTALL) -m 644 $(SRCDIR)/protocol/*.h $(INSTALLROOT)$(PREFIX)/include/efi/protocol
	$(INSTALL) -m 644 $(SRCDIR)/$(ARCH)/*.h $(INSTALLROOT)$(PREFIX)/include/efi/$(ARCH)

install_compat: install
	@if [ ! -h $(DEST)/$(BFD_ARCH) ]; then $(SYMLINK) $(ARCH) $(INSTALLROOT)$(PREFIX)/include/efi/$(BFD_ARCH) ; fi

include $(SRCDIR)/../Make.rules
