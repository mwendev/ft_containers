/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:06:53 by mwen              #+#    #+#             */
/*   Updated: 2022/06/05 12:56:57 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <algorithm>
#include <new>
#include "iterator.hpp"
#include "util.hpp"
#include <iostream>

namespace ft
{
	template<typename _Tp, typename _Alloc>
	struct _Vector_base
	{
		typedef typename _Alloc::template rebind<_Tp>::other _Tp_alloc_type;
		
		struct _Vector_impl : public _Tp_alloc_type
		{
			typename _Tp_alloc_type::pointer _M_start;
			typename _Tp_alloc_type::pointer _M_finish;
			typename _Tp_alloc_type::pointer _M_end_of_storage;

			_Vector_impl() : _Tp_alloc_type(), _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
			_Vector_impl(_Tp_alloc_type const& __a) : _Tp_alloc_type(__a), _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
		};
		
	public:
		typedef _Alloc			allocator_type;
		_Tp_alloc_type&			_M_get_Tp_allocator() { return *static_cast<_Tp_alloc_type*>(&this->_M_impl); }
		const _Tp_alloc_type&	_M_get_Tp_allocator() const { return *static_cast<const _Tp_alloc_type*>(&this->_M_impl); }

		allocator_type			get_allocator() const;

		_Vector_impl	_M_impl;
		typename _Tp_alloc_type::pointer	_M_allocate(size_t __n) { return __n != 0 ? _M_impl.allocate(__n) : 0; }
		void								_M_deallocate(typename _Tp_alloc_type::pointer __p, size_t __n)
		{
			if (__p)
				_M_impl.deallocate(__p, __n);
		}

		_Vector_base() : _M_impl() {}
		_Vector_base(const allocator_type& __a) : _M_impl(__a) {}
		_Vector_base(size_t __n) : _M_impl()
		{
			this->_M_impl._M_start = this->_M_allocate(__n);
			this->_M_impl._M_finish = this->_M_impl._M_start;
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
		}
		_Vector_base(size_t __n, const allocator_type& __a) : _M_impl(__a)
		{
			this->_M_impl._M_start = this->_M_allocate(__n);
			this->_M_impl._M_finish = this->_M_impl._M_start;
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
		}
		~_Vector_base() { _M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);}
	};

	template < class _Tp, class _Alloc = std::allocator<_Tp> > //prior to C++11, there must be a space betweem '>>'
	class vector : protected _Vector_base<_Tp, _Alloc>
	{
		typedef typename	_Alloc::value_type										_Alloc_value_type;
		typedef				_Vector_base<_Tp, _Alloc>								_Base;
		typedef typename	_Base::_Tp_alloc_type									_Tp_alloc_type;
	public:

		/*making alias of member types(= data types)*/
		typedef _Tp																	value_type;
		typedef _Alloc																allocator_type;
		typedef typename _Tp_alloc_type::reference									reference;
		typedef typename _Tp_alloc_type::const_reference							const_reference;
		typedef typename _Tp_alloc_type::pointer									pointer;
		typedef typename _Tp_alloc_type::const_pointer								const_pointer;
		typedef typename ft::__normal_iterator<pointer, vector>						iterator;
		typedef typename ft::__normal_iterator<const_pointer, vector>				const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef ptrdiff_t															difference_type;
		typedef size_t																size_type;

	protected:
		/*declare variables for functions to use*/
		using _Base::_M_allocate;
		using _Base::_M_deallocate;
		using _Base::_M_impl;
		using _Base::_M_get_Tp_allocator;

		template<typename _ForwardIterator, typename _Allocator>
		void					_Destroy(_ForwardIterator __first, _ForwardIterator __last, _Allocator& __alloc)
		{
			for (; __first != __last; ++__first)
				__alloc.destroy(reinterpret_cast<_Tp*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(*__first))));
		}
		template<typename _InputIterator, typename _ForwardIterator, typename _Allocator>
		_ForwardIterator		__uninitialized_copy_a(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, _Allocator& __alloc)
		{
			_ForwardIterator __cur = __result;
			try
			{
				for (; __first != __last; ++__first, ++__cur)
					__alloc.construct(&*__cur, *__first);
				return __cur;
			}
			catch(...)
			{
				_Destroy(__result, __cur, __alloc);
				throw std::bad_alloc();
			}
		}
		template<typename _ForwardIterator, typename _Size, typename _Allocator>
		void					__uninitialized_default_n_a(_ForwardIterator __first, _Size __n, _Allocator& __alloc)
		{
			_ForwardIterator __cur = __first;
			try
			{
				for (; __n > 0; --__n, ++__cur)
					__alloc.construct(__cur);
			}
			catch(...)
			{
				_Destroy(__first, __cur, __alloc);
				throw std::bad_alloc();
			}
		}
		template<typename _ForwardIterator, typename _Size, typename _Allocator>
		void					__uninitialized_fill_n_a(_ForwardIterator __first, _Size __n, const _Tp& __x, _Allocator& __alloc)
		{
			_ForwardIterator __cur = __first;
			try
			{
				for (; __n > 0; --__n, ++__cur)
					__alloc.construct(__cur, __x);
			}
			catch(...)
			{
				_Destroy(__first, __cur, __alloc);
				throw std::bad_alloc();
			}
		}
		template<typename _InputIterator, typename _ForwardIterator, typename _Allocator>
		_ForwardIterator		__uninitialized_move_a(_InputIterator __first, _InputIterator __last, _ForwardIterator __result, _Allocator& __alloc)
		{ return __uninitialized_copy_a(__first, __last, __result, __alloc); }
		void					_M_default_initialize(size_type __n)
		{
			__uninitialized_default_n_a(this->_M_impl._M_start, __n, _M_get_Tp_allocator());
			this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
		}
		template<typename _Integer>
		void					_M_initialize_dispatch(_Integer __n, _Integer __value, ft::__true_type)
		{
			this->_M_impl._M_start = _M_allocate(static_cast<size_type>(__n));
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + static_cast<size_type>(__n);
			_M_fill_initialize(static_cast<size_type>(__n), __value);
		}
		template<typename _InputIterator>
		void					_M_initialize_dispatch(_InputIterator __first, _InputIterator __last, ft::__false_type)
		{
			typedef typename ft::iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_range_initialize(__first, __last, _IterCategory());
		}
		template<typename _ForwardIterator>
		pointer					_M_allocate_and_copy(size_type __n, _ForwardIterator __first, _ForwardIterator __last)
		{
			pointer __result = this->_M_allocate(__n);
			try
			{
				__uninitialized_copy_a(__first, __last, __result, _M_get_Tp_allocator());
				return __result;
			}
			catch(...)
			{
				_M_deallocate(__result, __n);
				throw std::bad_alloc();
			}
		}
		void					_M_erase_at_end(pointer __pos)
		{
			_Destroy(__pos, this->_M_impl._M_finish, _M_get_Tp_allocator());
			this->_M_impl._M_finish = __pos;
		}
	public:
		/*default constructor*/
		vector() : _Base() {}

		explicit vector(const allocator_type& __a) : _Base(__a) {}

		/*fill constructor*/
		explicit vector (size_type __n, const value_type& __value = value_type(), 
			const allocator_type& __a = allocator_type()) : _Base(__n, __a) { _M_fill_initialize(__n, __value); }

		/*range constructor*/
		template <class _InputIterator>
		vector (_InputIterator __first, _InputIterator __last, const allocator_type& __a = allocator_type()) : _Base(__a)
		{
			typedef typename ft::__is_integer<_InputIterator>::__type _Intergral;
			_M_initialize_dispatch(__first, __last, _Intergral());
		}

		/*copy constructor*/
		vector (const vector& __x) : _Base(__x.size(), __x._M_get_Tp_allocator())
		{
			this->_M_impl._M_finish = __uninitialized_copy_a(__x.begin(), __x.end(), this->_M_impl._M_start, _M_get_Tp_allocator());
		}

		/*destructor*/
		~vector() { _Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator()); }

		/*Copy assign operator*/
		vector&	operator= (const vector<_Tp, _Alloc>& __x)
		{
			if (&__x != this)
			{
				const size_type __xlen = __x.size();
				if (__xlen > capacity())
				{
					pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
					_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator());
					_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
					this->_M_impl._M_start = __tmp;
					this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
				}
				else if (size() >= __xlen)
				{
					_Destroy(std::copy(__x.begin(), __x.end(), begin()), end(), _M_get_Tp_allocator());
				}
				else
				{
					std::copy(__x._M_impl._M_start, __x._M_impl._M_start + size(), this->_M_impl._M_start);
					__uninitialized_copy_a(__x._M_impl._M_start + size(), __x._M_impl._M_finish, this->_M_impl._M_finish, _M_get_Tp_allocator());
				}
				this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
			}
			return *this;
		}

		/*Iterators*/
		iterator				begin() { return iterator(this->_M_impl._M_start); }
		const_iterator			begin() const { return const_iterator(this->_M_impl._M_start); }
		iterator				end() { return iterator(this->_M_impl._M_finish); }
		const_iterator			end() const { return iterator(this->_M_impl._M_finish); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		/*Capacity*/
		size_type				size() const { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
		size_type				max_size() const { return _M_get_Tp_allocator().max_size(); }
		void					resize(size_type __new_size, value_type __x = value_type())
		{
			if (__new_size > size())
				insert(end(), __new_size - size(), __x);
			else if (__new_size < size())
				_M_erase_at_end(this->_M_impl._M_start + __new_size);
		}
		size_type				capacity() const { return size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_start); }
		bool					empty() const { return begin() == end(); }
		void					reserve (size_type __n)
		{
			if (__n > this->max_size())
				throw std::length_error("vector::reserve");
			if (this->capacity() < __n)
			{
				const size_type __old_size = size();
				pointer __tmp = _M_allocate_and_copy(__n, this->_M_impl._M_start, this->_M_impl._M_finish);
				_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator());
				this->_M_impl._M_start = __tmp;
				this->_M_impl._M_finish = __tmp + __old_size;
				this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
			}
		}

		/*Element access*/
		reference				operator[] (size_type __n) { return *(this->_M_impl._M_start + __n); }
		const_reference			operator[] (size_type __n) const { return *(this->_M_impl._M_start + __n); }

	protected:

		void					_M_fill_assign(size_t __n, const value_type& __val)
		{
			if (__n > capacity())
			{
				vector __tmp(__n, __val, _M_get_Tp_allocator());
				__tmp.swap(*this);
			}
			else if (__n > size())
			{
				std::fill(begin(), end(), __val);
				__uninitialized_fill_n_a(this->_M_impl._M_finish, __n - size(), __val, _M_get_Tp_allocator());
				this->_M_impl._M_finish += __n - size();
			}
			else
				this->_M_impl._M_finish = std::fill_n(this->_M_impl._M_start, __n, __val);
		}
		void					_M_range_check(size_type __n) const
		{ if (__n >= this->size())
			throw std::out_of_range("vector");
		}
		size_type				_M_check_len(size_type __n, const char* __s) const
		{
			if (max_size() - size() < __n)
				throw std::length_error(__s);
			
			const size_type __len = size() + std::max(size(), __n);
			return (__len < size() || __len > max_size()) ? max_size() : __len;
		}
		void					_M_insert_aux(iterator __position, const _Tp& __x)
		{
			if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
			{
				this->_M_impl.construct(this->_M_impl._M_finish, *(this->_M_impl._M_finish - 1));
				++this->_M_impl._M_finish;
				_Tp __x_copy = __x;
				std::copy_backward(__position.base(), this->_M_impl._M_finish - 2, this->_M_impl._M_finish - 1);
				*__position = __x_copy;
			}
			else
			{
				const size_type __len = _M_check_len(size_type(1), "vector::_M_insert_aux");
				const size_type __elems_before = __position - begin();
				pointer __new_start(this->_M_allocate(__len));
				pointer __new_finish(__new_start);
				try
				{
					this->_M_impl.construct(__new_start + __elems_before, __x);
					__new_finish = 0;
					__new_finish = __uninitialized_move_a(this->_M_impl._M_start, __position.base(), __new_start, _M_get_Tp_allocator());
					++__new_finish;
					__new_finish = __uninitialized_move_a(__position.base(), this->_M_impl._M_finish, __new_finish, _M_get_Tp_allocator());
				}
				catch(...)
				{
					if (!__new_finish)
						this->_M_impl.destroy(__new_start + __elems_before);
					else
						_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
					_M_deallocate(__new_start, __len);
					throw std::bad_alloc();
				}
				_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator());
				_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				this->_M_impl._M_start = __new_start;
				this->_M_impl._M_finish = __new_finish;
				this->_M_impl._M_end_of_storage = __new_start + __len;
			}
		}
		
		template<typename _InputIterator>
		void					_M_range_initialize(_InputIterator __first, _InputIterator __last, std::input_iterator_tag)
		{
			for (; __first != __last; ++__first)
				push_back(*__first);
		}
		template<typename _ForwardIterator>
		void					_M_range_initialize(_ForwardIterator __first, _ForwardIterator __last, std::forward_iterator_tag)
		{
			const size_type __n = std::distance(__first, __last);
			this->_M_impl._M_start = this->_M_allocate(__n);
			this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
			this->_M_impl._M_finish = __uninitialized_copy_a(__first, __last, this->_M_impl._M_start, _M_get_Tp_allocator());
		}
		void					_M_fill_initialize(size_type __n, const value_type& __value)
		{
			__uninitialized_fill_n_a(this->_M_impl._M_start, __n, __value, _M_get_Tp_allocator());
			this->_M_impl._M_finish = this->_M_impl._M_end_of_storage;
		}

		template<typename _Integer>
		void					_M_assign_dispatch(_Integer __n, _Integer __val, ft::__true_type) { _M_fill_assign(__n, __val); }
		template<typename _InputIterator>
		void					_M_assign_dispatch(_InputIterator __first, _InputIterator __last, ft::__false_type)
		{
			typedef typename std::iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_assign_aux(__first, __last, _IterCategory());
		}
		template<typename _InputIterator>
		void					_M_assign_aux(_InputIterator __first, _InputIterator __last, std::input_iterator_tag)
		{
			pointer __cur(this->_M_impl._M_start);
			for (; __first != __last && __cur != this->_M_impl._M_finish; ++__cur, ++__first)
				*__cur = *__first;
			if (__first == __last)
				for (; __cur != this->_M_impl._M_finish; ++__cur)
					_M_get_Tp_allocator().destroy(__cur);
			else
				insert(end(), __first, __last);
		}
		template<typename _ForwardIterator>
		void					_M_assign_aux(_ForwardIterator __first, _ForwardIterator __last, std::forward_iterator_tag)
		{
			const size_type __len = std::distance(__first, __last);
			if (__len > capacity())
			{
				pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
				_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator());
				_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
				this->_M_impl._M_start = __tmp;
				this->_M_impl._M_finish = this->_M_impl._M_start + __len;
				this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
			}
			else if (size() >= __len)
				_M_erase_at_end(std::copy(__first, __last, this->_M_impl._M_start));
			else
			{
				_ForwardIterator __mid = __first;
				std::advance(__mid, size());
				std::copy(__first, __mid, this->_M_impl._M_start);
				this->_M_impl._M_finish = __uninitialized_copy_a(__mid, __last, this->_M_impl._M_finish, _M_get_Tp_allocator());
			}
		}
		template<typename _InputIterator>
		void				_M_range_insert(iterator __pos, _InputIterator __first,  _InputIterator __last, std::input_iterator_tag)
		{
			for (; __first != __last; ++__first)
			{
				__pos = insert(__pos, *__first);
				++__pos;
			}
		}
		template<typename _ForwardIterator>
		void				_M_range_insert(iterator __position, _ForwardIterator __first, _ForwardIterator __last, std::forward_iterator_tag)
		{
			if (__first != __last)
			{
				const size_type __n = std::distance(__first, __last);
				if (size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_finish) >= __n)
				{
					const size_type __elems_after = end() - __position;
					pointer __old_finish(this->_M_impl._M_finish);
					if (__elems_after > __n)
					{
						__uninitialized_move_a(this->_M_impl._M_finish - __n, this->_M_impl._M_finish, this->_M_impl._M_finish, _M_get_Tp_allocator());
						this->_M_impl._M_finish += __n;
						std::copy_backward(__position.base(), __old_finish - __n, __old_finish);
						std::copy(__first, __last, __position);
					}
					else
					{
						_ForwardIterator __mid = __first;
						std::advance(__mid, __elems_after);
						__uninitialized_copy_a(__mid, __last, this->_M_impl._M_finish, _M_get_Tp_allocator());
						this->_M_impl._M_finish += __n - __elems_after;
						__uninitialized_move_a(__position.base(), __old_finish, this->_M_impl._M_finish, _M_get_Tp_allocator());
						this->_M_impl._M_finish += __elems_after;
						std::copy(__first, __mid, __position);
					}
				}
				else
				{
					const size_type __len = _M_check_len(__n, "vector::_M_range_insert");
					pointer __new_start(this->_M_allocate(__len));
					pointer __new_finish(__new_start);
					try
					{
						__new_finish = __uninitialized_move_a(this->_M_impl._M_start, __position.base(), __new_start, _M_get_Tp_allocator());
						__new_finish = __uninitialized_copy_a(__first, __last, __new_finish, _M_get_Tp_allocator());
						__new_finish = __uninitialized_move_a(__position.base(), this->_M_impl._M_finish, __new_finish, _M_get_Tp_allocator());
					}
					catch(...)
					{
						_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
						_M_deallocate(__new_start, __len);
						throw std::bad_alloc();
					}
					_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator());
					_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
					this->_M_impl._M_start = __new_start;
					this->_M_impl._M_finish = __new_finish;
					this->_M_impl._M_end_of_storage = __new_start + __len;
				}
			}
		}
		void				_M_fill_insert(iterator __position, size_type __n, const value_type& __x)
		{
			if (__n != 0)
			{
				if (size_type(this->_M_impl._M_end_of_storage - this->_M_impl._M_finish) >= __n)
				{
					value_type __x_copy = __x;
					const size_type __elems_after = end() - __position;
					pointer __old_finish(this->_M_impl._M_finish);
					if (__elems_after > __n)
					{
						__uninitialized_move_a(this->_M_impl._M_finish - __n, this->_M_impl._M_finish, this->_M_impl._M_finish, _M_get_Tp_allocator());
						this->_M_impl._M_finish += __n;
						std::copy_backward(__position.base(), __old_finish - __n, __old_finish);
						std::fill(__position.base(), __position.base() + __n, __x_copy);
					}
					else
					{
						__uninitialized_fill_n_a(this->_M_impl._M_finish, __n - __elems_after, __x_copy, _M_get_Tp_allocator());
						this->_M_impl._M_finish += __n - __elems_after;
						__uninitialized_move_a(__position.base(), __old_finish, this->_M_impl._M_finish, _M_get_Tp_allocator());
						this->_M_impl._M_finish += __elems_after;
						std::fill(__position.base(), __old_finish, __x_copy);
					}
				}
				else
				{
					const size_type __len = _M_check_len(__n, "vector::_M_fill_insert");
					const size_type __elems_before = __position - begin();
					pointer __new_start(this->_M_allocate(__len));
					pointer __new_finish(__new_start);
					try
					{
						__uninitialized_fill_n_a(__new_start + __elems_before, __n, __x, _M_get_Tp_allocator());
						__new_finish = 0;
						__new_finish = __uninitialized_move_a(this->_M_impl._M_start, __position.base(), __new_start, _M_get_Tp_allocator());
						__new_finish += __n;
						__new_finish = __uninitialized_move_a(__position.base(), this->_M_impl._M_finish, __new_finish, _M_get_Tp_allocator());
					}
					catch(...)
					{
						if (!__new_finish)
							_Destroy(__new_start + __elems_before, __new_start + __elems_before + __n, _M_get_Tp_allocator());
						else
							_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
						_M_deallocate(__new_start, __len);
						throw std::bad_alloc();
					}
					_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish, _M_get_Tp_allocator());
					_M_deallocate(this->_M_impl._M_start, this->_M_impl._M_end_of_storage - this->_M_impl._M_start);
					this->_M_impl._M_start = __new_start;
					this->_M_impl._M_finish = __new_finish;
					this->_M_impl._M_end_of_storage = __new_start + __len;
				}
			}
		}
		template<typename _Integer>
		void				_M_insert_dispatch(iterator __pos, _Integer __n, _Integer __val, ft::__true_type)
		{ _M_fill_insert(__pos, __n, __val); }
		template<typename _InputIterator>
		void				_M_insert_dispatch(iterator __pos, _InputIterator __first, _InputIterator __last, ft::__false_type)
		{
			typedef typename std::iterator_traits<_InputIterator>::iterator_category _IterCategory;
			_M_range_insert(__pos, __first, __last, _IterCategory());
		}

	public:
		reference				at (size_type __n) //protected operator[]
		{
			_M_range_check(__n);
			return (*this)[__n];
		}
		const_reference			at (size_type __n) const
		{
			_M_range_check(__n);
			return (*this)[__n];
		}
		reference				front() { return *begin(); }
		const_reference			front() const { return *begin(); }
		reference				back() { return *(end() - 1); }
		const_reference			back() const { return *(end() - 1); }

		/*Modifiers*/
		void					push_back (const value_type& __x)
		{
			if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
			{
				this->_M_impl.construct(this->_M_impl._M_finish, __x);
				++this->_M_impl._M_finish;
			}
			else
			{
				_M_insert_aux(end(), __x);
			}
		}
		template <class _InputIterator>
		void					assign (_InputIterator __first, _InputIterator __last)
		{
			typedef typename ft::__is_integer<_InputIterator>::__type _Intergral;
			_M_assign_dispatch(__first, __last, _Intergral());
		}
		void					assign (size_type __n, const value_type& __val) { _M_fill_assign(__n, __val); }
		void					swap (vector& __x)
		{
			std::swap(this->_M_impl._M_start, __x._M_impl._M_start);
			std::swap(this->_M_impl._M_finish, __x._M_impl._M_finish);
			std::swap(this->_M_impl._M_end_of_storage, __x._M_impl._M_end_of_storage);
			// std::swap(_M_get_Tp_allocator(), __x._M_get_Tp_allocator());
		}
		void					pop_back()
		{
			--this->_M_impl._M_finish;
			this->_M_impl.destroy(this->_M_impl._M_finish);
		}
		iterator				insert (iterator __position, const value_type& __x)
		{
			const size_type __n = __position - begin();
			if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage && __position == end())
			{
				this->_M_impl.construct(this->_M_impl._M_finish, __x);
				++this->_M_impl._M_finish;
			}
			else
			{
				if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
				{
					_Tp __x_copy = __x;
					_M_insert_aux(__position, __x_copy);
				}
				else
					_M_insert_aux(__position, __x);
			}
			return iterator(this->_M_impl._M_start + __n);
		}
		void					insert (iterator __position, size_type __n, const value_type& __x) { _M_fill_insert(__position, __n, __x); }
		template <class _InputIterator>
		void					insert (iterator __position, _InputIterator __first, _InputIterator __last)
		{
			typedef typename ft::__is_integer<_InputIterator>::__type _Intergral;
			_M_insert_dispatch(__position, __first, __last, _Intergral());
		}
		iterator				erase(iterator __position)
		{
			if (__position + 1 != end())
				std::copy(__position + 1, end(), __position);
			--this->_M_impl._M_finish;
			this->_M_impl.destroy(this->_M_impl._M_finish);
			return __position;
		}
		iterator				erase(iterator __first, iterator __last)
		{
			if (__first != __last)
			{
				if (__last != end())
					std::copy(__last, end(), __first);
				_M_erase_at_end(__first.base() + (end() - __last));
			}
			return __first;
		}
		void					clear() { _M_erase_at_end(this->_M_impl._M_start); }

		/*Allocator*/
		allocator_type			get_allocator() const { return allocator_type(_M_get_Tp_allocator()); }
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
		return !(rhs < lhs);
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
