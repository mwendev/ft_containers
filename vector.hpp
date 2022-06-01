/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:06:53 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:24:30 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "util.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> > //prior to C++11, there must be a space betweem '>>'
	class vector
	{
	public:

		/*making alias of member types(= data types)*/
		typedef T																	value_type;
		typedef Alloc																allocator_type;
		typedef typename Alloc::reference											reference;
		typedef typename Alloc::const_reference										const_reference;
		typedef typename Alloc::pointer												pointer;
		typedef typename Alloc::const_pointer										const_pointer;
		typedef typename ft::random_access_iterator<T>								iterator;
		typedef typename ft::random_access_iterator<const T>						const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type				difference_type;
		typedef size_t																size_type;

	protected:
		/*declare variables for functions to use*/
		allocator_type																_allocator;
		size_type																	_capacity;
		size_type																	_size;
		pointer																		_p;

		size_type&	get_capacity() { return _capacity; };

	public:
		/*default constructor*/
		explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _capacity(0), _size(0), _p(0) {}

		/*fill constructor*/
		vector (size_type n, const value_type& val = value_type(), 
			const allocator_type& alloc = allocator_type()) : _allocator(alloc), _capacity(n), _size(0), _p(_allocator.allocate(n))
		{
			while (_size < n)
			{
				_allocator.construct(_p + _size, val);
				++_size;
			}
		}

		/*range constructor*/
		template <class InputIterator>
		vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type()) : _allocator(alloc), _capacity(0), _size(0), _p(0)
		{
			range_construct(first, last, typename ft::is_integral<InputIterator>::type());
		}

		/*copy constructor*/
		vector (const vector& x) : _allocator(x._allocator), _capacity(x.capacity()), _size(0), _p(_allocator.allocate(x.capacity()))
		{
			for (size_type i = 0; i < x.size(); i++)
			{
				_allocator.construct(_p + _size, x._p[i]);
				++_size;
			}
		}

		/*destructor*/
		~vector()
		{
			while (_size != 0)
				pop_back();
			_allocator.deallocate(_p, _capacity);
		}

		/*Copy assign operator*/
		vector&	operator= (const vector& x)
		{
			if (this != &x)
			{
				while (_size != 0)
					pop_back();
				_allocator.deallocate(_p, _capacity);
				_p = _allocator.allocate(x._capacity);
				_capacity = x._capacity;
				for (size_type i = 0; i < x.size(); i++)
				{
					_allocator.construct(_p + _size, x._p[i]);
					++_size;
				}
			}
			return (*this);
		}

		/*Iterators*/
		iterator				begin()
		{
			return (iterator(_p));
		}

		const_iterator			begin() const
		{
			return (const_iterator(_p));
		}

		iterator				end()
		{
			return (iterator(_p + _size));
		}

		const_iterator			end() const
		{
			return (const_iterator(_p + _size));
		}

		reverse_iterator		rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator		rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		/*Capacity*/
		size_type				size() const
		{
			return _size;
		}

		size_type				max_size() const
		{
			return _allocator.max_size();
		}

		void					resize(size_type n, value_type val = value_type())
		{
			if (n > _capacity * 2)
				this->reserve(n);
			else if (n > _capacity)
				this->reserve(_capacity * 2);
			while (n < _size)
				erase(this->end());
			while (n > _size)
				insert(this->end(), val);
		}

		size_type				capacity() const
		{
			return _capacity;
		}

		bool					empty() const
		{
			return (_size == 0);
		}

		void					reserve (size_type n)
		{
			if (n > _capacity)
			{
				vector tmp;
				tmp._p = tmp._allocator.allocate(n);
				tmp._capacity = n;
				for (size_type i = 0; i < this->size(); i++)
				{
					tmp._allocator.construct(tmp._p + i, _p[i]);
					++tmp._size;
				}
				swap(tmp);
			}
		}

		/*Element access*/
		reference				operator[] (size_type n)
		{
			return (*(_p + n));
		}

		reference				at (size_type n) //protected operator[]
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return (_p[n]);
		}

		const_reference			at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return (_p[n]);
		}

		reference				front()
		{
			return *_p;
		}

		const_reference			front() const
		{
			return *_p;
		}

		reference				back()
		{
			return *(_p + _size - 1);
		}

		const_reference			back() const
		{
			return *(_p + _size - 1);
		}

		/*Modifiers*/
		void					push_back (const value_type& val)
		{
			if (_capacity == _size)
			{
				if (!_capacity)
					reserve(1);
				else
					reserve(_capacity * 2);
			}
			_allocator.construct(_p + _size, val);
			++_size;
		}

		template <class InputIterator>
		void					assign (InputIterator first, InputIterator last)
		{
			range_assign(first, last, typename ft::is_integral<InputIterator>::type());
		}

		void					assign (size_type n, const value_type& val)
		{
			size_type	capacity = _capacity;

			if (!capacity)
				capacity = n;
			clear();
			_allocator.deallocate(_p, _capacity);
			_capacity = capacity;
			_p = _allocator.allocate(capacity);
			while (_size < n)
			{
				_allocator.construct(_p + _size, val);
				++_size;
			}
		}

		void					swap (vector& x)
		{
			size_type capacity = _capacity;
			size_type size = _size;
			pointer p = _p;

			this->_capacity = x._capacity;
			this->_size = x._size;
			this->_p = x._p;

			x._capacity = capacity;
			x._size = size;
			x._p = p;
		}

		void					pop_back()
		{
			if (_size == 0)
				return ;
			if (_p)
			{
				_allocator.destroy(_p + _size - 1);
				--_size;
			}
		}

		iterator				insert (iterator position, const value_type& val)
		{
			vector		tmp;
			size_type	distance = position - this->begin();

			if (distance < 0)
				return position;
			if (distance < _capacity)
			{
				tmp._p = tmp._allocator.allocate(_capacity);
				tmp._capacity = _capacity;
			}
			else if (distance >= _capacity)
			{
				tmp._p = tmp._allocator.allocate(_capacity * 2);
				tmp._capacity = _capacity * 2;
			}
			else if (distance > _capacity * 2)
			{
				tmp._p = tmp._allocator.allocate(distance);
				tmp._capacity = distance;
			}
			for (size_type i = 0; i < distance; i++)
			{
				if (i < this->size())
					_allocator.construct(tmp._p + i, _p[i]);
				++tmp._size;
			}
			tmp._allocator.construct(tmp._p + distance, val);
			for (size_t i = distance; i < this->size(); i++)
			{
				tmp._allocator.construct(tmp._p + i + 1, _p[i]);
				++tmp._size;
			}
			tmp._size += 1;
			swap(tmp);
			return _p + distance;
		}

		void					insert (iterator position, size_type n, const value_type& val)
		{
			vector		tmp;
			size_type	distance = position - this->begin();

			if (distance < 0 || !n)
				return ;
			if (distance + n <= _capacity)
			{
				tmp._p = tmp._allocator.allocate(_capacity);
				tmp._capacity = _capacity;
			}
			else if (distance + n > _capacity)
			{
				tmp._p = tmp._allocator.allocate(_capacity * 2);
				tmp._capacity = _capacity * 2;
			}
			else if (distance + n > _capacity * 2)
			{
				tmp._p = tmp._allocator.allocate(distance);
				tmp._capacity = distance;
			}
			for (size_type i = 0; i < distance; i++)
			{
				if (i < this->size())
					_allocator.construct(tmp._p + i, _p[i]);
				++tmp._size;
			}
			for (size_t i = 0; i < n; i++)
				tmp._allocator.construct(tmp._p + distance + i, val);
			for (size_t i = distance; i < this->size(); i++)
			{
				tmp._allocator.construct(tmp._p + i + n, _p[i]);
				++tmp._size;
			}
			tmp._size += n;
			swap(tmp);
		}

		template <class InputIterator>
		void					insert (iterator position, InputIterator first, InputIterator last)
		{
			range_insert(position, first, last, typename ft::is_integral<InputIterator>::type());
		}

		iterator				erase(iterator position)
		{
			vector		tmp;
			size_type	distance = position - this->begin();

			tmp._capacity = _capacity;
			tmp._p = tmp._allocator.allocate(_capacity);
			for (size_t i = 0; i < this->size() - 1; i++)
			{
				if (i < distance)
				{
					tmp._allocator.construct(tmp._p + i, _p[i]);
					++tmp._size;
				}
				else
				{
					tmp._allocator.construct(tmp._p + i, _p[i + 1]);
					++tmp._size;
				}
			}
			swap(tmp);
			return (_p + distance);
		}

		void					clear()
		{
			while (_size)
				pop_back();
		}

		/*Allocator*/
		allocator_type			get_allocator() const
		{
			return (_allocator);
		}

	private:
		/*For int protection*/
		template <class InputIterator>
		void					range_construct (InputIterator first, InputIterator last, ft::true_type)
		{
			_capacity = (size_t)first;
			_p = _allocator.allocate(first);
			while (_size < (size_t)first)
			{
				_allocator.construct(_p + _size, last);
				++_size;
			}
		}

		template <class InputIterator>
		void					range_construct (InputIterator first, InputIterator last, ft::false_type)
		{
			size_type	distance = static_cast<size_type>(std::distance<InputIterator>(first, last));
			_capacity = distance;
			_p = _allocator.allocate(distance);
			for (InputIterator it = first; it != last; it++)
			{
				_allocator.construct(_p + _size, *it);
				++_size;
			}
		}

		template <class InputIterator>
		void					range_assign (InputIterator first, InputIterator last, ft::true_type)
		{
			size_type	capacity = _capacity;

			if (!capacity)
				capacity = (size_t)first;
			clear();
			_allocator.deallocate(_p, _capacity);
			_capacity = capacity;
			_p = _allocator.allocate(capacity);
			while (_size < (size_t)first)
			{
				_allocator.construct(_p + _size, last);
				++_size;
			}
		}

		template <class InputIterator>
		void					range_assign (InputIterator first, InputIterator last, ft::false_type)
		{
			clear();
			_allocator.deallocate(_p, _capacity);
			range_construct(first, last, typename ft::is_integral<InputIterator>::type());
		}

		template<class InputIterator>
		void					range_insert(iterator position, InputIterator first, InputIterator last, ft::true_type)
		{
			vector		tmp;
			size_type	distance = position - this->begin();

			if (distance < 0 || !first)
				return ;
			if (distance + first <= _capacity)
			{
				tmp._p = tmp._allocator.allocate(_capacity);
				tmp._capacity = _capacity;
			}
			else if (distance + first > _capacity)
			{
				tmp._p = tmp._allocator.allocate(_capacity * 2);
				tmp._capacity = _capacity * 2;
			}
			else if (distance + first > _capacity * 2)
			{
				tmp._p = tmp._allocator.allocate(distance);
				tmp._capacity = distance;
			}
			for (size_type i = 0; i < distance; i++)
			{
				if (i < this->size())
					_allocator.construct(tmp._p + i, _p[i]);
				++tmp._size;
			}
			for (int i = 0; i < first; i++)
				tmp._allocator.construct(tmp._p + distance + i, last);
			for (size_t i = distance; i < this->size(); i++)
			{
				tmp._allocator.construct(tmp._p + i + first, _p[i]);
				++tmp._size;
			}
			tmp._size += first;
			swap(tmp);
		}

		template<class InputIterator>
		void					range_insert(iterator position, InputIterator first, InputIterator last, ft::false_type)
		{
			vector		tmp;
			size_type	distance = position - this->begin();
			size_type	n = last - first;

			if (distance < 0)
				return ;
			tmp._capacity = _capacity;
			tmp._p = tmp._allocator.allocate(_capacity);
			for (size_type i = 0; i < distance; i++)
			{
				if (i < this->size())
					_allocator.construct(tmp._p + i, _p[i]);
				++tmp._size;
			}
			if (n > _capacity - _size && n <= _capacity * 2 - _size)
				tmp.reserve(_capacity * 2);
			else if (n > _capacity - _size && n > _capacity * 2 - _size)
				tmp.reserve(_capacity + n);
			for (size_t i = 0; i < n; i++)
				tmp._allocator.construct(tmp._p + distance + i, *(first + 1));
			for (size_t i = distance; i < this->size(); i++)
			{
				tmp._allocator.construct(tmp._p + i + n, _p[i]);
				++tmp._size;
			}
			tmp._size += n;
			swap(tmp);
		}
	};

	/*Non-member function overloads*/
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs > lhs);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

}
#endif
