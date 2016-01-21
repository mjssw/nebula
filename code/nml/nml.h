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
#ifndef NIC_D6A066B43404B178_NIC
#define NIC_D6A066B43404B178_NIC

#include "nml.h"
#include "dll_interface.h"
#include "../foundation/cstring.h"
#include "../foundation/tuple.h"
#include "../foundation/format.h"
#include "../foundation/stack.h"
#include "../foundation/hash_map.h"

namespace nebula { namespace nml {
/** @ingroup NML
 * @{
 * */
namespace nml_detail {

using namespace foundation;

//------------------------------------------------------------------------------
enum class token_category
{
    assignment,
    
    lbrace,
    rbrace,
    
    lbracket,
    rbracket,
    
    dollar,
    
    id,
    string,
    
    eof,
    unexpected
};
//------------------------------------------------------------------------------
struct token
{
    token_category category;
    const_cstring value;
};

//------------------------------------------------------------------------------
extern tuple<token, const char *> n_nml_dll lex(
    const_cstring s, const bool eat_white_ = true) noexcept;

//------------------------------------------------------------------------------
extern const char * n_nml_dll cat_to_str(const token_category x) noexcept;

extern tuple<size_t, const char *, const char *> n_nml_dll find_line(
    const const_cstring data, const char *pos);
    
extern string n_nml_dll source_extract(
    const const_cstring data, const char *pos);

//------------------------------------------------------------------------------
template <class ... TokenCats>
inline string pretty_error(
    const const_cstring data,
    const string &prefix,
    const char *pos,
    const TokenCats ... toks)
{
    io::msink<string> ss;
    
    fmt::fwrite(ss, prefix, fmt::endl, source_extract(data, pos));
    
    if(sizeof ... (TokenCats))
        fmt::fwrite(ss, fmt::endl, "Expected one of the following: ",
            cat_to_str(toks) ...);

    return move(ss.container());            
}
//------------------------------------------------------------------------------
template <class ... TokenCats>
inline string pretty_error(
    const const_cstring data,
    const token t,
    const TokenCats ... toks)
{
    const char *pos = t.value.begin();
    if(t.category == token_category::string)
        --pos;
    
    string prefix = fmt::to_string(
        "Offending ", cat_to_str(t.category), "token");    
    
    return pretty_error(data, prefix, pos, toks...);
}

//------------------------------------------------------------------------------
template <class CB>
inline bool add_symbol(
    hash_map<string, const char *> &lookup_table,
    string &&name,
    const char *pos,
    CB &&cb,
    const const_cstring id,
    const const_cstring data)
{
    bool res;
    tie(ignore, res) = lookup_table.emplace(move(name), pos);;
    if(!res)
    {
        string msg = fmt::to_string(
            "Redefinition of '", id, '\'', fmt::endl,
            source_extract(data, id.begin()));
        cb.error(move(msg));
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
template <class CB>
inline const char *parse_expr(
    CB &&cb,
    const char *i,
    const const_cstring data,
    const const_cstring id,
    hash_map<string, const char *> &lookup_table,
    stack<string> &block_stack,
    const bool add_to_stack,
    const size_t depth);
//------------------------------------------------------------------------------
template <class CB>
inline const char *parse_block(
    CB &&cb,
    const char *i,
    const const_cstring data,
    const const_cstring blk_id,
    hash_map<string, const char *> &lookup_table,
    stack<string> &block_stack,
    const bool add_to_stack,
    const size_t depth)
{
    cb.begin_block(blk_id);
    
    while(i != data.end())
    {
        token t;
        tie(t, i) = lex(const_cstring(i, data.end()));
        
        switch(t.category)
        {
        case token_category::eof:
            cb.error(pretty_error(data, t, token_category::rbrace));
            return data.end();
        
        case token_category::rbrace:
            if(add_to_stack)
                block_stack.pop_back();
            cb.end_block();
            return i;
            
        case token_category::dollar:
            tie(t, i) = lex(const_cstring(i, data.end()), false);
            switch(t.category)
            {
            case token_category::string:
                if(t.value.empty())
                {
                    cb.error(pretty_error(data, "<string> must not be empty",
                        t.value.begin()-1,
                        token_category::id));
                    return data.end();
                }
                break;
            case token_category::id:
                break;
            default:
                cb.error(pretty_error(data, t,
                    token_category::id,
                    token_category::string));
                return data.end();
            }
            
            if(add_to_stack)
            {
                if(!add_symbol(
                    lookup_table,
                    block_stack.back() + t.value,
                    i,
                    cb,
                    t.value,
                    data))
                    return data.end();
            }
            
            i = parse_expr(cb, i, data, t.value,
                lookup_table, block_stack, add_to_stack, depth+1);
            break;
                     
        case token_category::string:
            if(t.value.empty())
            {
                cb.error(pretty_error(data, "<string> must not be empty",
                    t.value.begin()-1,
                    token_category::id));
                return data.end();
            }
            // fall through
        case token_category::id:
            i = parse_expr(cb, i, data, t.value,
                lookup_table, block_stack, false, depth+1);
            break;
        
        case token_category::lbrace:
            i = parse_block(cb, i, data, "",
                lookup_table, block_stack, false, depth+1);
            break;
        
        default:
            cb.error(pretty_error(data, t,
                token_category::id,
                token_category::string,
                token_category::dollar,
                token_category::rbrace));
            return data.end();
        }
    }
    
    return i;
}
//------------------------------------------------------------------------------
template <class CB>
inline const char *parse_array(
    CB &&cb,
    const char *i,
    const const_cstring data,
    const const_cstring id,
    hash_map<string, const char *> &lookup_table,
    stack<string> &block_stack,
    const size_t depth)
{
    token t;
    
    cb.begin_array(id);
    
    while(true)
    {
        tie(t, i) = lex(const_cstring(i, data.end()));
        switch(t.category)
        {
        case token_category::string:
        case token_category::id:
            cb.array_element(t.value);
            continue;
        
        case token_category::dollar:
            {
                tie(t, i) = lex(const_cstring(i, data.end()), false);
                if(t.category != token_category::id
                    && t.category != token_category::string)
                {
                    cb.error(pretty_error(data, t,
                        token_category::id,
                        token_category::string));
                    return data.end();
                }
                const tuple<string, const char *> *res
                    = lookup_table.find(t.value);
                if(!res)
                {
                    cb.error(pretty_error(data,
                        fmt::to_string(
                            "Undefined symbol '", t.value, '\''),
                        t.value.begin()));
                    return data.end();
                }
                if(data.end() == parse_expr(cb, get<1>(*res), data, "",
                    lookup_table, block_stack, false, depth+1))
                    return data.end();
            }
            continue;
        
        case token_category::lbrace:
            i = parse_block(cb, i, data, "",
                lookup_table, block_stack, false, depth);
            if(data.end() == i) // to break the loop
                return data.end();
            continue;
            
        case token_category::lbracket:
            i = parse_array(cb, i, data, "", lookup_table, block_stack, depth);
            if(data.end() == i) // to break the loop
                return data.end();
            continue;
        
        case token_category::rbracket:
            break;
        
        default:
            cb.error(pretty_error(data, t,
                token_category::id,
                token_category::string,
                token_category::dollar,
                token_category::lbrace,
                token_category::lbracket,
                token_category::rbracket));
            return data.end();
        }
        
        break;
    }
    
    cb.end_array();
    
    return i;
}
//------------------------------------------------------------------------------
template <class CB>
inline const char *parse_expr(
    CB &&cb,
    const char *i,
    const const_cstring data,
    const const_cstring id,
    hash_map<string, const char *> &lookup_table,
    stack<string> &block_stack,
    const bool add_to_stack,
    const size_t depth)
{
    if(depth+1 > 1000)
    {
        cb.error(pretty_error(data,
            "Max depth reached. Check for cyclic references.",
            id.begin()));
        return data.end();
    }

    token t;
    tie(t, i) = lex(const_cstring(i, data.end()));
    
    switch(t.category)
    {
    case token_category::assignment:
        tie(t, i) = lex(const_cstring(i, data.end()));
        switch(t.category)
        {
        case token_category::dollar:
            {
                tie(t, i) = lex(const_cstring(i, data.end()), false);
                if(t.category != token_category::id
                    && t.category != token_category::string)
                {
                    cb.error(pretty_error(data, t,
                        token_category::id,
                        token_category::string));
                    return data.end();
                }
                const tuple<string, const char *> *res
                    = lookup_table.find(t.value);
                if(!res)
                {
                    cb.error(pretty_error(data,
                        fmt::to_string("Undefined symbol '", t.value, '\''),
                        t.value.begin()));
                    return data.end();
                }
                if(data.end() == parse_expr(cb, get<1>(*res), data, id,
                    lookup_table, block_stack, add_to_stack, depth+1))
                    return data.end();
            }
            break;
        
        case token_category::id:
        case token_category::string:
            cb.element(id, t.value);
            break;
        
        case token_category::lbrace:
            if(add_to_stack)
            {
                if(block_stack.empty())
                    block_stack.emplace_back(fmt::to_string(id, '.'));
                else
                    block_stack.emplace_back(
                        fmt::to_string(block_stack.back(), id, '.'));
            }
            i = parse_block(cb, i, data, id,
                lookup_table, block_stack, add_to_stack, depth);
            break;
        
        case token_category::lbracket:
            i = parse_array(cb, i, data, id, lookup_table, block_stack, depth);
            break;
        
        default:
            cb.error(pretty_error(data, t,
                token_category::id,
                token_category::string,
                token_category::lbrace,
                token_category::lbracket));
            return data.end();
        }
        break;
    
    case token_category::lbrace:
        if(add_to_stack)
        {
            if(block_stack.empty())
                block_stack.emplace_back(fmt::to_string(id, '.'));
            else
                block_stack.emplace_back(
                    fmt::to_string(block_stack.back(), id, '.'));
        }
        i = parse_block(cb, i, data, id,
            lookup_table, block_stack, add_to_stack, depth);
        break;
    
    default:
        cb.error(pretty_error(data, t,
            token_category::assignment,
            token_category::lbrace));
        return data.end();
    }
    
    return i;
}
//------------------------------------------------------------------------------
template <class CB>
inline void parse(
    CB &&cb,
    const const_cstring data,
    hash_map<string, const char *> &lookup_table,
    stack<string> &block_stack)
{
    const char *i = data.begin();
    
    while(i != data.end())
    {
        token t;
        tie(t, i) = lex(const_cstring(i, data.end()));
        
        switch(t.category)
        {
        case token_category::eof:
            return;
        case token_category::rbrace:
            cb.error(pretty_error(data, t, token_category::lbrace));
            return;
            
        case token_category::dollar:
            tie(t, i) = lex(const_cstring(i, data.end()), false);
            switch(t.category)
            {
            case token_category::string:
                if(t.value.empty())
                {
                    cb.error(pretty_error(data, "<string> must not be empty",
                        t.value.begin()-1,
                        token_category::id));
                    return;
                }
                break;
            case token_category::id:
                break;
            default:
                cb.error(pretty_error(data, t,
                    token_category::id,
                    token_category::string));
                return;
            }
            
            if(!add_symbol(
                lookup_table,
                t.value,
                i,
                cb,
                t.value,
                data))
                return;
            
            i = parse_expr(cb, i, data, t.value,
                lookup_table, block_stack, true, 0);
            break;
        
        case token_category::string:
            if(t.value.empty())
            {
                cb.error(pretty_error(data, "<string> must not be empty",
                    t.value.begin()-1,
                    token_category::id));
                return;
            }
            // fall through
        case token_category::id:
            i = parse_expr(cb, i, data, t.value,
                    lookup_table, block_stack, false, 0);
            break;
        
        case token_category::lbrace:
            i = parse_block(cb, i, data, "",
                lookup_table, block_stack, false, 0);
            break;
        
        default:
            cb.error(pretty_error(data, t,
                token_category::id,
                token_category::string,
                token_category::dollar,
                token_category::lbrace,
                token_category::eof));
            return;
        }
    }
}

} // nml_detail

//------------------------------------------------------------------------------
/** A parser for the markup language NML.
 *
 *  Below is some self-explenatory code.
 *
 *  XML
 *  @code
 *  <person firstName="John" lastName="Smith" age="25">
 *    <address streetAddress="21 2nd Street" city="New York" state="NY"
 *      postalCode="10021" />
 *    <phoneNumbers>
 *       <phoneNumber type="home" number="212 555-1234"/>
 *       <phoneNumber type="fax"  number="646 555-4567"/>
 *    </phoneNumbers>
 *    <gender type="male"/>
 *  </person>
 *  @endcode
 *  
 *  NML
 *  @code
 *  person { firstName=John lastName=Smith age=25
 *    address { streetAddress="21 2nd Street" city="New York" state="NY"
 *      postalCode=10021 }
 *    phoneNumbers {
 *      phoneNumber { type=home number="212 555-1234" }
 *      phoneNumber { type=fax  number="646 555-4567" }
 *    }
 *    gender { type=male }
 *  }
 *  @endcode
 *
 *  @code
 *  "a" = 'b!'
 *  "a" {} 'b' {}
 *  "a" = {} 'b' = {}
 *  a = []
 *  // a [] // error: missing assignment
 *  0=1 1=0
 *  -0 = +0
 *  
 *  foo = bar
 *  // x = $foo // error: foo not referencable
 *  
 *  $foo = bar
 *  x = $foo // equivalent to x == bar
 *  // $foo = baz // error: redefinition of foo
 *  
 *  $A { $B { $C = 0 } }
 *  x = $A.B.C // equivalent to x = 0
 *  
 *  $"A$ ?" { $"_%x" { } }
 *  x = $"A$ ?._%x" // equivalent to x = {}
 *  
 *  my-array = [0 1 "2" '3' $A.B.C]
 *  
 *  foo : bar // ':' behaves just like '='
 *  
 *  1=2,2=3,3=4,,, // ',' is treated as white space (ignored)
 *  
 *  { {} x = $foo } // anonymous blocks are allowed
 *  // [] // error: anonymous arrays are not allowed
 *  array : [ [] ] // but anon arrays are allowed within arrays
 *  
 *  // bad-array : [ x=y ] // error: no assignment expressions within arrays
 *  good-array : [ { x=y } ] // ok now
 *  @endcode
 *
 *  A backslash '\' can only stand within a string and causes the parser to
 *  ignore the next ascii character.
 *  
 *  @code
 *  // bad-string = "abc"xyz" // error
 *  ok-string = "abc\"xyz"
 *  ok-string = "abc'xyz'
 *  ok-string = 'abc"xyz'
 *  ok-string = 'abc\'xyz'
 *  ok-string = 'a\b\c\\\def'
 *  // bad-string = "abcdef\" // error: '\' causes the parser to ignore the
 *                            // trailing '"'.
 *  @endcode
 *
 *  @note This parser can be used to parse JSON as well but it doesn't
 *  interpret JSON types (bool, int, ...) and it doesn't handle strings well.
 *  For example it doesn't know what to do with '\u0013'.
 *
 *  @param CB A callback of the following form.
 *  @code
 *  struct CB {
 *      void element(const_cstring id, const_cstring value)
 *      void begin_block(const_cstring id)
 *      void end_block()
 *      void begin_array(const_cstring id)
 *      void end_array()
 *      void array_element(const_cstring v)
 *      void error(string &&msg)
 *  };
 *  @endcode
 *
 *  @param source The source code to parse, which is not copied and must
 *  remain valid during parsing.
 * */
template <class CB>
inline void parse(CB &&cb, const foundation::const_cstring source)
{
    using namespace foundation;
    hash_map<string, const char *> lookup_table;
    stack<string> block_stack;
    nml_detail::parse(cb, source, lookup_table, block_stack);
}

/** @} */

}} // namespaces

#endif // NIC_D6A066B43404B178_NIC


