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

TARGETS	= gnu-efi-$(ARCH).pc \
	  $(foreach arch,$(ARCH) $(ARCH_ALIASES),$(arch)-efi-gnu.personality)

all:	$(TARGETS)

clean:
	@rm -vf $(TARGETS) *~

install:
	@mkdir -p $(INSTALLROOT)$(SHAREDIR)/pkgconfig/$(ARCH)-efi-gnu/
	@mkdir -p $(INSTALLROOT)$(SHAREDIR)/pkgconfig/personality.d/
	@$(INSTALL) -v -m 644 gnu-efi-$(ARCH).pc $(INSTALLROOT)$(SHAREDIR)/pkgconfig/$(ARCH)-efi-gnu/gnu-efi.pc
	@$(INSTALL) -v -m 644 $(foreach arch,$(ARCH) $(ARCH_ALIASES),$(arch)-efi-gnu.personality) \
		$(INSTALLROOT)$(SHAREDIR)/pkgconfig/personality.d/

.PHONY: install install_compat

include $(SRCDIR)/../Make.rules
