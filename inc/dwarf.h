// SPDX-License-Identifier: GPL-2-or-later
/*
 * dwarf-asm.h
 * Copyright 2020 Peter Jones <pjones@redhat.com>
 */
#ifndef DWARF_H_
#define DWARF_H_ 1

/* DWARF Unit Header Types.  */
#define DW_UT_compile				0x01
#define DW_UT_type				0x02
#define DW_UT_partial				0x03
#define DW_UT_skeleton				0x04
#define DW_UT_split_compile			0x05
#define DW_UT_split_type			0x06

#define DW_UT_lo_user				0x80
#define DW_UT_hi_user				0xff

/* DWARF tags.  */
#define DW_TAG_array_type			0x01
#define DW_TAG_class_type			0x02
#define DW_TAG_entry_point			0x03
#define DW_TAG_enumeration_type			0x04
#define DW_TAG_formal_parameter			0x05
#define DW_TAG_reserved_0x06			0x06
#define DW_TAG_reserved_0x07			0x07
#define DW_TAG_imported_declaration		0x08
#define DW_TAG_reserved_0x09			0x09
#define DW_TAG_label				0x0a
#define DW_TAG_lexical_block			0x0b
#define DW_TAG_reserved_0x0c			0x0c
#define DW_TAG_member				0x0d
#define DW_TAG_reserved_0x0e			0x0e
#define DW_TAG_pointer_type			0x0f
#define DW_TAG_reference_type			0x10
#define DW_TAG_compile_unit			0x11
#define DW_TAG_string_type			0x12
#define DW_TAG_structure_type			0x13
#define DW_TAG_reserved_0x14			0x14
#define DW_TAG_subroutine_type			0x15
#define DW_TAG_typedef				0x16
#define DW_TAG_union_type			0x17
#define DW_TAG_unspecified_parameters		0x18
#define DW_TAG_variant				0x19
#define DW_TAG_common_block			0x1a
#define DW_TAG_common_inclusion			0x1b
#define DW_TAG_inheritance			0x1c
#define DW_TAG_inlined_subroutine		0x1d
#define DW_TAG_module				0x1e
#define DW_TAG_ptr_to_member_type		0x1f
#define DW_TAG_set_type				0x20
#define DW_TAG_subrange_type			0x21
#define DW_TAG_with_stmt			0x22
#define DW_TAG_access_declaration		0x23
#define DW_TAG_base_type			0x24
#define DW_TAG_catch_block			0x25
#define DW_TAG_const_type			0x26
#define DW_TAG_constant				0x27
#define DW_TAG_enumerator			0x28
#define DW_TAG_file_type			0x29
#define DW_TAG_friend				0x2a
#define DW_TAG_namelist				0x2b
#define DW_TAG_namelist_item			0x2c
#define DW_TAG_packed_type			0x2d
#define DW_TAG_subprogram			0x2e
#define DW_TAG_template_type_parameter		0x2f
#define DW_TAG_template_value_parameter		0x30
#define DW_TAG_thrown_type			0x31
#define DW_TAG_try_block			0x32
#define DW_TAG_variant_part			0x33
#define DW_TAG_variable				0x34
#define DW_TAG_volatile_type			0x35
#define DW_TAG_dwarf_procedure			0x36
#define DW_TAG_restrict_type			0x37
#define DW_TAG_interface_type			0x38
#define DW_TAG_namespace			0x39
#define DW_TAG_imported_module			0x3a
#define DW_TAG_unspecified_type			0x3b
#define DW_TAG_partial_unit			0x3c
#define DW_TAG_imported_unit			0x3d
#define DW_TAG_reserved_0x3e			0x3e /* Was DW_TAG_mutable_type.  */
#define DW_TAG_condition			0x3f
#define DW_TAG_shared_type			0x40
#define DW_TAG_type_unit			0x41
#define DW_TAG_rvalue_reference_type		0x42
#define DW_TAG_template_alias			0x43
#define DW_TAG_coarray_type			0x44
#define DW_TAG_generic_subrange			0x45
#define DW_TAG_dynamic_type			0x46
#define DW_TAG_atomic_type			0x47
#define DW_TAG_call_site			0x48
#define DW_TAG_call_site_parameter		0x49
#define DW_TAG_skeleton_unit			0x4a
#define DW_TAG_immutable_type			0x4b

#define DW_TAG_lo_user				0x4080
#define DW_TAG_MIPS_loop			0x4081
#define DW_TAG_format_label			0x4101
#define DW_TAG_function_template		0x4102
#define DW_TAG_class_template			0x4103

#define DW_TAG_GNU_BINCL			0x4104
#define DW_TAG_GNU_EINCL			0x4105

#define DW_TAG_GNU_template_template_param	0x4106
#define DW_TAG_GNU_template_parameter_pack	0x4107
#define DW_TAG_GNU_formal_parameter_pack	0x4108
#define DW_TAG_GNU_call_site			0x4109
#define DW_TAG_GNU_call_site_parameter		0x410a

#define DW_TAG_hi_user				0xffff

/* Children determination encodings.  */
#define DW_CHILDREN_no				0
#define DW_CHILDREN_yes				1

