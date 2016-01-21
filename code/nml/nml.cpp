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
#include "nml.h"

namespace nebula { namespace nml { namespace nml_detail {
//------------------------------------------------------------------------------
inline const_cstring eat_white(const const_cstring s) noexcept
{
    const char *i = s.begin();
    for( ; i < s.end(); ++i)
    {
        switch(*i)
        {
        case ' ':
        case '\n':
        case '\t':
        case ',':
            continue;
        default: break;
        }
        
        break;
    }
    
    return const_cstring(i, s.end());
}
//------------------------------------------------------------------------------
inline const_cstring eat_comment(const const_cstring s) noexcept
{
    const char *i = s.begin();
    if(i == s.end())
        return s;
    if(s.size() > 1)
    {
        if(s[0]=='/')
        {
            if(s[1]=='/')
            {
                const char *j = s.begin()+2;
                for( ; j < s.end(); ++j)
                    if(*j == '\n')
                        return const_cstring(j+1, s.end());
                return const_cstring(s.end(), s.end());
            }
            else if(s[1]=='*')
            {
                if(s.size() < 4)
                    return s;
                
                const char *j = s.begin()+2;
                for( ; j < s.end(); ++j)
                {
                    if(*j == '*')
                    {
                        ++j;
                        if(j == s.end())
                            return s;
                        if(*j == '/')
                            return const_cstring(j+1, s.end());
                    }
                }
            }
        }
    }
    return s;
}
//------------------------------------------------------------------------------
inline const_cstring eat(const const_cstring s) noexcept
{
    const_cstring res = s;
    while(!res.empty())
    {
        const char *tmp = res.begin();
        res = eat_comment(eat_white(res));
        if(tmp == res.begin())
            break;
    }
    return res;
}
//------------------------------------------------------------------------------
template <char Q>
inline tuple<token, const char *> lex_string(const_cstring s) noexcept
{
    n_assert(!s.empty());
    
    for(const char *i = s.begin(); i < s.end(); ++i)
    {
        if(*i == '\\')
        {
            if(++i == s.end())
                break;
        }
        else if(*i == Q)
            return make_tuple(token{token_category::string,
                const_cstring(s.begin(), i)}, i+1);
    }
    return make_tuple(token{token_category::unexpected,
        const_cstring(s.begin()-1, s.begin()-1)}, s.end());
}
//------------------------------------------------------------------------------
inline bool test_char(const char c) noexcept
{
    switch(c)
    {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '_':
    case '-':
    case '+':
    case '.':
        return true;
    default:
        return false;
    }
}
//------------------------------------------------------------------------------
inline tuple<token, const char *> lex_id(const_cstring s) noexcept
{
    n_assert(!s.empty());
    
    const char *i = s.begin();
    
    if(!test_char(*i))
        return make_tuple(token{token_category::unexpected, s}, s.end());
    
    while(++i != s.end())
    {
        if(!test_char(*i))
            return make_tuple(
                token{token_category::id, const_cstring(s.begin(), i)}, i); 
    }
    
    return make_tuple(token{token_category::eof, s}, s.end());
}
//------------------------------------------------------------------------------
tuple<token, const char *> lex(
    const_cstring s, const bool eat_white_) noexcept
{
    if(eat_white_)
        s = eat(s);
    
    if(s.empty())
        return make_tuple(token{token_category::eof, s}, s.end());
    
    switch(s.front())
    {
    case ':':
    case '=':
        return make_tuple(token{token_category::assignment,
            const_cstring(s.begin(), s.begin()+1)}, s.begin()+1);
    case '{':
        return make_tuple(token{token_category::lbrace,
            const_cstring(s.begin(), s.begin()+1)}, s.begin()+1);
    case '}':
        return make_tuple(token{token_category::rbrace,
            const_cstring(s.begin(), s.begin()+1)}, s.begin()+1);
    case '[':
        return make_tuple(token{token_category::lbracket,
            const_cstring(s.begin(), s.begin()+1)}, s.begin()+1);
    case ']':
        return make_tuple(token{token_category::rbracket,
            const_cstring(s.begin(), s.begin()+1)}, s.begin()+1);
    case '$':
        return make_tuple(token{token_category::dollar,
            const_cstring(s.begin(), s.begin()+1)}, s.begin()+1);
    case '\"':
        return lex_string<'\"'>(const_cstring(s.begin()+1, s.end()));
    case '\'':
        return lex_string<'\''>(const_cstring(s.begin()+1, s.end()));
    default:
        return lex_id(s);
    }
}

//------------------------------------------------------------------------------
const char *cat_to_str(const token_category x) noexcept
{
    switch(x)
    {
    case token_category::assignment: return "'=' ':' ";
    case token_category::lbrace: return "'{' ";
    case token_category::rbrace: return "'}' ";
    case token_category::lbracket: return "'[' ";
    case token_category::rbracket: return "']' ";
    case token_category::id: return "<id> ";
    case token_category::string: return "<string> ";
    case token_category::dollar: return "'$' ";
    case token_category::eof: return "<eof> ";
    default: return "<unexpected> ";
    }
}

//------------------------------------------------------------------------------
inline tuple<size_t, const char *, const char *> find_line(
    const const_cstring data, const char *pos)
{
    size_t line = 1;
    const char *line_start = data.data();
    for(const char *i = data.begin(); i < pos; ++i)
    {
        if(*i == '\n')
        {
            ++line;
            line_start = i+1;
        }
    }
    const char *line_end = data.end();
    for(const char *i = pos; i < data.end(); ++i)
    {
        if(*i == '\n')
        {
            line_end = i;
            break;
        }
    }
    
    return make_tuple(line, line_start, line_end);
}
//------------------------------------------------------------------------------
string source_extract(const const_cstring data, const char *pos)
{
    size_t line;
    const char *line_start;
    const char *line_end;
    
    tie(line, line_start, line_end) = find_line(data, pos);
    const size_t col = (pos - line_start) + 1;
    
    if(line_end - line_start > 80)
    {
        if(pos - line_start > 40)
        {
            line_start = pos - 40;
            if(line_end - line_start > 80)
                line_end = line_start + 80;
        }
        else
        {
            line_end = pos + (80 - (pos-line_start));
        }
    }
    
    io::msink<string> ss;
    
    fmt::fwrite(ss, "line ", line, " column ", col, fmt::endl);
    fmt::fwrite(ss, const_cstring(line_start, line_end), fmt::endl);
    
    for(const char *i = line_start; i < pos; ++i)
        ss.container().push_back('.');
    ss.container().push_back('^');
    
    return move(ss.container());
}

}}} // namespaces


