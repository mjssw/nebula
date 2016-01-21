/*--!>
This file is part of Nebula, a multi-purpose library mainly written in C++.

Copyright 2016 lis (lis@tutanota.com)
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
#ifndef NIC_0348AF04415D6825_NIC
#define NIC_0348AF04415D6825_NIC

#include "config.h"
#include "exception.h"

namespace nebula { namespace gpg { namespace detail {
/** @ingroup GPG
 * @{
 * */
//------------------------------------------------------------------------------
namespace keylist_mode
{
    using type = gpgme_keylist_mode_t;
    /** The local keyring should be searched for keys in the keylisting
     *  operation. This is the default.
     * */
    constexpr static type local = GPGME_KEYLIST_MODE_LOCAL;
    /** An external source should be searched for keys in the keylisting
     *  operation. The type of external source is dependant on the crypto
     *  engine used and whether it is combined with local.
     *  For example, it can be a remote keyserver or LDAP certificate server.
     * */
    constexpr static type extern_ = GPGME_KEYLIST_MODE_EXTERN;
    /** The key signatures should be included in the listed keys.
     * */
    constexpr static type sigs = GPGME_KEYLIST_MODE_SIGS;
    /** The signature notations on key signatures should be included in the
     *  listed keys. This only works if sigs is also enabled.
     * */
    constexpr static type sig_notations = GPGME_KEYLIST_MODE_SIG_NOTATIONS;
    /** Returns information about the presence of a corresponding secret key
     *  in a public key listing. A public key listing with this mode is slower
     *  than a standard listing but can be used instead of a second run to list
     *  the secret keys. This is only supported for GnuPG versions >= 2.1.
     * */
    constexpr static type with_secret = GPGME_KEYLIST_MODE_WITH_SECRET;
    /** Specifies that keys flagged as ephemeral are included in the listing.
     * */
    constexpr static type ephemeral = GPGME_KEYLIST_MODE_EPHEMERAL;
};
//------------------------------------------------------------------------------
inline const char *to_cstr(const keylist_mode::type x) noexcept
{
    switch(x)
    {
    case keylist_mode::local: return "local";
    case keylist_mode::extern_: return "extern";
    case keylist_mode::sigs: return "sigs";
    case keylist_mode::sig_notations: return "sig_notations";
    case keylist_mode::with_secret: return "with_secret";
    case keylist_mode::ephemeral: return "ephemeral";
    default: "Dragons!";
    }
}

//------------------------------------------------------------------------------
enum class public_key_algorithm
{
    /** This value indicates the RSA (Rivest, Shamir, Adleman) algorithm. */
    rsa = GPGME_PK_RSA,
    /** This value indicates DSA, the Digital Signature Algorithm. */
    dsa = GPGME_PK_DSA,
    /** This value indicates ElGamal. */
    elg = GPGME_PK_ELG,
    /** This value also indicates ElGamal and is used specifically in GnuPG. */
    elg_e = GPGME_PK_ELG_E,
    /** This value is a generic indicator for ellipic curve algorithms. */
    ecc = GPGME_PK_ECC,
    /** This value indicates ECDSA, the Elliptic Curve Digital Signature
     *  Algorithm as defined by FIPS 186-2 and RFC-6637.
     * */
    ecdsa = GPGME_PK_ECDSA,
    /** This value indicates ECDH, the Eliptic Curve Diffie-Hellmann encryption
     *  algorithm as defined by RFC-6637.
     * */
    ecdh = GPGME_PK_ECDH
};
//------------------------------------------------------------------------------
inline public_key_algorithm to_public_key_algorithm(const gpgme_pubkey_algo_t x)
{
    switch(x)
    {
    case GPGME_PK_RSA:
    case GPGME_PK_DSA:
    case GPGME_PK_ELG:
    case GPGME_PK_ELG_E:
    case GPGME_PK_ECC:
    case GPGME_PK_ECDSA:
    case GPGME_PK_ECDH:
        return static_cast<public_key_algorithm>(x);
    case GPGME_PK_RSA_E:
    case GPGME_PK_RSA_S:
        n_throw(gpg_error)
        << ei_msg_c("Deprecated public key algorithm type.");
    default:
        n_throw(gpg_error)
        << ei_msg_c("Invalid public key algorithm type.");
    }
}
//------------------------------------------------------------------------------
inline const char *to_cstr(const public_key_algorithm x) noexcept
{
    switch(x)
    {
    case public_key_algorithm::rsa: return "rsa";
    case public_key_algorithm::dsa: return "dsa";
    case public_key_algorithm::elg: return "elg";
    case public_key_algorithm::elg_e: return "elg_e";
    case public_key_algorithm::ecc: return "ecc";
    case public_key_algorithm::ecdsa: return "ecdsa";
    case public_key_algorithm::ecdh: return "ecdh";
    default: "Dragons!";
    }
}

//------------------------------------------------------------------------------
enum class hash_algorithm
{
    none = GPGME_MD_NONE,
    md5 = GPGME_MD_MD5,
    sha1 = GPGME_MD_SHA1,
    rmd160 = GPGME_MD_RMD160,
    md2 = GPGME_MD_MD2,
    tiger = GPGME_MD_TIGER,
    haval = GPGME_MD_HAVAL,
    sha256 = GPGME_MD_SHA256,
    sha384 = GPGME_MD_SHA384,
    sha512 = GPGME_MD_SHA512,
    sha224 = GPGME_MD_SHA224,
    md4 = GPGME_MD_MD4,
    crc32 = GPGME_MD_CRC32,
    crc32_rfc1510 = GPGME_MD_CRC32_RFC1510,
    crc32_rfc2440 = GPGME_MD_CRC24_RFC2440
};
//------------------------------------------------------------------------------
inline hash_algorithm to_hash_algorithm(const gpgme_hash_algo_t x)
{
    switch(x)
    {
    case GPGME_MD_NONE:
    case GPGME_MD_MD5:
    case GPGME_MD_SHA1:
    case GPGME_MD_RMD160:
    case GPGME_MD_MD2:
    case GPGME_MD_TIGER:
    case GPGME_MD_HAVAL:
    case GPGME_MD_SHA256:
    case GPGME_MD_SHA384:
    case GPGME_MD_SHA512:
    case GPGME_MD_SHA224:
    case GPGME_MD_MD4:
    case GPGME_MD_CRC32:
    case GPGME_MD_CRC32_RFC1510:
    case GPGME_MD_CRC24_RFC2440:
        return static_cast<hash_algorithm>(x);
    default:
        n_throw(gpg_error)
        << ei_msg_c("Invalid hash algorithm type.");
    }
}
//------------------------------------------------------------------------------
inline const char *to_cstr(const hash_algorithm x) noexcept
{
    switch(x)
    {
    case hash_algorithm::md5: return "md5";
    case hash_algorithm::sha1: return "sha1";
    case hash_algorithm::rmd160: return "rmd160";
    case hash_algorithm::tiger: return "tiger";
    case hash_algorithm::haval: return "haval";
    case hash_algorithm::sha256: return "sha256";
    case hash_algorithm::sha384: return "sha384";
    case hash_algorithm::sha512: return "sha512";
    case hash_algorithm::sha224: return "sha224";
    case hash_algorithm::md4: return "md4";
    case hash_algorithm::crc32: return "crc32";
    case hash_algorithm::crc32_rfc1510: return "crc32_rfc1510";
    case hash_algorithm::crc32_rfc2440: return "crc32_rfc2440";
    default: "Dragons!";
    }
}

/** @} */

}}} // namespaces

#endif // NIC_0348AF04415D6825_NIC