/* DWARF attributes encodings.  */
#define DW_AT_end				0x00
#define DW_AT_sibling				0x01
#define DW_AT_location				0x02
#define DW_AT_name				0x03
#define DW_AT_reserved_0x04			0x04
#define DW_AT_reserved_0x05			0x05
#define DW_AT_reserved_0x06			0x06
#define DW_AT_reserved_0x07			0x07
#define DW_AT_reserved_0x08			0x08
#define DW_AT_ordering				0x09
#define DW_AT_reserved_0x0a			0x0a
#define DW_AT_byte_size				0x0b
#define DW_AT_bit_offset			0x0c /* Deprecated in DWARF4.  */
#define DW_AT_bit_size				0x0d
#define DW_AT_reserved_0x0e			0x0e
#define DW_AT_reserved_0x0f			0x0f
#define DW_AT_stmt_list				0x10
#define DW_AT_low_pc				0x11
#define DW_AT_high_pc				0x12
#define DW_AT_language				0x13
#define DW_AT_reserved_0x14			0x14
#define DW_AT_discr				0x15
#define DW_AT_discr_value			0x16
#define DW_AT_visibility			0x17
#define DW_AT_import				0x18
#define DW_AT_string_length			0x19
#define DW_AT_common_reference			0x1a
#define DW_AT_comp_dir				0x1b
#define DW_AT_const_value			0x1c
#define DW_AT_containing_type			0x1d
#define DW_AT_default_value			0x1e
#define DW_AT_reserved_0x1f			0x1f
#define DW_AT_inline				0x20
#define DW_AT_is_optional			0x21
#define DW_AT_lower_bound			0x22
#define DW_AT_reserved_0x23			0x23
#define DW_AT_reserved_0x24			0x24
#define DW_AT_producer				0x25
#define DW_AT_reserved_0x26			0x26
#define DW_AT_prototyped			0x27
#define DW_AT_reserved_0x28			0x28
#define DW_AT_reserved_0x29			0x29
#define DW_AT_return_addr			0x2a
#define DW_AT_reserved_0x2b			0x2b
#define DW_AT_start_scope			0x2c
#define DW_AT_reserved_0x2d			0x2d
#define DW_AT_bit_stride			0x2e
#define DW_AT_upper_bound			0x2f
#define DW_AT_reserved_0x30			0x30
#define DW_AT_abstract_origin			0x31
#define DW_AT_accessibility			0x32
#define DW_AT_address_class			0x33
#define DW_AT_artificial			0x34
#define DW_AT_base_types			0x35
#define DW_AT_calling_convention		0x36
#define DW_AT_count				0x37
#define DW_AT_data_member_location		0x38
#define DW_AT_decl_column			0x39
#define DW_AT_decl_file				0x3a
#define DW_AT_decl_line				0x3b
#define DW_AT_declaration			0x3c
#define DW_AT_discr_list			0x3d
#define DW_AT_encoding				0x3e
#define DW_AT_external				0x3f
#define DW_AT_frame_base			0x40
#define DW_AT_friend				0x41
#define DW_AT_identifier_case			0x42
#define DW_AT_macro_info			0x43 /* Deprecated in DWARF5.  */
#define DW_AT_namelist_item			0x44
#define DW_AT_priority				0x45
#define DW_AT_segment				0x46
#define DW_AT_specification			0x47
#define DW_AT_static_link			0x48
#define DW_AT_type				0x49
#define DW_AT_use_location			0x4a
#define DW_AT_variable_parameter		0x4b
#define DW_AT_virtuality			0x4c
#define DW_AT_vtable_elem_location		0x4d
#define DW_AT_allocated				0x4e
#define DW_AT_associated			0x4f
#define DW_AT_data_location			0x50
#define DW_AT_byte_stride			0x51
#define DW_AT_entry_pc				0x52
#define DW_AT_use_UTF8				0x53
#define DW_AT_extension				0x54
#define DW_AT_ranges				0x55
#define DW_AT_trampoline			0x56
#define DW_AT_call_column			0x57
#define DW_AT_call_file				0x58
#define DW_AT_call_line				0x59
#define DW_AT_description			0x5a
#define DW_AT_binary_scale			0x5b
#define DW_AT_decimal_scale			0x5c
#define DW_AT_small				0x5d
#define DW_AT_decimal_sign			0x5e
#define DW_AT_digit_count			0x5f
#define DW_AT_picture_string			0x60
#define DW_AT_mutable				0x61
#define DW_AT_threads_scaled			0x62
#define DW_AT_explicit				0x63
#define DW_AT_object_pointer			0x64
#define DW_AT_endianity				0x65
#define DW_AT_elemental				0x66
#define DW_AT_pure				0x67
#define DW_AT_recursive				0x68
#define DW_AT_signature				0x69
#define DW_AT_main_subprogram			0x6a
#define DW_AT_data_bit_offset			0x6b
#define DW_AT_const_expr			0x6c
#define DW_AT_enum_class			0x6d
#define DW_AT_linkage_name			0x6e
#define DW_AT_string_length_bit_size		0x6f
#define DW_AT_string_length_byte_size		0x70
#define DW_AT_rank				0x71
#define DW_AT_str_offsets_base			0x72
#define DW_AT_addr_base				0x73
#define DW_AT_rnglists_base			0x74
#define DW_AT_reserved_0x75			0x75
#define DW_AT_dwo_name				0x76
#define DW_AT_reference				0x77
#define DW_AT_rvalue_reference			0x78
#define DW_AT_macros				0x79
#define DW_AT_call_all_calls			0x7a
#define DW_AT_call_all_source_calls		0x7b
#define DW_AT_call_all_tail_calls		0x7c
#define DW_AT_call_return_pc			0x7d
#define DW_AT_call_value			0x7e
#define DW_AT_call_origin			0x7f
#define DW_AT_call_parameter			0x80
#define DW_AT_call_pc				0x81
#define DW_AT_call_tail_call			0x82
#define DW_AT_call_target			0x83
#define DW_AT_call_target_clobbered		0x84
#define DW_AT_call_data_location		0x85
#define DW_AT_call_data_value			0x86
#define DW_AT_noreturn				0x87
#define DW_AT_alignment				0x88
#define DW_AT_export_symbols			0x89
#define DW_AT_deleted				0x8a
#define DW_AT_defaulted				0x8b
#define DW_AT_loclists_base			0x8c

