/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:15:34 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:08:09 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <cstddef>
#include <iterator>

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

	template < class T >
	class random_access_iterator
	{
	public:
		typedef T*															iterator_type;
		typedef typename ft::iterator_traits<T*>::value_type				value_type;
		typedef typename ft::iterator_traits<T*>::difference_type			difference_type;
		typedef typename ft::iterator_traits<T*>::iterator_category			iterator_category;
		typedef typename ft::iterator_traits<T*>::reference					reference;
		typedef typename ft::iterator_traits<T*>::pointer					pointer;
		typedef typename ft::iterator_traits<const T*>::reference			const_reference;
		typedef typename ft::iterator_traits<const T*>::pointer				const_pointer;

		random_access_iterator() {};
		random_access_iterator(iterator_type iterator) : _base(iterator) {}
		random_access_iterator(const random_access_iterator<T>& obj) : _base(obj._base) {}
		random_access_iterator& operator= (const random_access_iterator<T>& obj)
		{
			if (this != &obj)
				_base = obj._base;
			return (*this);
		}
		~random_access_iterator() {};

		friend bool						operator==(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base == i2._base;
		}

		friend bool						operator!=(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base != i2._base;
		}

		friend bool						operator< (const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base < i2._base;
		}

		friend bool						operator> (const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base > i2._base;
		}

		friend bool						operator<=(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base < i2._base;
		}

		friend bool						operator>=(const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base > i2._base;
		}

		friend random_access_iterator	operator+ (difference_type d, const random_access_iterator& other)
		{
			return other + d;
		}
		
		friend difference_type			operator- (const random_access_iterator& i1, const random_access_iterator& i2)
		{
			return i1._base - i2._base;
		}

		reference						operator* ()	const	{ return *this->_base; }
		const_pointer					operator->()	const	{ return this->_base; }
		const_reference					operator[](difference_type d) const { return this->_base[d]; }

		random_access_iterator& 		operator++()				{ ++this->_base; return *this; }
		random_access_iterator& 		operator--()				{ --this->_base; return *this; }
		random_access_iterator	 		operator++(int)				{ random_access_iterator i(*this); ++this->_base ; return i; }
		random_access_iterator	 		operator--(int)				{ random_access_iterator i(*this); --this->_base ; return i; }
			
		random_access_iterator&	 		operator+=(difference_type d)		{ this->_base += d; return *this; }
		random_access_iterator&	 		operator-=(difference_type d)		{ this->_base -= d; return *this; }

		random_access_iterator	 		operator+ (difference_type d) const { return random_access_iterator(this->_base + d); }
		random_access_iterator	 		operator- (difference_type d) const { return random_access_iterator(this->_base - d); }

	private:
		iterator_type	_base;
	};

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
  		reverse_iterator (const reverse_iterator<Iterator>& rev_it) : _base(rev_it.base()) {}
		/*copy oeratpr*/

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

		/*relational operators*/
		friend bool operator== (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs.base() == rhs.base();
		}

		friend bool operator!= (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return !(lhs.base() == rhs.base());
		}

		friend bool operator< (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs.base() > rhs.base();
		}

		friend bool operator<= (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs.base() >= rhs.base();
		}

		friend bool operator> (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs.base() < rhs.base();
		}

		friend bool operator>= (const reverse_iterator& lhs,
								const reverse_iterator& rhs)
		{
			return lhs.base() <= rhs.base();
		}

		/*Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it*/
		friend reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
		{
			reverse_iterator tmp = rev_it + n;
			return tmp;
		}

		/*Returns the distance between lhs and rhs*/
		friend typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
		{
			return rhs.base() - lhs.base();
		}

	protected:
		iterator_type	_base;
	};
}

#endif
