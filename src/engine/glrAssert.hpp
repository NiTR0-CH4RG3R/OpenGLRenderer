#ifndef GLR_ASSERT_HPP_INCLUDED
#define GLR_ASSERT_HPP_INCLUDED

#include <cassert>

#ifndef NDEBUG
#define ASSERT_IF_DEBUG( call ) assert( call )
#else
#define ASSERT_IF_DEBUG( call ) call
#endif // NDEBUG

#endif // GLR_ASSERT_HPP_INCLUDED