#define DW_AT_lo_user				0x2000

#define DW_AT_MIPS_fde				0x2001
#define DW_AT_MIPS_loop_begin			0x2002
#define DW_AT_MIPS_tail_loop_begin		0x2003
#define DW_AT_MIPS_epilog_begin			0x2004
#define DW_AT_MIPS_loop_unroll_factor		0x2005
#define DW_AT_MIPS_software_pipeline_depth	0x2006
#define DW_AT_MIPS_linkage_name			0x2007
#define DW_AT_MIPS_stride			0x2008
#define DW_AT_MIPS_abstract_name		0x2009
#define DW_AT_MIPS_clone_origin			0x200a
#define DW_AT_MIPS_has_inlines			0x200b
#define DW_AT_MIPS_stride_byte			0x200c
#define DW_AT_MIPS_stride_elem			0x200d
#define DW_AT_MIPS_ptr_dopetype			0x200e
#define DW_AT_MIPS_allocatable_dopetype		0x200f
#define DW_AT_MIPS_assumed_shape_dopetype	0x2010
#define DW_AT_MIPS_assumed_size			0x2011

/* GNU extensions.  */
#define DW_AT_sf_names				0x2101
#define DW_AT_src_info				0x2102
#define DW_AT_mac_info				0x2103
#define DW_AT_src_coords			0x2104
#define DW_AT_body_begin			0x2105
#define DW_AT_body_end				0x2106
#define DW_AT_GNU_vector			0x2107
#define DW_AT_GNU_guarded_by			0x2108
#define DW_AT_GNU_pt_guarded_by			0x2109
#define DW_AT_GNU_guarded			0x210a
#define DW_AT_GNU_pt_guarded			0x210b
#define DW_AT_GNU_locks_excluded		0x210c
#define DW_AT_GNU_exclusive_locks_required	0x210d
#define DW_AT_GNU_shared_locks_required		0x210e
#define DW_AT_GNU_odr_signature			0x210f
#define DW_AT_GNU_template_name			0x2110
#define DW_AT_GNU_call_site_value		0x2111
#define DW_AT_GNU_call_site_data_value		0x2112
#define DW_AT_GNU_call_site_target		0x2113
#define DW_AT_GNU_call_site_target_clobbered	0x2114
#define DW_AT_GNU_tail_call			0x2115
#define DW_AT_GNU_all_tail_call_sites		0x2116
#define DW_AT_GNU_all_call_sites		0x2117
#define DW_AT_GNU_all_source_call_sites		0x2118
#define DW_AT_GNU_locviews			0x2137
#define DW_AT_GNU_entry_view			0x2138
#define DW_AT_GNU_macros			0x2119
#define DW_AT_GNU_deleted			0x211a
/* GNU Debug Fission extensions.  */
#define DW_AT_GNU_dwo_name			0x2130
#define DW_AT_GNU_dwo_id			0x2131
#define DW_AT_GNU_ranges_base			0x2132
#define DW_AT_GNU_addr_base			0x2133
#define DW_AT_GNU_pubnames			0x2134
#define DW_AT_GNU_pubtypes			0x2135

#define DW_AT_GNU_numerator			0x2303 /* https://gcc.gnu.org/wiki/DW_AT_GNU_numerator_denominator  */
#define DW_AT_GNU_denominator			0x2304 /* https://gcc.gnu.org/wiki/DW_AT_GNU_numerator_denominator  */
#define DW_AT_GNU_bias				0x2305 /* https://gcc.gnu.org/wiki/DW_AT_GNU_bias  */

#define DW_AT_hi_user				0x3fff

/* DWARF form encodings.  */
#define DW_FORM_end				0x00
#define DW_FORM_addr				0x01
#define DW_FORM_block2				0x03
#define DW_FORM_block4				0x04
#define DW_FORM_data2				0x05
#define DW_FORM_data4				0x06
#define DW_FORM_data8				0x07
#define DW_FORM_string				0x08
#define DW_FORM_block				0x09
#define DW_FORM_block1				0x0a
#define DW_FORM_data1				0x0b
#define DW_FORM_flag				0x0c
#define DW_FORM_sdata				0x0d
#define DW_FORM_strp				0x0e
#define DW_FORM_udata				0x0f
#define DW_FORM_ref_addr			0x10
#define DW_FORM_ref1				0x11
#define DW_FORM_ref2				0x12
#define DW_FORM_ref4				0x13
#define DW_FORM_ref8				0x14
#define DW_FORM_ref_udata			0x15
#define DW_FORM_indirect			0x16
#define DW_FORM_sec_offset			0x17
#define DW_FORM_exprloc				0x18
#define DW_FORM_flag_present			0x19
#define DW_FORM_strx				0x1a
#define DW_FORM_addrx				0x1b
#define DW_FORM_ref_sup4			0x1c
#define DW_FORM_strp_sup			0x1d
#define DW_FORM_data16				0x1e
#define DW_FORM_line_strp			0x1f
#define DW_FORM_ref_sig8			0x20
#define DW_FORM_implicit_const			0x21
#define DW_FORM_loclistx			0x22
#define DW_FORM_rnglistx			0x23
#define DW_FORM_ref_sup8			0x24
#define DW_FORM_strx1				0x25
#define DW_FORM_strx2				0x26
#define DW_FORM_strx3				0x27
#define DW_FORM_strx4				0x28
#define DW_FORM_addrx1				0x29
#define DW_FORM_addrx2				0x2a
#define DW_FORM_addrx3				0x2b
#define DW_FORM_addrx4				0x2c

