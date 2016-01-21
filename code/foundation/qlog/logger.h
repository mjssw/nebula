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
#ifndef NIC_E077E3FD789A3483_NIC
#define NIC_E077E3FD789A3483_NIC

#include "formatter/function.h"
#include "sink/function.h"

#include "../format.h"
#include "../exception.h"
#include "../ptr.h"
#include "../async.h"

namespace nebula { namespace foundation { namespace qlog {
//------------------------------------------------------------------------------
template <
    class Formatter = formatter::formatter_base,
    class Sink = sink::sink_base>
class basic_logger : public sink::sink_base
{    
public:
    inline basic_logger()
    : lvl_(level::info)
    {}
    
    template <
        class Formatter_,
        class Sink_,
        class Error_ = std::nullptr_t>
    inline basic_logger(
        Formatter_ &&fmttr,
        Sink_ &&snk,
        Error_ err_h = Error_())
    :   lvl_(level::info),
        error_handler_(foundation::forward<Error_>(err_h))
    {
        formatter_nolock(foundation::forward<Formatter_>(fmttr));
        sink_nolock(foundation::forward<Sink_>(snk));
    }
    
    template <class ... Params>
    inline void log(const level lvl, const Params & ... p) {
        log_(lvl, p...);
    }
    template <class ... Params>
    inline void fatal(const Params & ... p) {
        log_(level::fatal, p...);
    }
    template <class ... Params>
    inline void alert(const Params & ... p) {
        log_(level::alert, p...);
    }
    template <class ... Params>
    inline void critical(const Params & ... p) {
        log_(level::critical, p...);
    }
    template <class ... Params>
    inline void error(const Params & ... p) {
        log_(level::error, p...);
    }
    template <class ... Params>
    inline void warning(const Params & ... p) {
        log_(level::warning, p...);
    }
    template <class ... Params>
    inline void notice(const Params & ... p) {
        log_(level::notice, p...);
    }
    template <class ... Params>
    inline void info(const Params & ... p) {
        log_(level::info, p...);
    }
    template <class ... Params>
    inline void debug(const Params & ... p) {
        log_(level::debug, p...);
    }
    inline void flush() {
        sink_->flush();
    }
    inline void operator () (level lvl, const string &s) {
        log_(lvl, s);
    }
    
    inline void threshold(const level lvl) {
        async::atomic_store(&lvl_, lvl);
    }
    inline level threshold() const {
        return async::atomic_load(&lvl_);
    }
    
    template <class X>
    inline void formatter(X &&x) {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        formatter_nolock(foundation::forward<X>(x));
    }
    inline const intrusive_ptr<Formatter> &formatter() const noexcept {
        return formatter_;
    }
    
    template <class X>
    inline void sink(X &&x) {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        sink_nolock(foundation::forward<X>(x));
    }
    inline const intrusive_ptr<Sink> &sink() const noexcept {
        return sink_;
    }
    
    template <class X>
    inline void error_handler(X &&x) {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        error_handler_ = foundation::forward<X>(x);
    }
    inline function<void (exception_ptr)> error_handler()
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        function<void (exception_ptr)> res = error_handler_;
        return res;
    }
    
    template <
        class Formatter_,
        class Sink_,
        class Error_ = std::nullptr_t>
    inline void reset(
        Formatter_ &&fmttr,
        Sink_ &&snk,
        Error_ err_h)
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        
        formatter_nolock(foundation::forward<Formatter_>(fmttr));
        sink_nolock(foundation::forward<Sink_>(snk));
        error_handler_ = foundation::forward<Error_>(err_h);
    }
    inline void get(
        intrusive_ptr<Formatter> &f,
        intrusive_ptr<Sink> &s,
        function<void (exception_ptr)> &e)
    {
        async::lock(mtx);
        n_scoped_unlock(mtx);
        
        f = formatter_;
        s = sink_;
        e = error_handler_;
    }
    
private:
    template <class ... Params>
    inline void log_(const level lvl, const Params & ... p)
    {
        if(lvl > threshold())
            return;
    
        string str;
        
        try
        {
            intrusive_ptr<Sink> snk;
            intrusive_ptr<Formatter> frmt;
            
            {
                async::lock(mtx);
                n_scoped_unlock(mtx);
                snk = sink_;
                frmt = formatter_;
            }
            
            if(snk)
            {                
                io::msink<string> ss;
                ss.container().reserve(256);
                fmt::fwrite(ss, p ...);
                
                str = foundation::move(ss.container());
                
                if(frmt)
                    frmt->operator () (lvl, str);
                
                snk->operator () (lvl, str);
            }
        }
        catch(...)
        {            
            async::lock(mtx);
            n_scoped_unlock(mtx);
            if(error_handler_)
                error_handler_(current_exception());
            else
            {
                try {
                    fmt::fwrite(io::cerr, "LOGGING ERROR: ", p..., fmt::endl);
                } catch(...) {}
                throw;
            }
        }
    }
    
    template <class X>
    inline void formatter_nolock(intrusive_ptr<X> &&x) {
        this->formatter_ = foundation::move(x);
    }
    template <class X>
    inline void formatter_nolock(const intrusive_ptr<X> &x) {
        this->formatter_ = x;
    }
    template <class X>
    inline void formatter_nolock(intrusive_ptr<X> &x) {
        this->formatter_ = x;
    }
    template <class X>
    inline void formatter_nolock(X *x) {
        this->formatter_ = x;
    }
    inline void formatter_nolock(std::nullptr_t) {
        this->formatter_ = nullptr;
    }
    template <class Func>
    inline void formatter_nolock(Func &&f) {
        formatter_nolock(qlog::formatter::capture(
            foundation::forward<Func>(f)));
    }
    
    template <class X>
    inline void sink_nolock(intrusive_ptr<X> &&x) {
        this->sink_ = foundation::move(x);
    }
    template <class X>
    inline void sink_nolock(const intrusive_ptr<X> &x) {
        this->sink_ = x;
    }
    template <class X>
    inline void sink_nolock(intrusive_ptr<X> &x) {
        this->sink_ = x;
    }
    template <class X>
    inline void sink_nolock(X *x) {
        this->sink_ = x;
    }
    inline void sink_nolock(std::nullptr_t) {
        this->sink_ = nullptr;
    }
    template <class Func>
    inline void sink_nolock(Func &&f) {
        sink_nolock(qlog::sink::capture(
            foundation::forward<Func>(f)));
    }
    
    async::mutex mtx;
    async::atomic<level> lvl_;
    intrusive_ptr<Formatter> formatter_;
    intrusive_ptr<Sink> sink_;
    function<void (exception_ptr)> error_handler_;
};

using logger = basic_logger<>;

}}} // namespaces

#endif // NIC_E077E3FD789A3483_NIC
