//
// Created by dougfinl on 10/02/16.
//

#ifndef VISUALISER_MAKE_UNIQUE_H
#define VISUALISER_MAKE_UNIQUE_H

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

// Implements the make_unique function that is missing from C++11.
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3656.htm

namespace std {
    template<class T> struct _Unique_if {
        typedef unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
            return unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename remove_extent<T>::type U;
            return unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;
}

#endif //VISUALISER_MAKE_UNIQUE_H