#define DW_FORM_GNU_addr_index			0x1f01 /* GNU Debug Fission extensions.  */
#define DW_FORM_GNU_str_index			0x1f02 /* GNU Debug Fission extensions.  */

#define DW_FORM_GNU_ref_alt			0x1f20 /* offset in alternate .debuginfo.  */
#define DW_FORM_GNU_strp_alt			0x1f21 /* offset in alternate .debug_str. */

/* DWARF location operation encodings.  */
#define DW_OP_addr				0x03 /* Constant address.  */
#define DW_OP_deref				0x06
#define DW_OP_const1u				0x08 /* Unsigned 1-byte constant.  */
#define DW_OP_const1s				0x09 /* Signed 1-byte constant.  */
#define DW_OP_const2u				0x0a /* Unsigned 2-byte constant.  */
#define DW_OP_const2s				0x0b /* Signed 2-byte constant.  */
#define DW_OP_const4u				0x0c /* Unsigned 4-byte constant.  */
#define DW_OP_const4s				0x0d /* Signed 4-byte constant.  */
#define DW_OP_const8u				0x0e /* Unsigned 8-byte constant.  */
#define DW_OP_const8s				0x0f /* Signed 8-byte constant.  */
#define DW_OP_constu				0x10 /* Unsigned LEB128 constant.  */
#define DW_OP_consts				0x11 /* Signed LEB128 constant.  */
#define DW_OP_dup				0x12
#define DW_OP_drop				0x13
#define DW_OP_over				0x14
#define DW_OP_pick				0x15 /* 1-byte stack index.  */
#define DW_OP_swap				0x16
#define DW_OP_rot				0x17
#define DW_OP_xderef				0x18
#define DW_OP_abs				0x19
#define DW_OP_and				0x1a
#define DW_OP_div				0x1b
#define DW_OP_minus				0x1c
#define DW_OP_mod				0x1d
#define DW_OP_mul				0x1e
#define DW_OP_neg				0x1f
#define DW_OP_not				0x20
#define DW_OP_or				0x21
#define DW_OP_plus				0x22
#define DW_OP_plus_uconst			0x23 /* Unsigned LEB128 addend.  */
#define DW_OP_shl				0x24
#define DW_OP_shr				0x25
#define DW_OP_shra				0x26
#define DW_OP_xor				0x27
#define DW_OP_bra				0x28 /* Signed 2-byte constant.  */
#define DW_OP_eq				0x29
#define DW_OP_ge				0x2a
#define DW_OP_gt				0x2b
#define DW_OP_le				0x2c
#define DW_OP_lt				0x2d
#define DW_OP_ne				0x2e
#define DW_OP_skip				0x2f /* Signed 2-byte constant.  */
#define DW_OP_lit0				0x30 /* Literal 0.  */
#define DW_OP_lit1				0x31 /* Literal 1.  */
#define DW_OP_lit2				0x32 /* Literal 2.  */
#define DW_OP_lit3				0x33 /* Literal 3.  */
#define DW_OP_lit4				0x34 /* Literal 4.  */
#define DW_OP_lit5				0x35 /* Literal 5.  */
#define DW_OP_lit6				0x36 /* Literal 6.  */
#define DW_OP_lit7				0x37 /* Literal 7.  */
#define DW_OP_lit8				0x38 /* Literal 8.  */
#define DW_OP_lit9				0x39 /* Literal 9.  */
#define DW_OP_lit10				0x3a /* Literal 10.  */
#define DW_OP_lit11				0x3b /* Literal 11.  */
#define DW_OP_lit12				0x3c /* Literal 12.  */
#define DW_OP_lit13				0x3d /* Literal 13.  */
#define DW_OP_lit14				0x3e /* Literal 14.  */
#define DW_OP_lit15				0x3f /* Literal 15.  */
#define DW_OP_lit16				0x40 /* Literal 16.  */
#define DW_OP_lit17				0x41 /* Literal 17.  */
#define DW_OP_lit18				0x42 /* Literal 18.  */
#define DW_OP_lit19				0x43 /* Literal 19.  */
#define DW_OP_lit20				0x44 /* Literal 20.  */
#define DW_OP_lit21				0x45 /* Literal 21.  */
#define DW_OP_lit22				0x46 /* Literal 22.  */
#define DW_OP_lit23				0x47 /* Literal 23.  */
#define DW_OP_lit24				0x48 /* Literal 24.  */
#define DW_OP_lit25				0x49 /* Literal 25.  */
#define DW_OP_lit26				0x4a /* Literal 26.  */
#define DW_OP_lit27				0x4b /* Literal 27.  */
#define DW_OP_lit28				0x4c /* Literal 28.  */
#define DW_OP_lit29				0x4d /* Literal 29.  */
#define DW_OP_lit30				0x4e /* Literal 30.  */
#define DW_OP_lit31				0x4f /* Literal 31.  */
#define DW_OP_reg0				0x50 /* Register 0.  */
#define DW_OP_reg1				0x51 /* Register 1.  */
#define DW_OP_reg2				0x52 /* Register 2.  */
#define DW_OP_reg3				0x53 /* Register 3.  */
#define DW_OP_reg4				0x54 /* Register 4.  */
#define DW_OP_reg5				0x55 /* Register 5.  */
#define DW_OP_reg6				0x56 /* Register 6.  */
#define DW_OP_reg7				0x57 /* Register 7.  */
#define DW_OP_reg8				0x58 /* Register 8.  */
#define DW_OP_reg9				0x59 /* Register 9.  */
#define DW_OP_reg10				0x5a /* Register 10.  */
#define DW_OP_reg11				0x5b /* Register 11.  */
#define DW_OP_reg12				0x5c /* Register 12.  */
#define DW_OP_reg13				0x5d /* Register 13.  */
#define DW_OP_reg14				0x5e /* Register 14.  */
#define DW_OP_reg15				0x5f /* Register 15.  */
#define DW_OP_reg16				0x60 /* Register 16.  */
#define DW_OP_reg17				0x61 /* Register 17.  */
#define DW_OP_reg18				0x62 /* Register 18.  */
#define DW_OP_reg19				0x63 /* Register 19.  */
#define DW_OP_reg20				0x64 /* Register 20.  */
#define DW_OP_reg21				0x65 /* Register 21.  */
#define DW_OP_reg22				0x66 /* Register 22.  */
#define DW_OP_reg23				0x67 /* Register 24.  */
#define DW_OP_reg24				0x68 /* Register 24.  */
#define DW_OP_reg25				0x69 /* Register 25.  */
#define DW_OP_reg26				0x6a /* Register 26.  */
#define DW_OP_reg27				0x6b /* Register 27.  */
#define DW_OP_reg28				0x6c /* Register 28.  */
#define DW_OP_reg29				0x6d /* Register 29.  */
#define DW_OP_reg30				0x6e /* Register 30.  */
#define DW_OP_reg31				0x6f /* Register 31.  */
#define DW_OP_breg0				0x70 /* Base register 0.  */
#define DW_OP_breg1				0x71 /* Base register 1.  */
#define DW_OP_breg2				0x72 /* Base register 2.  */
#define DW_OP_breg3				0x73 /* Base register 3.  */
#define DW_OP_breg4				0x74 /* Base register 4.  */
#define DW_OP_breg5				0x75 /* Base register 5.  */
#define DW_OP_breg6				0x76 /* Base register 6.  */
#define DW_OP_breg7				0x77 /* Base register 7.  */
#define DW_OP_breg8				0x78 /* Base register 8.  */
#define DW_OP_breg9				0x79 /* Base register 9.  */
#define DW_OP_breg10				0x7a /* Base register 10.  */
#define DW_OP_breg11				0x7b /* Base register 11.  */
#define DW_OP_breg12				0x7c /* Base register 12.  */
#define DW_OP_breg13				0x7d /* Base register 13.  */
#define DW_OP_breg14				0x7e /* Base register 14.  */
#define DW_OP_breg15				0x7f /* Base register 15.  */
#define DW_OP_breg16				0x80 /* Base register 16.  */
#define DW_OP_breg17				0x81 /* Base register 17.  */
#define DW_OP_breg18				0x82 /* Base register 18.  */
#define DW_OP_breg19				0x83 /* Base register 19.  */
#define DW_OP_breg20				0x84 /* Base register 20.  */
#define DW_OP_breg21				0x85 /* Base register 21.  */
#define DW_OP_breg22				0x86 /* Base register 22.  */
#define DW_OP_breg23				0x87 /* Base register 23.  */
#define DW_OP_breg24				0x88 /* Base register 24.  */
#define DW_OP_breg25				0x89 /* Base register 25.  */
#define DW_OP_breg26				0x8a /* Base register 26.  */
#define DW_OP_breg27				0x8b /* Base register 27.  */
#define DW_OP_breg28				0x8c /* Base register 28.  */
#define DW_OP_breg29				0x8d /* Base register 29.  */
#define DW_OP_breg30				0x8e /* Base register 30.  */
#define DW_OP_breg31				0x8f /* Base register 31.  */
#define DW_OP_regx				0x90 /* Unsigned LEB128 register.  */
#define DW_OP_fbreg				0x91 /* Signed LEB128 offset.  */
#define DW_OP_bregx				0x92 /* ULEB128 register followed by SLEB128 off. */
#define DW_OP_piece				0x93 /* ULEB128 size of piece addressed. */
#define DW_OP_deref_size			0x94 /* 1-byte size of data retrieved.  */
#define DW_OP_xderef_size			0x95 /* 1-byte size of data retrieved.  */
#define DW_OP_nop				0x96
#define DW_OP_push_object_address		0x97
#define DW_OP_call2				0x98
#define DW_OP_call4				0x99
#define DW_OP_call_ref				0x9a
#define DW_OP_form_tls_address			0x9b /* TLS offset to address in current thread */
#define DW_OP_call_frame_cfa			0x9c /* CFA as determined by CFI.  */
#define DW_OP_bit_piece				0x9d /* ULEB128 size and ULEB128 offset in bits.  */
#define DW_OP_implicit_value			0x9e /* DW_FORM_block follows opcode.  */
#define DW_OP_stack_value			0x9f /* No operands, special like DW_OP_piece.  */

