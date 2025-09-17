#ifndef XPARSERLIB_VECTOR_HPP
#define XPARSERLIB_VECTOR_HPP


#include <vector>

namespace xparserlib {


    template <class T, class A>
    std::vector<T, A> operator + (const std::vector<T, A>& left, const std::vector<T, A>& right) {
        std::vector<T, A> result;
        result.reserve(left.size() + right.size());
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }


    template <class T, class A>
    std::vector<T, A> operator + (const std::vector<T, A>& left, const T& right) {
        std::vector<T, A> result;
        result.reserve(left.size() + 1);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(right);
        return result;
    }


    template <class T, class A>
    std::vector<T, A> operator + (const T& left, const std::vector<T, A>& right) {
        std::vector<T, A> result;
        result.reserve(1 + right.size());
        result.push_back(left);
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }


} //namespace xparserlib


#endif //XPARSERLIB_VECTOR_HPP
