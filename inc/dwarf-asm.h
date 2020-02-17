// SPDX-License-Identifier: GPL-2-or-later
/*
 * dwarf-asm.h
 * Copyright 2020 Peter Jones <pjones@redhat.com>
 */

#ifndef DWARF_ASM_H_
#define DWARF_ASM_H_

#ifdef __ASSEMBLER__

#define ___CONCAT(x,y) x ## y
#define __CONCAT(x,y) ___CONCAT(x,y)
#ifdef __ARMEL__
#define DEBUG_INFO_STM %
#else
#define DEBUG_INFO_STM @
#endif
#define DEBUG_INFO_SECTION(name, flags, type, args...) \
	.section name, flags, __CONCAT(DEBUG_INFO_STM,type), ## args

#define DEBUG_INFO_HEADER(text, etext, entry, producer, dir, file)	\
	DEBUG_INFO_SECTION(".debug_info","",progbits)			;\
		.4byte	.Ldebug_info_end-.Ldebug_info_start		;\
	.Ldebug_info_start:						;\
		.2byte	0x3						;\
		.4byte	.Ldebug_abbrev0					;\
		.byte	__SIZEOF_POINTER__				;\
	.Ldebug_info_cu:						;\
		.uleb128 1						;\
		.4byte		producer				;\
		.2byte		0					;\
		.4byte		file					;\
		.4byte		dir					;\
		DEBUG_INFO_PTR	text					;\
		.4byte		etext - text				;\
		DEBUG_INFO_PTR	entry					;\
		.4byte		0					;\
		.4byte		0

/*
 * n is a monotonically increasing integer starting at 2, and must match a
 * DEBUG_INFO_ABBREV(n) invocation.
 */
#define DEBUG_INFO_FUNCTION(n, line, start, end, label)	\
	.uleb128	n				;\
	.4byte		label				;\
	.byte		1				;\
	.byte		line				;\
	.byte		0				;\
	DEBUG_INFO_PTR	start				;\
	DEBUG_INFO_PTR	end

#define DEBUG_INFO_LABEL(n, line, locus, label)		\
	.uleb128	n				;\
	.4byte		label				;\
	.byte		1				;\
	.byte		line				;\
	.byte		1				;\
	DEBUG_INFO_PTR	locus

#define DEBUG_INFO_FOOTER()					\
	.Ldebug_info_end:

#define DEBUG_ABBREV_HEADER()					\
	DEBUG_INFO_SECTION(.debug_abbrev,"",progbits)		;\
	.Ldebug_abbrev0:					;\
		.uleb128 1					;\
		.uleb128	DW_TAG_compile_unit		;\
		.byte		DW_CHILDREN_yes			;\
		.uleb128	DW_AT_producer			;\
		.uleb128	DW_FORM_strp			;\
		.uleb128	DW_AT_language			;\
		.uleb128	DW_FORM_data2			;\
		.uleb128	DW_AT_name			;\
		.uleb128	DW_FORM_strp			;\
		.uleb128	DW_AT_comp_dir			;\
		.uleb128	DW_FORM_strp			;\
		.uleb128	DW_AT_low_pc			;\
		.uleb128	DW_FORM_addr			;\
		.uleb128	DW_AT_high_pc			;\
		.uleb128	DW_FORM_sec_offset		;\
		.uleb128	DW_AT_entry_pc			;\
		.uleb128	DW_FORM_addr			;\
		.uleb128	DW_AT_stmt_list			;\
		.uleb128	DW_FORM_sec_offset		;\
		.uleb128	DW_AT_GNU_macros		;\
		.uleb128	DW_FORM_sec_offset		;\
		.byte		DW_AT_end			;\
		.byte		DW_FORM_end

/*
 * n is a monotonically increasing integer starting at 2, and must match a
 * DEBUG_INFO_LOCAL(n, ...) invocation.
 */
#define DEBUG_ABBREV_FUNCTION(n)		\
	.uleb128	n			;\
	.uleb128	DW_TAG_subprogram	;\
	.byte		DW_CHILDREN_yes		;\
	.uleb128	DW_AT_external		;\
	.uleb128	DW_FORM_flag_present	;\
	.uleb128	DW_AT_name		;\
	.uleb128	DW_FORM_strp		;\
	.uleb128	DW_AT_decl_file		;\
	.uleb128	DW_FORM_data1		;\
	.uleb128	DW_AT_decl_line		;\
	.uleb128	DW_FORM_data1		;\
	.uleb128	DW_AT_decl_column	;\
	.uleb128	DW_FORM_data1		;\
	.uleb128	DW_AT_prototyped	;\
	.uleb128	DW_FORM_flag_present	;\
	.uleb128	DW_AT_low_pc		;\
	.uleb128	DW_FORM_addr		;\
	.uleb128	DW_AT_high_pc		;\
	.uleb128	DEBUG_INFO_FORM_PC	;\
	.byte		DW_AT_end		;\
	.byte		DW_FORM_end

#define DEBUG_ABBREV_LABEL(n)			\
	.uleb128	n			;\
	.uleb128	DW_TAG_label		;\
	.byte		DW_CHILDREN_yes		;\
	.uleb128	DW_AT_name		;\
	.uleb128	DW_FORM_strp		;\
	.uleb128	DW_AT_decl_file		;\
	.uleb128	DW_FORM_data1		;\
	.uleb128	DW_AT_decl_line		;\
	.uleb128	DW_FORM_data1		;\
	.uleb128	DW_AT_decl_column	;\
	.uleb128	DW_FORM_data1		;\
	.uleb128	DW_AT_low_pc		;\
	.uleb128	DW_FORM_addr		;\
	.byte		DW_AT_end		;\
	.byte		DW_FORM_end

#define DEBUG_ABBREV_END()			\
	.uleb128	0xffff			;\
	.uleb128	0			;\
	.byte		DW_CHILDREN_no		;\
	.byte		DW_AT_end		;\
	.byte		DW_FORM_end		;\
	.byte 0

#define DEBUG_INFO_STR(label, value)					\
	DEBUG_INFO_SECTION(.debug_str,"SMG",progbits,1,.debug_str)	;\
	label:								;\
		.string value

#define DEBUG_INFO_STR_END()

#else /* !__ASSEMBLER__ */
#define DEBUG_INFO_HEADER(...)
#define DEBUG_INFO_FUNCTION(...)
#define DEBUG_INFO_FOOTER()
#define DEBUG_ABBREV_HEADER()
#define DEBUG_ABBREV_FUNCTION(...)
#define DEBUG_ABBREV_END()
#define DEBUG_INFO_STR(...)
#define DEBUG_INFO_STR_END()
#endif

#endif /* !DWARF_ASM_H_ */
// vim:fenc=utf-8:tw=75:noet
