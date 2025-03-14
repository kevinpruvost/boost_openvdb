//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//


#include <boost/url/detail/config.hpp>
#include "scheme_rule.hpp"
#include <boost/url/grammar/alpha_chars.hpp>
#include <boost/url/grammar/delim_rule.hpp>
#include <boost/url/grammar/lut_chars.hpp>
#include <boost/url/grammar/parse.hpp>
#include <boost/url/grammar/tuple_rule.hpp>

namespace boost {
namespace urls {
namespace detail {

auto
scheme_rule::
parse(
    char const*& it,
    char const* end) const noexcept ->
        system::result<value_type>
{
    auto const start = it;
    if(it == end)
    {
        // end
        BOOST_URL_RETURN_EC(
            grammar::error::mismatch);
    }
    if(! grammar::alpha_chars(*it))
    {
        // expected alpha
        BOOST_URL_RETURN_EC(
            grammar::error::mismatch);
    }

    static
    constexpr
    grammar::lut_chars scheme_chars(
        "0123456789" "+-."
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz");
    it = grammar::find_if_not(
        it + 1, end, scheme_chars);
    value_type t;
    t.scheme = core::string_view(
        start, it - start);
    t.scheme_id = string_to_scheme(
        t.scheme);
    return t;
}

} // detail
} // urls
} // boost