#define DW_OP_implicit_pointer			0xa0
#define DW_OP_addrx				0xa1
#define DW_OP_constx				0xa2
#define DW_OP_entry_value			0xa3
#define DW_OP_const_type			0xa4
#define DW_OP_regval_type			0xa5
#define DW_OP_deref_type			0xa6
#define DW_OP_xderef_type			0xa7
#define DW_OP_convert				0xa8
#define DW_OP_reinterpret			0xa9

/* GNU extensions.  */
#define DW_OP_GNU_push_tls_address		0xe0
#define DW_OP_GNU_uninit			0xf0
#define DW_OP_GNU_encoded_addr			0xf1
#define DW_OP_GNU_implicit_pointer		0xf2
#define DW_OP_GNU_entry_value			0xf3
#define DW_OP_GNU_const_type			0xf4
#define DW_OP_GNU_regval_type			0xf5
#define DW_OP_GNU_deref_type			0xf6
#define DW_OP_GNU_convert			0xf7
#define DW_OP_GNU_reinterpret			0xf9
#define DW_OP_GNU_parameter_ref			0xfa

/* GNU Debug Fission extensions.  */
#define DW_OP_GNU_addr_index			0xfb
#define DW_OP_GNU_const_index			0xfc

#define DW_OP_GNU_variable_value		0xfd

