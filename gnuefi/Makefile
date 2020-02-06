#
#  Copyright (C) 1999-2001 Hewlett-Packard Co.
#	Contributed by David Mosberger <davidm@hpl.hp.com>
#	Contributed by Stephane Eranian <eranian@hpl.hp.com>
#
#    All rights reserved.
#
#    Redistribution and use in source and binary forms, with or without
#    modification, are permitted provided that the following conditions
#    are met:
#
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above
#      copyright notice, this list of conditions and the following
#      disclaimer in the documentation and/or other materials
#      provided with the distribution.
#    * Neither the name of Hewlett-Packard Co. nor the names of its
#      contributors may be used to endorse or promote products derived
#      from this software without specific prior written permission.
#
#    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
#    CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
#    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
#    BE LIABLE FOR ANYDIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
#    OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
#    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
#    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
#    THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#    SUCH DAMAGE.
#

SRCDIR = .

VPATH = $(SRCDIR)
TOPDIR = $(SRCDIR)/..

include $(SRCDIR)/../Make.version
include $(SRCDIR)/../Make.defaults

FILES	= reloc_$(ARCH)

OBJS	= $(FILES:%=%.o)

# on aa64, avoid jump tables before all relocations have been processed
reloc_aa64.o: CFLAGS += -fno-jump-tables

TARGETS	= crt0-efi-$(ARCH).o libgnuefi.a

all:	$(TARGETS)

libgnuefi.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	@rm -vf $(TARGETS) *~ *.o $(OBJS)

install:
	@mkdir -p $(INSTALLROOT)$(LIBDIR)/gnuefi/$(ARCH)
	@$(INSTALL) -v -m 644 -t $(INSTALLROOT)$(LIBDIR)/gnuefi/$(ARCH) libgnuefi.a
	@$(INSTALL) -v -m 644 crt0-efi-$(ARCH).o $(INSTALLROOT)$(LIBDIR)/gnuefi/$(ARCH)/crt0.o
ifneq (,$(findstring FreeBSD,$(OS)))
 ifeq ($(ARCH),x64)
	@$(INSTALL) -v -m 644 $(SRCDIR)/elf_$(ARCH)_fbsd_efi.lds $(INSTALLROOT)$(LIBDIR)/gnuefi/$(ARCH)/efi.lds
 else
	@$(INSTALL) -v -m 644 $(SRCDIR)/elf_$(ARCH)_efi.lds $(INSTALLROOT)$(LIBDIR)/gnuefi/$(ARCH)/efi.lds
 endif
else
	@$(INSTALL) -v -m 644 $(SRCDIR)/elf_$(ARCH)_efi.lds $(INSTALLROOT)$(LIBDIR)/gnuefi/$(ARCH)/efi.lds
endif

install_compat: install
	mkdir -p $(INSTALLROOT)$(LIBDIR)
	$(SYMLINK) gnuefi/$(ARCH)/libgnuefi.a $(INSTALLROOT)$(LIBDIR)/libgnuefi.a
	$(SYMLINK) gnuefi/$(ARCH)/crt0.o $(INSTALLROOT)$(LIBDIR)/crt0-efi-$(BFD_ARCH).o
ifneq (,$(findstring FreeBSD,$(OS)))
 ifeq ($(ARCH),x64)
	$(SYMLINK) gnuefi/$(ARCH)/elf_$(ARCH)_fbsd_efi.lds $(INSTALLROOT)$(LIBDIR)/elf_$(BFD_ARCH)_fbsd_efi.lds
 else
	$(SYMLINK) gnuefi/$(ARCH)/efi.lds $(INSTALLROOT)$(LIBDIR)/elf_$(BFD_ARCH)_efi.lds
 endif
else
	$(SYMLINK) gnuefi/$(ARCH)/efi.lds $(INSTALLROOT)$(LIBDIR)/elf_$(BFD_ARCH)_efi.lds
endif

include $(SRCDIR)/../Make.rules
