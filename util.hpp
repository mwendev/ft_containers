/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:12:03 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 15:01:35 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_HPP
# define UTIL_HPP

#include <iostream>

namespace ft
{
	// template<typename _Tp>
	// struct __is_empty_
	// { 
	// private:
	// 	template<typename>
	// 		struct __first { };
	// 	template<typename _Up>
	// 		struct __second : public _Up { };
	// public:
	// 	enum { __value = sizeof(__first<_Tp>) == sizeof(__second<_Tp>)};
	// };

	// template<typename _Alloc, bool = __is_empty_(_Alloc)>
	// struct __alloc_swap
	// {
	// 	static void _S_do_it(const _Alloc&, const _Alloc&) { }
	// };

	// template<typename _Alloc>
	// struct __alloc_swap<_Alloc, false>
	// {
	// 	static void _S_do_it(const _Alloc& __one, const _Alloc& __two)
	// 	{ if (__one != __two)
	// 		std::swap(__one, __two); }
	// };

	template <bool, typename>
	struct enable_if
	{	};

	template <class T>
	struct enable_if <true, T>
	{ typedef T type; };

	struct __true_type {};
	struct __false_type {};

	template<typename, typename>
	struct __are_same
	{
		enum { __value = 0 };
		typedef __false_type __type;
	};

	template<typename _Tp>
	struct __are_same<_Tp, _Tp>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<typename _Tp>
	struct __is_integer
	{
		enum { __value = 0 };
		typedef __false_type __type;
	};

	template<>
	struct __is_integer<bool>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<char>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<signed char>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned char>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<short>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned short>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<int>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned int>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<long long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template<>
	struct __is_integer<unsigned long long>
	{
		enum { __value = 1 };
		typedef __true_type __type;
	};

	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	template <class T, T v> const
	T integral_constant<T, v>::value;

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T> struct is_integral : public false_type { };

	template <> struct is_integral<bool> : public true_type { };
	template <> struct is_integral<char> : public true_type { };
	template <> struct is_integral<unsigned char> : public true_type { };
	template <> struct is_integral<signed char> : public true_type { };
	template <> struct is_integral<short> : public true_type { };
	template <> struct is_integral<unsigned short> : public true_type { };
	template <> struct is_integral<int> : public true_type { };
	template <> struct is_integral<unsigned int> : public true_type { };
	template <> struct is_integral<long long> : public true_type { };
	template <> struct is_integral<unsigned long long> : public true_type { };

	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		
		T1 first;
		T2 second;
		
		pair() : first(), second() {}
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}
		pair& operator= (const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}
	};

	template <typename T1, typename T2>
	inline bool operator== (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj1.first == obj2.first && obj1.second == obj2.second;
	}

	template <typename T1, typename T2>
	inline bool operator!= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj1 == obj2);
	}

	template <typename T1, typename T2>
	inline bool operator< (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj1.first < obj2.first \
			|| (!(obj2.first < obj1.first) && obj1.second < obj2.second );
	}

	template <typename T1, typename T2>
	inline bool operator> (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return obj2 < obj1;
	}

	template <typename T1, typename T2>
	inline bool operator<= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj2 < obj1);
	}

	template <typename T1, typename T2>
	inline bool operator>= (const pair<T1, T2>& obj1, const pair<T1, T2>& obj2)
	{
		return !(obj1 < obj2);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (ft::pair<T1,T2>(x,y));
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first1))
				return false; 
		}
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class _Arg, class _Result>
	struct unary_function {
		typedef _Arg argument_type;
		typedef _Result result_type;
	};

	template <class _Pair>
	struct _Select1st : public unary_function<_Pair, typename _Pair::first_type> {
		typename _Pair::first_type& operator()(_Pair& __x) const {
			return __x.first;
		}
		const typename _Pair::first_type& operator()(const _Pair& __x) const {
			return __x.first;
		}
	};

	template<typename _Tp>
	struct _Identity : public unary_function<_Tp,_Tp>
	{
		_Tp&
		operator()(_Tp& __x) const { return __x; }

		const _Tp&
		operator()(const _Tp& __x) const { return __x; }
	};

}

#endif
