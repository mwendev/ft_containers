/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:15:34 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 15:46:40 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include "util.hpp"

namespace ft
{
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t									difference_type;
		typedef T											value_type;
		typedef const T*									pointer;
		typedef const T&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template<typename _Iterator, typename _Container>
	class __normal_iterator
	{
	protected:
		_Iterator _M_current;

	public:
		typedef typename ft::iterator_traits<_Iterator>::value_type				value_type;
		typedef typename ft::iterator_traits<_Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<_Iterator>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<_Iterator>::reference				reference;
		typedef typename ft::iterator_traits<_Iterator>::pointer				pointer;

		__normal_iterator() : _M_current(_Iterator()) {}
		explicit __normal_iterator(const _Iterator& __i) : _M_current(__i) {}
		// Allow iterator to const_iterator conversion
		template<typename _Iter, typename _Cont>
		__normal_iterator(const __normal_iterator<_Iter, _Cont>& __i) : _M_current(__i.base()) {}
		// __normal_iterator(const __normal_iterator<_Iter, typename ft::enable_if<(ft::__are_same<_Iter, typename _Container::pointer>::__value), _Container>::__type>& __i) : _M_current(__i.base()) {}
		// template<typename _Iter>
		// __normal_iterator &operator=(const __normal_iterator& __i) { _M_current = __i.base(); return *this; }

		reference						operator*() const	{ return *_M_current; }
		pointer							operator->() const	{ return _M_current; }
		reference						operator[](const difference_type& __n) const { return _M_current[__n]; }

		__normal_iterator&				operator++()				{ ++_M_current; return *this; }
		__normal_iterator&				operator--()				{ --_M_current; return *this; }
		__normal_iterator				operator++(int)				{ return __normal_iterator(_M_current++); }
		__normal_iterator				operator--(int)				{ return __normal_iterator(_M_current--); }
			
		__normal_iterator&				operator+=(const difference_type& __n)	{ _M_current += __n; return *this; }
		__normal_iterator&				operator-=(const difference_type& __n)	{ _M_current -= __n; return *this; }

		__normal_iterator				operator+ (const difference_type& __n) const { return __normal_iterator(_M_current + __n); }
		__normal_iterator				operator- (const difference_type& __n) const { return __normal_iterator(_M_current - __n); }

		const _Iterator&				base() const { return _M_current; }
	};
	
	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator==(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() == __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline bool operator==(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() == __rhs.base(); }

	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator!=(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() != __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline bool operator!=(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() != __rhs.base(); }

	// Random access iterator requirements
	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator<(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() < __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline bool operator<(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() < __rhs.base(); }

	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator>(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() > __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline bool operator>(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() > __rhs.base(); }

	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator<=(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() <= __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline bool operator<=(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() <= __rhs.base(); }

	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline bool operator>=(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() >= __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline bool operator>=(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() >= __rhs.base(); }

	template<typename _IteratorL, typename _IteratorR, typename _Container>
	inline typename __normal_iterator<_IteratorL, _Container>::difference_type
	operator-(const __normal_iterator<_IteratorL, _Container>& __lhs, const __normal_iterator<_IteratorR, _Container>& __rhs)
	{ return __lhs.base() - __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline typename __normal_iterator<_Iterator, _Container>::difference_type
	operator-(const __normal_iterator<_Iterator, _Container>& __lhs, const __normal_iterator<_Iterator, _Container>& __rhs)
	{ return __lhs.base() - __rhs.base(); }

	template<typename _Iterator, typename _Container>
	inline __normal_iterator<_Iterator, _Container>
	operator+(typename __normal_iterator<_Iterator, _Container>::difference_type
	__n, const __normal_iterator<_Iterator, _Container>& __i)
	{ return __normal_iterator<_Iterator, _Container>(__i.base() + __n); }

	template <class Iterator>
	class reverse_iterator
	{
	public:
		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		/*default constructor*/
		reverse_iterator() : _base() {}
		/*initialization constructor*/
		explicit reverse_iterator (iterator_type it) : _base(it) {}
		/*copy / type-cast constructor*/
		template<typename Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}


		iterator_type	base() const { return this->_base; }
		
		/*member function to dereference the iterator*/
		reference operator*() const
		{
			iterator_type ref = _base;
			--ref;
			return *ref;
		}

		/*member function to return the iterator pointing to the element located n positions away*/
		reverse_iterator operator+ (difference_type n) const
		{
			return reverse_iterator(_base - n);
		}

		/*pre-increment*/
		reverse_iterator& operator++ ()
		{
			--_base;
			return *this;
		}

		/*post-increment*/
		reverse_iterator operator++ (int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator& operator+= (difference_type n)
		{
			_base -= n;
			return *this;
		}

		reverse_iterator operator- (difference_type n) const
		{
			return reverse_iterator(_base + n);
		}

		reverse_iterator& operator-- ()
		{
			++_base;
			return *this;
		}

		reverse_iterator operator-- (int)
		{
			reverse_iterator tmp = *this;
			++this->_base;
			return tmp;
		}

		reverse_iterator& operator-= (difference_type n)
		{
			_base += n;
			return *this;
		}

		pointer operator->() const
		{
			return &(operator*());
		}
		
		reference operator[] (difference_type n) const
		{
			return *((*this) + n); 
		}

	protected:
		iterator_type	_base;
	};
	template<typename _Iterator>
	inline bool operator==(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return __x.base() == __y.base(); }
	template<typename _Iterator>
	inline bool operator<(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return __y.base() < __x.base(); }
	template<typename _Iterator>
	inline bool operator!=(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return !(__x == __y); }

	template<typename _Iterator>
	inline bool operator>(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return __y < __x; }

	template<typename _Iterator>
	inline bool operator<=(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return !(__y < __x); }

	template<typename _Iterator>
	inline bool operator>=(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return !(__x < __y); }

	template<typename _Iterator>
	inline typename reverse_iterator<_Iterator>::difference_type
	operator-(const reverse_iterator<_Iterator>& __x, const reverse_iterator<_Iterator>& __y)
	{ return __y.base() - __x.base(); }

	template<typename _Iterator>
	inline reverse_iterator<_Iterator>
	operator+(typename reverse_iterator<_Iterator>::difference_type __n, const reverse_iterator<_Iterator>& __x)
	{ return reverse_iterator<_Iterator>(__x.base() - __n); }

	//comparison of non const and const
	template<typename _IteratorL, typename _IteratorR>
	inline bool operator==(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return __x.base() == __y.base(); }

	template<typename _IteratorL, typename _IteratorR>
	inline bool operator<(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return __y.base() < __x.base(); }

	template<typename _IteratorL, typename _IteratorR>
	inline bool operator!=(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return !(__x == __y); }

	template<typename _IteratorL, typename _IteratorR>
	inline bool operator>(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return __y < __x; }

	template<typename _IteratorL, typename _IteratorR>
	inline bool operator<=(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return !(__y < __x); }

	template<typename _IteratorL, typename _IteratorR>
	inline bool operator>=(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return !(__x < __y); }

	template<typename _IteratorL, typename _IteratorR>
	inline typename reverse_iterator<_IteratorL>::difference_type
	operator-(const reverse_iterator<_IteratorL>& __x, const reverse_iterator<_IteratorR>& __y)
	{ return __y.base() - __x.base(); }
}

#endif
