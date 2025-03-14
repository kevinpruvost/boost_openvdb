//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/url
//


#include <boost/url/detail/config.hpp>
#include <boost/url/detail/config.hpp>
#include <boost/url/grammar/delim_rule.hpp>

namespace boost {
namespace urls {
namespace grammar {

auto
implementation_defined::ch_delim_rule::
parse(
    char const*& it,
    char const* end) const noexcept ->
        system::result<value_type>
{
    if(it == end)
    {
        // end
        BOOST_URL_RETURN_EC(
            error::need_more);
    }
    if(*it != ch_)
    {
        // wrong character
        BOOST_URL_RETURN_EC(
            error::mismatch);
    }
    return core::string_view{
        it++, 1 };
};

} // grammar
} // urls
} // boost