#define DW_OP_lo_user				0xe0 /* Implementation-defined range start.  */
#define DW_OP_hi_user				0xff /* Implementation-defined range end.  */

/* DWARF base type encodings.  */
#define DW_ATE_void				0x0
#define DW_ATE_address				0x1
#define DW_ATE_boolean				0x2
#define DW_ATE_complex_float			0x3
#define DW_ATE_float				0x4
#define DW_ATE_signed				0x5
#define DW_ATE_signed_char			0x6
#define DW_ATE_unsigned				0x7
#define DW_ATE_unsigned_char			0x8
#define DW_ATE_imaginary_float			0x9
#define DW_ATE_packed_decimal			0xa
#define DW_ATE_numeric_string			0xb
#define DW_ATE_edited				0xc
#define DW_ATE_signed_fixed			0xd
#define DW_ATE_unsigned_fixed			0xe
#define DW_ATE_decimal_float			0xf
#define DW_ATE_UTF				0x10
#define DW_ATE_UCS				0x11
#define DW_ATE_ASCII				0x12

#define DW_ATE_lo_user				0x80
#define DW_ATE_hi_user				0xff

/* DWARF decimal sign encodings.  */
#define DW_DS_unsigned				1
#define DW_DS_leading_overpunch			2
#define DW_DS_trailing_overpunch		3
#define DW_DS_leading_separate			4
#define DW_DS_trailing_separate			5

/* DWARF endianity encodings.  */
#define DW_END_default				0
#define DW_END_big				1
#define DW_END_little				2

#define DW_END_lo_user				0x40
#define DW_END_hi_user				0xff

/* DWARF accessibility encodings.  */
#define DW_ACCESS_public			1
#define DW_ACCESS_protected			2
#define DW_ACCESS_private			3

/* DWARF visibility encodings.  */
#define DW_VIS_local				1
#define DW_VIS_exported				2
#define DW_VIS_qualified			3

/* DWARF virtuality encodings.  */
#define DW_VIRTUALITY_none			0
#define DW_VIRTUALITY_virtual			1
#define DW_VIRTUALITY_pure_virtual		2

/* DWARF language encodings.  */
#define DW_LANG_C89				0x0001 /* ISO C:1989 */
#define DW_LANG_C				0x0002 /* C */
#define DW_LANG_Ada83				0x0003 /* ISO Ada:1983 */
#define DW_LANG_C_plus_plus			0x0004 /* ISO C++:1998 */
#define DW_LANG_Cobol74				0x0005 /* ISO Cobol:1974 */
#define DW_LANG_Cobol85				0x0006 /* ISO Cobol:1985 */
#define DW_LANG_Fortran77			0x0007 /* ISO FORTRAN 77 */
#define DW_LANG_Fortran90			0x0008 /* ISO Fortran 90 */
#define DW_LANG_Pascal83			0x0009 /* ISO Pascal:1983 */
#define DW_LANG_Modula2				0x000a /* ISO Modula-2:1996 */
#define DW_LANG_Java				0x000b /* Java */
#define DW_LANG_C99				0x000c /* ISO C:1999 */
#define DW_LANG_Ada95				0x000d /* ISO Ada:1995 */
#define DW_LANG_Fortran95			0x000e /* ISO Fortran 95 */
#define DW_LANG_PLI				0x000f /* ISO PL/1:1976 */
#define DW_LANG_ObjC				0x0010 /* Objective-C */
#define DW_LANG_ObjC_plus_plus			0x0011 /* Objective-C++ */
#define DW_LANG_UPC				0x0012 /* Unified Parallel C */
#define DW_LANG_D				0x0013 /* D */
#define DW_LANG_Python				0x0014 /* Python */
#define DW_LANG_OpenCL				0x0015 /* OpenCL */
#define DW_LANG_Go				0x0016 /* Go */
#define DW_LANG_Modula3				0x0017 /* Modula-3 */
#define DW_LANG_Haskell				0x0018 /* Haskell */
#define DW_LANG_C_plus_plus_03			0x0019 /* ISO C++:2003 */
#define DW_LANG_C_plus_plus_11			0x001a /* ISO C++:2011 */
#define DW_LANG_OCaml				0x001b /* OCaml */
#define DW_LANG_Rust				0x001c /* Rust */
#define DW_LANG_C11				0x001d /* ISO C:2011 */
#define DW_LANG_Swift				0x001e /* Swift */
#define DW_LANG_Julia				0x001f /* Julia */
#define DW_LANG_Dylan				0x0020 /* Dylan */
#define DW_LANG_C_plus_plus_14			0x0021 /* ISO C++:2014 */
#define DW_LANG_Fortran03			0x0022 /* ISO/IEC 1539-1:2004 */
#define DW_LANG_Fortran08			0x0023 /* ISO/IEC 1539-1:2010 */
#define DW_LANG_RenderScript			0x0024 /* RenderScript Kernal Language */
#define DW_LANG_BLISS				0x0025 /* BLISS */

