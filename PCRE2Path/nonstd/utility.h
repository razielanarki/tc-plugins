//==========================================================================
// nonstd: detection idiom
//==========================================================================

#pragma once

#include <type_traits>
#include <utility>

//--------------------------------------------------------------------------

namespace nonstd
{

//--------------------------------------------------------------------------
// class erased type

inline namespace fundamentals_v3
{

struct erased_type
{
    // not using type = T;
};

}

//--------------------------------------------------------------------------
//

inline namespace deduction_safe_wrapper
{

template<class T>
struct dont_deduce
{
    using type = T;
};

template<class T>
using dont_deduce_t = typename dont_deduce<T>::name;

}

//--------------------------------------------------------------------------
// false value attached to a dependent name (for static_assert)

inline namespace dependent_false
{

template<class...>
constexpr bool always_false = false;

}

//--------------------------------------------------------------------------
// variadic `is_same`:
// for checking if T same as (at least) one of the listed Ts types

inline namespace any_same
{

template <typename Type, typename... TypeList>
using is_any_same = std::disjunction<std::is_same<Type, TypeList>...>;

template <typename Type, typename... TypeList>
constexpr bool is_any_same_v = is_any_same<Type, TypeList...>::value;

}

/** /
//--------------------------------------------------------------------------
//  safe indexed tuple element

inline namespace safe_indexed_tuple_element
{

template <bool valid, int index, class Tuple>
struct safe_tuple_element;

template <int index, class Tuple>
struct safe_tuple_element<false, index, Tuple> { using type = void; };

template <int index, class Tuple>
struct safe_tuple_element<true,  index, Tuple> { using type = std::tuple_element<index, Tuple>::type; };

};
/**/

}
