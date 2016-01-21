/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2015-2016 (lis@tutanota.com)
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
#ifndef NIC_80CF68032B421777_NIC
#define NIC_80CF68032B421777_NIC

namespace nebula { namespace foundation { namespace utf {
/** @ingroup Foundation
 * @{
 * */
//------------------------------------------------------------------------------
struct block_t
{
    char32_t first;
    char32_t last;
    const_cstring name;
};

//------------------------------------------------------------------------------
enum class normal_form
{
    nfc,
    nfd,
    nfkc,
    nfkd
};

//------------------------------------------------------------------------------
enum class property
{
    white_space,
    alphabetic,
    other_alphabetic,
    not_a_character,
    default_ignorable_code_point,
    other_default_ignorable_code_point,
    deprecated,
    logical_order_exception,
    variation_selector,
    private_use,
    unassigned_code_value,
    uppercase,
    other_uppercase,
    lowercase,
    other_lowercase,
    titlecase,
    soft_dotted,
    id_start,
    other_id_start,
    id_continue,
    other_id_continue,
    xid_start,
    xid_continue,
    pattern_white_space,
    pattern_syntax,
    join_control,
    grapheme_base,
    grapheme_extend,
    other_grapheme_extend,
    grapheme_link,
    bidi_control,
    bidi_left_to_right,
    bidi_hebrew_right_to_left,
    bidi_arabic_right_to_left,
    bidi_european_digit,
    bidi_eur_num_separator,
    bidi_eur_num_terminator,
    bidi_arabic_digit,
    bidi_common_separator,
    bidi_block_separator,
    bidi_segment_separator,
    bidi_whitespace,
    bidi_non_spacing_mark,
    bidi_boundary_neutral,
    bidi_pdf,
    bidi_embedding_or_override,
    bidi_other_neutral,
    hex_digit,
    ascii_hex_digit,
    ideographic,
    unified_ideograph,
    radical,
    ids_binary_operator,
    ids_trinary_operator,
    zero_width,
    space,
    non_break,
    iso_control,
    format_control,
    dash,
    hyphen,
    punctuation,
    line_separator,
    paragraph_separator,
    quotation_mark,
    sentence_terminal,
    terminal_punctuation,
    currency_symbol,
    math,
    other_math,
    paired_punctuation,
    left_of_pair,
    combining,
    composite,
    decimal_digit,
    numeric,
    diacritic,
    extender,
    ignorable_control
};

/** @} */

}}} // namespaces

#endif // NIC_80CF68032B421777_NIC