#define DW_LANG_lo_user				0x8000
#define DW_LANG_Mips_Assembler			0x8001 /* Assembler */
#define DW_LANG_hi_user				0xffff

/* DWARF calling conventions encodings.
   Used as values of DW_AT_calling_convention for subroutines
   (normal, program or nocall) or structures, unions and class types
   (normal, reference or value).  */
#define DW_CC_normal				0x1
#define DW_CC_program				0x2
#define DW_CC_nocall				0x3
#define DW_CC_pass_by_reference			0x4
#define DW_CC_pass_by_value			0x5
#define DW_CC_lo_user				0x40
#define DW_CC_hi_user				0xff

/* DWARF inline encodings.  */
#define DW_INL_not_inlined			0
#define DW_INL_inlined				1
#define DW_INL_declared_not_inlined		2
#define DW_INL_declared_inlined			3

/* DWARF ordering encodings.  */
#define DW_ORD_row_major			0
#define DW_ORD_col_major			1

/* DWARF discriminant descriptor encodings.  */
#define DW_DSC_label				0
#define DW_DSC_range				1

/* DWARF defaulted member function encodings.  */
#define DW_DEFAULTED_no				0
#define DW_DEFAULTED_in_class			1
#define DW_DEFAULTED_out_of_class		2

/* DWARF line content descriptions.  */
#define DW_LNCT_path				0x1
#define DW_LNCT_directory_index			0x2
#define DW_LNCT_timestamp			0x3
#define DW_LNCT_size				0x4
#define DW_LNCT_MD5				0x5
#define DW_LNCT_lo_user				0x2000
#define DW_LNCT_hi_user				0x3fff

/* DWARF standard opcode encodings.  */
#define DW_LNS_copy				1
#define DW_LNS_advance_pc			2
#define DW_LNS_advance_line			3
#define DW_LNS_set_file				4
#define DW_LNS_set_column			5
#define DW_LNS_negate_stmt			6
#define DW_LNS_set_basic_block			7
#define DW_LNS_const_add_pc			8
#define DW_LNS_fixed_advance_pc			9
#define DW_LNS_set_prologue_end			10
#define DW_LNS_set_epilogue_begin		11
#define DW_LNS_set_isa				12

/* DWARF extended opcode encodings.  */
#define DW_LNE_end_sequence			1
#define DW_LNE_set_address			2
#define DW_LNE_define_file			3
#define DW_LNE_set_discriminator		4

#define DW_LNE_lo_user				128
#define DW_LNE_hi_user				255

/* DWARF macinfo type encodings.  */
#define DW_MACINFO_define			1
#define DW_MACINFO_undef			2
#define DW_MACINFO_start_file			3
#define DW_MACINFO_end_file			4
#define DW_MACINFO_vendor_ext			255

/* DWARF debug_macro type encodings.  */
#define DW_MACRO_define				0x01
#define DW_MACRO_undef				0x02
#define DW_MACRO_start_file			0x03
#define DW_MACRO_end_file			0x04
#define DW_MACRO_define_strp			0x05
#define DW_MACRO_undef_strp			0x06
#define DW_MACRO_import				0x07
#define DW_MACRO_define_sup			0x08
#define DW_MACRO_undef_sup			0x09
#define DW_MACRO_import_sup			0x0a
#define DW_MACRO_define_strx			0x0b
#define DW_MACRO_undef_strx			0x0c
#define DW_MACRO_lo_user			0xe0
#define DW_MACRO_hi_user			0xff

/* Old GNU extension names for DWARF5 debug_macro type encodings.
   There are no equivalents for the supplementary object file (sup)
   and indirect string references (strx).  */
#define DW_MACRO_GNU_define			DW_MACRO_define
#define DW_MACRO_GNU_undef			DW_MACRO_undef
#define DW_MACRO_GNU_start_file			DW_MACRO_start_file
#define DW_MACRO_GNU_end_file			DW_MACRO_end_file
#define DW_MACRO_GNU_define_indirect		DW_MACRO_define_strp
#define DW_MACRO_GNU_undef_indirect		DW_MACRO_undef_strp
#define DW_MACRO_GNU_transparent_include DW_MACRO_import
#define DW_MACRO_GNU_lo_user			DW_MACRO_lo_user
#define DW_MACRO_GNU_hi_user			DW_MACRO_hi_user

