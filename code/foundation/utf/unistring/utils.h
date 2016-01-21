/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 lis (lis@tutanota.com)
    (PGP: 0x98E65B43B03E8A6B68BA3132568ACAF1A05DE1CE)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------------<!--*/
#ifndef NIC_3CF411152E9DC193_NIC
#define NIC_3CF411152E9DC193_NIC

#include "../types.h"

#include <unistr.h>
#include <unictype.h>
#include <uninorm.h>
#include <uniwbrk.h>
#include <unicase.h>
#include <uniwidth.h>

namespace nebula { namespace foundation { namespace utf {
namespace unistring {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
n_static_assert(sizeof(ucs4_t)==sizeof(char32_t), "");
 
//------------------------------------------------------------------------------
inline constexpr const ::uint8_t *to_ustr(const char *ptr) noexcept {
    return static_cast<const ::uint8_t*>(static_cast<const void *>(ptr));
}
inline constexpr ::uint8_t *to_ustr(char *ptr) noexcept {
    return static_cast<::uint8_t*>(static_cast<void *>(ptr));
}
inline constexpr const char *from_ustr(const ::uint8_t *ptr) noexcept {
    return static_cast<const char*>(static_cast<const void *>(ptr));
}
inline constexpr char *from_ustr(::uint8_t *ptr) noexcept {
    return static_cast<char*>(static_cast<void *>(ptr));
}

//------------------------------------------------------------------------------
inline ::uninorm_t to_uninorm_t(const normal_form nf)
{
    switch(nf)
    {
    case normal_form::nfc: return UNINORM_NFC;
    case normal_form::nfd: return UNINORM_NFD;
    case normal_form::nfkc: return UNINORM_NFKC;
    case normal_form::nfkd: return UNINORM_NFKD;
    default:
        n_throw(logic_error);
    };
}
//------------------------------------------------------------------------------
inline ::uc_property_t to_uc_property_t(const property p)
{
    switch(p)
    {
        case property::white_space: return ::UC_PROPERTY_WHITE_SPACE;
        case property::alphabetic: return ::UC_PROPERTY_ALPHABETIC;
        case property::other_alphabetic: return ::UC_PROPERTY_OTHER_ALPHABETIC;
        case property::not_a_character: return ::UC_PROPERTY_NOT_A_CHARACTER;
        case property::default_ignorable_code_point: return ::UC_PROPERTY_DEFAULT_IGNORABLE_CODE_POINT;
        case property::other_default_ignorable_code_point: return ::UC_PROPERTY_OTHER_DEFAULT_IGNORABLE_CODE_POINT;
        case property::deprecated: return ::UC_PROPERTY_DEPRECATED;
        case property::logical_order_exception: return ::UC_PROPERTY_LOGICAL_ORDER_EXCEPTION;
        case property::variation_selector: return ::UC_PROPERTY_VARIATION_SELECTOR;
        case property::private_use: return ::UC_PROPERTY_PRIVATE_USE;
        case property::unassigned_code_value: return ::UC_PROPERTY_UNASSIGNED_CODE_VALUE;
        case property::uppercase: return ::UC_PROPERTY_UPPERCASE;
        case property::other_uppercase: return ::UC_PROPERTY_OTHER_UPPERCASE;
        case property::lowercase: return ::UC_PROPERTY_LOWERCASE;
        case property::other_lowercase: return ::UC_PROPERTY_OTHER_LOWERCASE;
        case property::titlecase: return ::UC_PROPERTY_TITLECASE;
        case property::soft_dotted: return ::UC_PROPERTY_SOFT_DOTTED;
        case property::id_start: return ::UC_PROPERTY_ID_START;
        case property::other_id_start: return ::UC_PROPERTY_OTHER_ID_START;
        case property::id_continue: return ::UC_PROPERTY_ID_CONTINUE;
        case property::other_id_continue: return ::UC_PROPERTY_OTHER_ID_CONTINUE;
        case property::xid_start: return ::UC_PROPERTY_XID_START;
        case property::xid_continue: return ::UC_PROPERTY_XID_CONTINUE;
        case property::pattern_white_space: return ::UC_PROPERTY_PATTERN_WHITE_SPACE;
        case property::pattern_syntax: return ::UC_PROPERTY_PATTERN_SYNTAX;
        case property::join_control: return ::UC_PROPERTY_JOIN_CONTROL;
        case property::grapheme_base: return ::UC_PROPERTY_GRAPHEME_BASE;
        case property::grapheme_extend: return ::UC_PROPERTY_GRAPHEME_EXTEND;
        case property::other_grapheme_extend: return ::UC_PROPERTY_OTHER_GRAPHEME_EXTEND;
        case property::grapheme_link: return ::UC_PROPERTY_GRAPHEME_LINK;
        case property::bidi_control: return ::UC_PROPERTY_BIDI_CONTROL;
        case property::bidi_left_to_right: return ::UC_PROPERTY_BIDI_LEFT_TO_RIGHT;
        case property::bidi_hebrew_right_to_left: return ::UC_PROPERTY_BIDI_HEBREW_RIGHT_TO_LEFT;
        case property::bidi_arabic_right_to_left: return ::UC_PROPERTY_BIDI_ARABIC_RIGHT_TO_LEFT;
        case property::bidi_european_digit: return ::UC_PROPERTY_BIDI_EUROPEAN_DIGIT;
        case property::bidi_eur_num_separator: return ::UC_PROPERTY_BIDI_EUR_NUM_SEPARATOR;
        case property::bidi_eur_num_terminator: return ::UC_PROPERTY_BIDI_EUR_NUM_TERMINATOR;
        case property::bidi_arabic_digit: return ::UC_PROPERTY_BIDI_ARABIC_DIGIT;
        case property::bidi_common_separator: return ::UC_PROPERTY_BIDI_COMMON_SEPARATOR;
        case property::bidi_block_separator: return ::UC_PROPERTY_BIDI_BLOCK_SEPARATOR;
        case property::bidi_segment_separator: return ::UC_PROPERTY_BIDI_SEGMENT_SEPARATOR;
        case property::bidi_whitespace: return ::UC_PROPERTY_BIDI_WHITESPACE;
        case property::bidi_non_spacing_mark: return ::UC_PROPERTY_BIDI_NON_SPACING_MARK;
        case property::bidi_boundary_neutral: return ::UC_PROPERTY_BIDI_BOUNDARY_NEUTRAL;
        case property::bidi_pdf: return ::UC_PROPERTY_BIDI_PDF;
        case property::bidi_embedding_or_override: return ::UC_PROPERTY_BIDI_EMBEDDING_OR_OVERRIDE;
        case property::bidi_other_neutral: return ::UC_PROPERTY_BIDI_OTHER_NEUTRAL;
        case property::hex_digit: return ::UC_PROPERTY_HEX_DIGIT;
        case property::ascii_hex_digit: return ::UC_PROPERTY_ASCII_HEX_DIGIT;
        case property::ideographic: return ::UC_PROPERTY_IDEOGRAPHIC;
        case property::unified_ideograph: return ::UC_PROPERTY_UNIFIED_IDEOGRAPH;
        case property::radical: return ::UC_PROPERTY_RADICAL;
        case property::ids_binary_operator: return ::UC_PROPERTY_IDS_BINARY_OPERATOR;
        case property::ids_trinary_operator: return ::UC_PROPERTY_IDS_TRINARY_OPERATOR;
        case property::zero_width: return ::UC_PROPERTY_ZERO_WIDTH;
        case property::space: return ::UC_PROPERTY_SPACE;
        case property::non_break: return ::UC_PROPERTY_NON_BREAK;
        case property::iso_control: return ::UC_PROPERTY_ISO_CONTROL;
        case property::format_control: return ::UC_PROPERTY_FORMAT_CONTROL;
        case property::dash: return ::UC_PROPERTY_DASH;
        case property::hyphen: return ::UC_PROPERTY_HYPHEN;
        case property::punctuation: return ::UC_PROPERTY_PUNCTUATION;
        case property::line_separator: return ::UC_PROPERTY_LINE_SEPARATOR;
        case property::paragraph_separator: return ::UC_PROPERTY_PARAGRAPH_SEPARATOR;
        case property::quotation_mark: return ::UC_PROPERTY_QUOTATION_MARK;
        case property::sentence_terminal: return ::UC_PROPERTY_SENTENCE_TERMINAL;
        case property::terminal_punctuation: return ::UC_PROPERTY_TERMINAL_PUNCTUATION;
        case property::currency_symbol: return ::UC_PROPERTY_CURRENCY_SYMBOL;
        case property::math: return ::UC_PROPERTY_MATH;
        case property::other_math: return ::UC_PROPERTY_OTHER_MATH;
        case property::paired_punctuation: return ::UC_PROPERTY_PAIRED_PUNCTUATION;
        case property::left_of_pair: return ::UC_PROPERTY_LEFT_OF_PAIR;
        case property::combining: return ::UC_PROPERTY_COMBINING;
        case property::composite: return ::UC_PROPERTY_COMPOSITE;
        case property::decimal_digit: return ::UC_PROPERTY_DECIMAL_DIGIT;
        case property::numeric: return ::UC_PROPERTY_NUMERIC;
        case property::diacritic: return ::UC_PROPERTY_DIACRITIC;
        case property::extender: return ::UC_PROPERTY_EXTENDER;
        case property::ignorable_control: return ::UC_PROPERTY_IGNORABLE_CONTROL;
        default:
            n_throw(logic_error);
    }
}

/** @} */

}}}} // namespaces

#endif // NIC_3CF411152E9DC193_NIC