/* Range list entry encoding.  */
#define DW_RLE_end_of_list			0x0
#define DW_RLE_base_addressx			0x1
#define DW_RLE_startx_endx			0x2
#define DW_RLE_startx_length			0x3
#define DW_RLE_offset_pair			0x4
#define DW_RLE_base_address			0x5
#define DW_RLE_start_end			0x6
#define DW_RLE_start_length			0x7

/* Location list entry encoding.  */
#define DW_LLE_end_of_list			0x0
#define DW_LLE_base_addressx			0x1
#define DW_LLE_startx_endx			0x2
#define DW_LLE_startx_length			0x3
#define DW_LLE_offset_pair			0x4
#define DW_LLE_default_location			0x5
#define DW_LLE_base_address			0x6
#define DW_LLE_start_end			0x7
#define DW_LLE_start_length			0x8

/* GNU DebugFission list entry encodings (.debug_loc.dwo).  */
#define DW_LLE_GNU_end_of_list_entry		0x0
#define DW_LLE_GNU_base_address_selection_entry		0x1
#define DW_LLE_GNU_start_end_entry		0x2
#define DW_LLE_GNU_start_length_entry		0x3

/* DWARF call frame instruction encodings.  */
#define DW_CFA_advance_loc			0x40
#define DW_CFA_offset				0x80
#define DW_CFA_restore				0xc0
#define DW_CFA_extended				0

#define DW_CFA_nop				0x00
#define DW_CFA_set_loc				0x01
#define DW_CFA_advance_loc1			0x02
#define DW_CFA_advance_loc2			0x03
#define DW_CFA_advance_loc4			0x04
#define DW_CFA_offset_extended			0x05
#define DW_CFA_restore_extended			0x06
#define DW_CFA_undefined			0x07
#define DW_CFA_same_value			0x08
#define DW_CFA_register				0x09
#define DW_CFA_remember_state			0x0a
#define DW_CFA_restore_state			0x0b
#define DW_CFA_def_cfa				0x0c
#define DW_CFA_def_cfa_register			0x0d
#define DW_CFA_def_cfa_offset			0x0e
#define DW_CFA_def_cfa_expression		0x0f
#define DW_CFA_expression			0x10
#define DW_CFA_offset_extended_sf		0x11
#define DW_CFA_def_cfa_sf			0x12
#define DW_CFA_def_cfa_offset_sf		0x13
#define DW_CFA_val_offset			0x14
#define DW_CFA_val_offset_sf			0x15
#define DW_CFA_val_expression			0x16

#define DW_CFA_low_user				0x1c
#define DW_CFA_MIPS_advance_loc8		0x1d
#define DW_CFA_GNU_window_save			0x2d
#define DW_CFA_GNU_args_size			0x2e
#define DW_CFA_GNU_negative_offset_extended	0x2f
#define DW_CFA_high_user			0x3f

/* ID indicating CIE as opposed to FDE in .debug_frame.  */
#define DW_CIE_ID_32				0xffffffffU /* In 32-bit format CIE header.  */
#define DW_CIE_ID_64				0xffffffffffffffffULL /* In 64-bit format CIE header. */

/* Information for GNU unwind information.  */
#define DW_EH_PE_absptr				0x00
#define DW_EH_PE_omit				0xff

/* FDE data encoding.  */
#define DW_EH_PE_uleb128			0x01
#define DW_EH_PE_udata2				0x02
#define DW_EH_PE_udata4				0x03
#define DW_EH_PE_udata8				0x04
#define DW_EH_PE_sleb128			0x09
#define DW_EH_PE_sdata2				0x0a
#define DW_EH_PE_sdata4				0x0b
#define DW_EH_PE_sdata8				0x0c
#define DW_EH_PE_signed				0x08

/* FDE flags.  */
#define DW_EH_PE_pcrel				0x10
#define DW_EH_PE_textrel			0x20
#define DW_EH_PE_datarel			0x30
#define DW_EH_PE_funcrel			0x40
#define DW_EH_PE_aligned			0x50

#define DW_EH_PE_indirect			0x80

#define DW_ADDR_none				0

/*
 * Section 7.2.2 of the DWARF3 specification defines a range of escape codes
 * that can appear in the length field of certain DWARF structures.
 *
 * These defines enumerate the minium and maximum values of this range.
 * Currently only the maximum value is used (to indicate that 64-bit values
 * are going to be used in the dwarf data that accompanies the structure).
 * The other values are reserved.
 *
 * Note: There is a typo in DWARF3 spec (published Dec 20, 2005).  In sections
 * 7.4, 7.5.1, 7.19, 7.20 the minimum escape code is referred to as
 * 0xffffff00 whereas in fact it should be 0xfffffff0.
 */
#define DWARF3_LENGTH_MIN_ESCAPE_CODE		0xfffffff0u
#define DWARF3_LENGTH_MAX_ESCAPE_CODE		0xffffffffu
#define DWARF3_LENGTH_64_BIT			DWARF3_LENGTH_MAX_ESCAPE_CODE

#if __SIZEOF_POINTER__ == 8
#define DEBUG_INFO_PTR .8byte
#define DEBUG_INFO_FORM_PC DW_FORM_data8
#else
#define DEBUG_INFO_PTR .4byte
#define DEBUG_INFO_FORM_PC DW_FORM_data4
#endif

#include "dwarf-asm.h"

#endif /* DWARF_H_ */
