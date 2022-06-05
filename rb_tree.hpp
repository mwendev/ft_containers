/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 20:53:43 by mwen              #+#    #+#             */
/*   Updated: 2022/06/05 10:48:19 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RB_TREE_HPP
# define FT_RB_TREE_HPP

#include "util.hpp"
#include "iterator.hpp"
#include <memory>

namespace ft
{
	enum _Rb_tree_color { _S_red = false, _S_black = true };

	struct _Rb_tree_node_base
	{
		typedef _Rb_tree_node_base*			_Base_ptr;
		typedef const _Rb_tree_node_base*	_Const_Base_ptr;

		_Rb_tree_color	_M_color;
		_Base_ptr		_M_parent;
		_Base_ptr		_M_left;
		_Base_ptr		_M_right;

		static _Base_ptr _S_minimum(_Base_ptr __x)
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}
		
		static _Const_Base_ptr _S_minimum(_Const_Base_ptr __x)
		{
			while (__x->_M_left != 0)
				__x = __x->_M_left;
			return __x;
		}
		
		static _Base_ptr _S_maximum(_Base_ptr __x)
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}
		
		static _Const_Base_ptr _S_maximum(_Const_Base_ptr __x)
		{
			while (__x->_M_right != 0)
				__x = __x->_M_right;
			return __x;
		}
	};

	template<typename _Val>
	struct _Rb_tree_node : public _Rb_tree_node_base
	{
		typedef _Rb_tree_node<_Val>*	_Link_type;
		_Val	_M_value_field;
	};

	template<typename _Tp>
	struct _Rb_tree_iterator
	{
		typedef _Tp											value_type;
		typedef _Tp&										reference;
		typedef _Tp*										pointer;

		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t									difference_type;
		typedef _Rb_tree_iterator<_Tp>						_Self;
		typedef _Rb_tree_node_base::_Base_ptr				_Base_ptr;
		typedef _Rb_tree_node<_Tp>*							_Link_type;

		_Rb_tree_iterator() : _M_node() {}
		explicit _Rb_tree_iterator(_Link_type __x) : _M_node(__x) {}

		reference operator*() const
		{
			return static_cast<_Link_type>(_M_node)->_M_value_field;
		}
		pointer operator->() const
		{
			return &static_cast<_Link_type>(_M_node)->_M_value_field;
		}
		_Self& operator++ ()
		{
			if (_M_node->_M_right != 0)
			{
				_M_node = _M_node->_M_right;
				while (_M_node->_M_left != 0)
					_M_node = _M_node->_M_left;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_right) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				if (_M_node->_M_right != __y)
					_M_node = __y;
			}
			return *this;
		}
		_Self operator++(int)
		{
			_Self tmp = *this;
			if (_M_node->_M_right != 0)
			{
				_M_node = _M_node->_M_right;
				while (_M_node->_M_left != 0)
					_M_node = _M_node->_M_left;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_right) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				if (_M_node->_M_right != __y)
					_M_node = __y;
			}
			return tmp;
		}
		_Self& operator-- ()
		{
			if (_M_node->_M_color == _S_red && _M_node->_M_parent->_M_parent == _M_node)
				_M_node = _M_node->_M_right;
			else if (_M_node->_M_left != 0) 
			{
				_Rb_tree_node_base* __y = _M_node->_M_left;
				while (__y->_M_right != 0)
					__y = __y->_M_right;
				_M_node = __y;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_left) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				_M_node = __y;
			}
			return *this;
		}
		_Self operator--(int)
		{
			_Self tmp = *this;
			if (_M_node->_M_color == _S_red && _M_node->_M_parent->_M_parent == _M_node)
				_M_node = _M_node->_M_right;
			else if (_M_node->_M_left != 0) 
			{
				_Rb_tree_node_base* __y = _M_node->_M_left;
				while (__y->_M_right != 0)
					__y = __y->_M_right;
				_M_node = __y;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_left) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				_M_node = __y;
			}
			return tmp;
		}

		bool operator==(const _Self& __x) const
		{
			return _M_node == __x._M_node;
		}
		bool operator!=(const _Self& __x) const
		{
			return _M_node != __x._M_node;
		}

		_Base_ptr	_M_node;
	};

	template<typename _Tp>
	struct _Rb_tree_const_iterator
	{
		typedef _Tp											value_type;
		typedef const _Tp&									reference;
		typedef const _Tp*									pointer;

		typedef _Rb_tree_iterator<_Tp>						iterator;

		typedef typename std::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t									difference_type;

		typedef _Rb_tree_const_iterator<_Tp>				_Self;
		typedef _Rb_tree_node_base::_Const_Base_ptr			_Base_ptr;
		typedef const _Rb_tree_node<_Tp>*					_Link_type;

		_Rb_tree_const_iterator() : _M_node() {}
		explicit _Rb_tree_const_iterator(_Link_type __x) : _M_node(__x) {}
		_Rb_tree_const_iterator(const iterator& __it) : _M_node(__it._M_node) {}

		iterator _M_const_cast() const
		{
			return iterator(static_cast<typename iterator::_Link_type>(const_cast<typename iterator::_Base_ptr>(_M_node)));
		}
		reference operator*() const
		{
			return static_cast<_Link_type>(_M_node)->_M_value_field;
		}
		pointer operator->() const
		{
			return &static_cast<_Link_type>(_M_node)->_M_value_field;
		}
		_Self& operator++ ()
		{
			if (_M_node->_M_right != 0)
			{
				_M_node = _M_node->_M_right;
				while (_M_node->_M_left != 0)
					_M_node = _M_node->_M_left;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_right) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				if (_M_node->_M_right != __y)
					_M_node = __y;
			}
			return *this;
		}
		_Self operator++(int)
		{
			_Self tmp = *this;
			if (_M_node->_M_right != 0)
			{
				_M_node = _M_node->_M_right;
				while (_M_node->_M_left != 0)
					_M_node = _M_node->_M_left;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_right) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				if (_M_node->_M_right != __y)
					_M_node = __y;
			}
			return tmp;
		}
		_Self& operator--()
		{
			if (_M_node->_M_color == _S_red && _M_node->_M_parent->_M_parent == _M_node)
				_M_node = _M_node->_M_right;
			else if (_M_node->_M_left != 0) 
			{
				_Rb_tree_node_base* __y = _M_node->_M_left;
				while (__y->_M_right != 0)
					__y = __y->_M_right;
				_M_node = __y;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_left) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				_M_node = __y;
			}
			return *this;
		}
		_Self operator--(int)
		{
			_Self tmp = *this;
			if (_M_node->_M_color == _S_red && _M_node->_M_parent->_M_parent == _M_node)
				_M_node = _M_node->_M_right;
			else if (_M_node->_M_left != 0) 
			{
				_Rb_tree_node_base* __y = _M_node->_M_left;
				while (__y->_M_right != 0)
					__y = __y->_M_right;
				_M_node = __y;
			}
			else 
			{
				_Rb_tree_node_base* __y = _M_node->_M_parent;
				while (_M_node == __y->_M_left) 
				{
					_M_node = __y;
					__y = __y->_M_parent;
				}
				_M_node = __y;
			}
			return tmp;
		}

		bool operator==(const _Self& __x) const
		{
			return _M_node == __x._M_node;
		}
		bool operator!=(const _Self& __x) const
		{
			return _M_node != __x._M_node;
		}

		_Base_ptr	_M_node;
	};

	template<typename _Val>
	inline bool operator==(const _Rb_tree_iterator<_Val>& __x, const _Rb_tree_const_iterator<_Val>& __y)
	{ return __x._M_node == __y._M_node; }

	template<typename _Val>
	inline bool operator!=(const _Rb_tree_iterator<_Val>& __x, const _Rb_tree_const_iterator<_Val>& __y)
	{ return __x._M_node != __y._M_node; }

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc = std::allocator<_Val> >
	class _Rb_tree
	{
		typedef typename _Alloc::template rebind<_Rb_tree_node<_Val> >::other	_Node_allocator;//rebind is a dependent template to std::allocator so Alloc::template, it means the allocator also needs to allocate memory for _Val

	public:
		typedef _Key											key_type;
		typedef _Val											value_type;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef _Rb_tree_node<_Val>*							_Link_type;
		typedef const _Rb_tree_node<_Val>*						_Const_Link_type;
		typedef size_t											size_type;
		typedef ptrdiff_t										difference_type;
		typedef _Alloc											allocator_type;
		typedef _Rb_tree_iterator<value_type>					iterator;
		typedef _Rb_tree_const_iterator<value_type>				const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;	

	protected:
		typedef _Rb_tree_node_base*								_Base_ptr;
		typedef const _Rb_tree_node_base*						_Const_Base_ptr;

		template <typename _Key_compare>
		struct _Rb_tree_impl : public _Node_allocator
		{
			_Key_compare		_M_key_compare;
			_Rb_tree_node_base	_M_header;
			size_type			_M_node_count;
			
			_Rb_tree_impl() : _Node_allocator(), _M_key_compare(), _M_header(), _M_node_count(0) { _M_initialize(); }
			_Rb_tree_impl(const _Key_compare& __comp, const _Node_allocator& __a) : _Node_allocator(__a), _M_key_compare(__comp), _M_header(), _M_node_count(0) { _M_initialize(); }
			
		private:
			void	_M_initialize()
			{
				this->_M_header._M_color = _S_red;
				this->_M_header._M_parent = 0;
				this->_M_header._M_left = &this->_M_header;
				this->_M_header._M_right = &this->_M_header;
			}
		};

		_Rb_tree_impl<_Compare>	_M_impl;

		_Link_type			_M_get_node() { return _M_impl._Node_allocator::allocate(1); } //allocate
		void				_M_put_node(_Link_type __p) { _M_impl._Node_allocator::deallocate(__p, 1); } //deallocate
		_Link_type			_M_create_node(const value_type& __x)
		{
			_Link_type __tmp = _M_get_node();
			try
			{
				get_allocator().construct(&(__tmp->_M_value_field), __x);
			}
			catch(...)
			{
				_M_put_node(__tmp);
			}
			return __tmp;
		}
		void				_M_destroy_node(_Link_type __p)//kill value and deallocate
		{
			get_allocator().destroy(&(__p->_M_value_field));
			_M_put_node(__p);
		}
		_Link_type			_M_clone_node(_Const_Link_type __x)
		{
			_Link_type	__tmp = _M_create_node(__x->_M_value_field);
			__tmp->_M_color = __x->_M_color;
			__tmp->_M_left = 0;
			__tmp->_M_right = 0;
			return __tmp;
		}
		_Base_ptr&			_M_root() { return this->_M_impl._M_header._M_parent; }
		_Const_Base_ptr		_M_root() const { return this->_M_impl._M_header._M_parent; }
		_Base_ptr&			_M_leftmost() { return this->_M_impl._M_header._M_left; }
		_Const_Base_ptr		_M_leftmost() const { return this->_M_impl._M_header._M_left; }
		_Base_ptr&			_M_rightmost() { return this->_M_impl._M_header._M_right; }
		_Const_Base_ptr		_M_rightmost() const { return this->_M_impl._M_header._M_right; }
		_Link_type			_M_begin() { return static_cast<_Link_type>(this->_M_impl._M_header._M_parent); }
		_Const_Link_type	_M_begin() const { return static_cast<_Const_Link_type>(this->_M_impl._M_header._M_parent); }
		_Link_type			_M_end() { return static_cast<_Link_type>(&this->_M_impl._M_header); }
		_Const_Link_type	_M_end() const { return static_cast<_Const_Link_type>(&this->_M_impl._M_header); }

	private:
		iterator		_M_insert_(_Const_Base_ptr __x, _Const_Base_ptr __p, const value_type& __v) // v.key < p.key, insert left
		{
			bool		__insert_left = (__x || __p == _M_end() || _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__p)));
			_Link_type	__z = _M_create_node(__v);

			_Rb_tree_insert_and_rebalance(__insert_left, __z, const_cast<_Base_ptr>(__p), this->_M_impl._M_header);
			++_M_impl._M_node_count;
			return iterator(__z);
		}
		iterator		_M_insert_lower(_Base_ptr __x, _Base_ptr __p, const value_type& __v) //insert with ralative position of y. v.key <= p.key, insert left
		{
			bool		__insert_left = (__x || __p == _M_end() || !_M_impl._M_key_compare(_S_key(__p), _KeyOfValue()(__v)));
			_Link_type	__z = _M_create_node(__v);

			_Rb_tree_insert_and_rebalance(__insert_left, __z, const_cast<_Base_ptr>(__p), this->_M_impl._M_header);
			++_M_impl._M_node_count;
			return iterator(__z);
		}
		iterator		_M_insert_equal_lower(const value_type& __v)
		{
			_Link_type __x = _M_begin();
			_Link_type __y = _M_end();
			while (__x)
			{
				__y = __x;
				__x = !_M_impl._M_key_compare(_S_key(__x), _KeyOfValue()(__v)) ? _S_left(__x) : _S_right(__x);
			}
			return _M_insert_lower(__x, __y, __v);
		}
		_Link_type		_M_copy(_Const_Link_type __x, _Link_type __p)
		{
			_Link_type	__top = _M_clone_node(__x);
			__top->_M_parent = __p;

			try
			{
				// copy right side of the tree
				if (__x->_M_right)
					__top->_M_right = _M_copy(_S_right(__x), __top); // x right child points to top
				__p = __top;
				__x = _S_left(__x);

				// copy left side of the tree
				while (__x)
				{
					_Link_type __y = _M_clone_node(__x);
					__p->_M_left = __y;
					__y->_M_parent = __p;
					if (__x->_M_right)
						__y->_M_right = _M_copy(_S_right(__x), __y);
					__p = __y;
					__x = _S_left(__x);
				}
			}
			catch(...)
			{
				_M_erase(__top);
			}
			return __top;
		}
		void			_M_erase(_Link_type __x) //erase without rebalancing
		{
			while (__x)
			{
				_M_erase(_S_right(__x));
				_Link_type __y = _S_left(__x);
				_M_destroy_node(__x);
				__x = __y;
			}
		}
		iterator		_M_lower_bound(_Link_type __x, _Link_type __y, const _Key& __k) //return a iterator pointing at a node >= k
		{
			while (__x)
				if (!_M_impl._M_key_compare(_S_key(__x), __k)) // x >= k
					__y = __x, __x = _S_left(__x);
				else
					__x = _S_right(__x);
			return iterator(__y);
		}
		const_iterator	_M_lower_bound(_Const_Link_type __x, _Const_Link_type __y, const _Key& __k) const
		{
			while (__x)
				if (!_M_impl._M_key_compare(_S_key(__x), __k)) // x >= k
					__y = __x, __x = _S_left(__x);
				else
					__x = _S_right(__x);
			return const_iterator(__y);
		}
		iterator		_M_upper_bound(_Link_type __x, _Link_type __y, const _Key& __k) //return a iterator pointing at a node > k
		{
			while (__x)
				if (_M_impl._M_key_compare(__k, _S_key(__x)))
					__y = __x, __x = _S_left(__x);
				else
					__x = _S_right(__x);
			return iterator(__y);
		}
		const_iterator	_M_upper_bound(_Const_Link_type __x, _Const_Link_type __y, const _Key& __k) const
		{
			while (__x)
				if (_M_impl._M_key_compare(__k, _S_key(__x)))
					__y = __x, __x = _S_left(__x);
				else
					__x = _S_right(__x);
			return const_iterator(__y);
		}
		void			_M_erase_aux(const_iterator __position)
		{
			_Link_type __y = static_cast<_Link_type>(_Rb_tree_rebalance_for_erase(const_cast<_Base_ptr>(__position._M_node), this->_M_impl._M_header));
			_M_destroy_node(__y);
			--_M_impl._M_node_count;
		}
		void			_M_erase_aux(const_iterator __first, const_iterator __last)
		{
			if (__first == begin() && __last == end())
				clear();
			else
				while (__first != __last)
					erase(__first++);
		}
		_Node_allocator&		_M_get_Node_allocator() { return *static_cast<_Node_allocator*>(&this->_M_impl); }
		const _Node_allocator&	_M_get_Node_allocator() const { return *static_cast<const _Node_allocator*>(&this->_M_impl); }
		void _Rb_tree_rotate_left(_Rb_tree_node_base* const __x, _Rb_tree_node_base*& __root)
		{
			_Rb_tree_node_base* const __y = __x->_M_right;

			__x->_M_right = __y->_M_left;
			if (__y->_M_left != 0)
				__y->_M_left->_M_parent = __x;
			__y->_M_parent = __x->_M_parent;

			if (__x == __root)
				__root = __y;
			else if (__x == __x->_M_parent->_M_left)
				__x->_M_parent->_M_left = __y;
			else
				__x->_M_parent->_M_right = __y;
			__y->_M_left = __x;
			__x->_M_parent = __y;
		}

		void _Rb_tree_rotate_right(_Rb_tree_node_base* const __x, _Rb_tree_node_base*& __root)
		{
			_Rb_tree_node_base* const __y = __x->_M_left;

			__x->_M_left = __y->_M_right;
			if ( __y->_M_right != 0)
				__y->_M_right->_M_parent = __x;
			__y->_M_parent = __x->_M_parent;

			if (__x == __root)
				__root = __y;
			else if (__x == __x->_M_parent->_M_right)
				__x->_M_parent->_M_right = __y;
			else
				__x->_M_parent->_M_left = __y;
			__y->_M_right = __x;
			__x->_M_parent = __y;
		}

		void _Rb_tree_insert_and_rebalance(const bool	__insert_left, _Rb_tree_node_base* __x,
											_Rb_tree_node_base* __p, _Rb_tree_node_base& __header)
		{
			_Rb_tree_node_base *& __root = __header._M_parent; //using pointer reference so anything done to __root does not change the root of the tree

			// Initialize fields in new node to insert.
			__x->_M_parent = __p;
			__x->_M_left = 0;
			__x->_M_right = 0;
			__x->_M_color = _S_red;

			// Insert.
			// Make new node child of parent and maintain root, leftmost and rightmost nodes.
			// N.B. First node is always inserted left.
			if (__insert_left)
			{
				__p->_M_left = __x; 
				if (__p == &__header) // also makes leftmost = __x when __p == &__header
				{
					__header._M_parent = __x;
					__header._M_right = __x;
				}
				else if (__p == __header._M_left)
					__header._M_left = __x; // maintain leftmost pointing to min node
			}
			else
			{
				__p->_M_right = __x;
				if (__p == __header._M_right)
					__header._M_right = __x; // maintain rightmost pointing to max node
			}

			// Rebalance.
			while (__x != __root  && __x->_M_parent->_M_color == _S_red) //if parent is red
			{
				_Rb_tree_node_base* const __xpp = __x->_M_parent->_M_parent;
				if (__x->_M_parent == __xpp->_M_left) //if parent is on the left
				{
					_Rb_tree_node_base* const __y = __xpp->_M_right;
					if (__y && __y->_M_color == _S_red) //if aunt is red, color flip
					{
						__x->_M_parent->_M_color = _S_black;
						__y->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						__x = __xpp;
					}
					else //if aunt is null or black, rotation
					{
						if (__x == __x->_M_parent->_M_right)
						{
							__x = __x->_M_parent;
							_Rb_tree_rotate_left(__x, __root);
						}
						__x->_M_parent->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						_Rb_tree_rotate_right(__xpp, __root);
					}
				}
				else //if parent is on the right
				{
					_Rb_tree_node_base* const __y = __xpp->_M_left;
					if (__y && __y->_M_color == _S_red) 
					{
						__x->_M_parent->_M_color = _S_black;
						__y->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						__x = __xpp;
					}
					else
					{
						if (__x == __x->_M_parent->_M_left) 
						{
							__x = __x->_M_parent;
							_Rb_tree_rotate_right(__x, __root);
						}
						__x->_M_parent->_M_color = _S_black;
						__xpp->_M_color = _S_red;
						_Rb_tree_rotate_left(__xpp, __root);
					}
				}
			}
			__root->_M_color = _S_black;
		}

		_Rb_tree_node_base* _Rb_tree_rebalance_for_erase(_Rb_tree_node_base* const __z, _Rb_tree_node_base& __header)
		{
			_Rb_tree_node_base *& __root = __header._M_parent;
			_Rb_tree_node_base *& __leftmost = __header._M_left;
			_Rb_tree_node_base *& __rightmost = __header._M_right;
			_Rb_tree_node_base* __y = __z; // child of z
			_Rb_tree_node_base* __x = 0; // leave
			_Rb_tree_node_base* __x_parent = 0;

			// get x
			if (__y->_M_left == 0) // z has at most one non-null child on the right. y == z.
				__x = __y->_M_right; // x is the right child of z, might be null.
			else
				if (__y->_M_right == 0) // z has exactly one non-null child on the left. y == z.
					__x = __y->_M_left; // x is the left child, not null.
				else // z has two non-null children.  Set y to z's successor. x might be null.
				{
					__y = __y->_M_right;
					while (__y->_M_left != 0)
						__y = __y->_M_left;
					__x = __y->_M_right;
				}

			// prepar sub-nodes
			if (__y != __z) // z has two children
			{
				// point y back to z
				__z->_M_left->_M_parent = __y; 
				__y->_M_left = __z->_M_left;
				if (__y != __z->_M_right) // when y has at least one left child
				{
					__x_parent = __y->_M_parent;
					if (__x)
						__x->_M_parent = __y->_M_parent;
					__y->_M_parent->_M_left = __x; // point x to y
					__y->_M_right = __z->_M_right;
					__z->_M_right->_M_parent = __y; // point y to y's parent
				}
				else
					__x_parent = __y;
				if (__root == __z)
					__root = __y;
				else if (__z->_M_parent->_M_left == __z) // z is a left child
					__z->_M_parent->_M_left = __y;
				else  // z is a right child
					__z->_M_parent->_M_right = __y;
				__y->_M_parent = __z->_M_parent;
				std::swap(__y->_M_color, __z->_M_color);
				__y = __z;
			}
			else // __z has no or one child
			{
				// point x to z
				__x_parent = __y->_M_parent;
				if (__x)
					__x->_M_parent = __y->_M_parent;
				if (__root == __z)
					__root = __x;
				else 
					if (__z->_M_parent->_M_left == __z) // z is a left child
						__z->_M_parent->_M_left = __x;
					else // z is a right child
						__z->_M_parent->_M_right = __x;
				if (__leftmost == __z)
				{
					if (__z->_M_right == 0)
						__leftmost = __z->_M_parent;
					else
						__leftmost = _Rb_tree_node_base::_S_minimum(__x);
				}
				if (__rightmost == __z)
				{
					if (__z->_M_left == 0) // makes __rightmost == _M_header if __z == __root
						__rightmost = __z->_M_parent;
					else // __x == __z->_M_left
						__rightmost = _Rb_tree_node_base::_S_maximum(__x);
				}
			}

			// handle colors
			if (__y->_M_color != _S_red) 
			{ 
				while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
				if (__x == __x_parent->_M_left) // x is a left child
				{
					_Rb_tree_node_base* __w = __x_parent->_M_right; // sibling
					if (__w->_M_color == _S_red)
					{
					// parent black, x black, sibling red -> parent takes sibling's black, turns red, and left rotates
						__w->_M_color = _S_black;
						__x_parent->_M_color = _S_red;
						_Rb_tree_rotate_left(__x_parent, __root);
						__w = __x_parent->_M_right;
					}
					if ((__w->_M_left == 0 || __w->_M_left->_M_color == _S_black) &&
						(__w->_M_right == 0 || __w->_M_right->_M_color == _S_black))
					{
					// sibling doesn't have child or has only black child(ren) -> sibling turns red, tree moves up
						__w->_M_color = _S_red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					}
					else 
					{
						// handle left child (if applied)
						if (__w->_M_right == 0 || __w->_M_right->_M_color == _S_black) 
						{
						// sibling has only a left child or a black right child -> sibling makes left child black, turns red, right rotates
							__w->_M_left->_M_color = _S_black;
							__w->_M_color = _S_red;
							_Rb_tree_rotate_right(__w, __root);
							__w = __x_parent->_M_right;
						}
						// handle right child
						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = _S_black;
						if (__w->_M_right)
							__w->_M_right->_M_color = _S_black;
						_Rb_tree_rotate_left(__x_parent, __root);
						break;
					}
				} 
				else // x is a right child
				{
					_Rb_tree_node_base* __w = __x_parent->_M_left;
					if (__w->_M_color == _S_red) 
					{
						__w->_M_color = _S_black;
						__x_parent->_M_color = _S_red;
						_Rb_tree_rotate_right(__x_parent, __root);
						__w = __x_parent->_M_left;
					}
					if ((__w->_M_right == 0 || __w->_M_right->_M_color == _S_black) &&
						(__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)) 
					{
						__w->_M_color = _S_red;
						__x = __x_parent;
						__x_parent = __x_parent->_M_parent;
					}
					else 
					{
						if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black) 
						{
							__w->_M_right->_M_color = _S_black;
							__w->_M_color = _S_red;
							_Rb_tree_rotate_left(__w, __root);
							__w = __x_parent->_M_left;
						}
						__w->_M_color = __x_parent->_M_color;
						__x_parent->_M_color = _S_black;
						if (__w->_M_left) 
							__w->_M_left->_M_color = _S_black;
						_Rb_tree_rotate_right(__x_parent, __root);
						break;
					}
				}
				if (__x)
					__x->_M_color = _S_black;
			}
			return __y;
		}

		unsigned int _Rb_tree_black_count(const _Rb_tree_node_base* __node, const _Rb_tree_node_base* __root)
		{
			if (__node == 0)
				return 0;
			unsigned int __sum = 0;
			do
			{
				if (__node->_M_color == _S_black)
					++__sum;
				if (__node == __root)
					break;
				__node = __node->_M_parent;
			} while (1);
			return __sum;
		}

	public:
		_Rb_tree() {}
		_Rb_tree(const _Compare& __comp, const allocator_type& __a = allocator_type()) : _M_impl(__comp, __a) {}
		_Rb_tree(const _Rb_tree& __x) : _M_impl(__x._M_impl._M_key_compare, __x._M_get_Node_allocator())
		{
			if (__x._M_root())
			{
				_M_root() = _M_copy(__x._M_begin(), _M_end());
				_M_leftmost() = _S_minimum(_M_root());
				_M_rightmost() = _S_maximum(_M_root());
				_M_impl._M_node_count = __x._M_impl._M_node_count;
			}
		}
		~_Rb_tree() { _M_erase(_M_begin()); }
		_Rb_tree& operator=(const _Rb_tree& __x)
		{
			if (this != &__x)
			{
				clear();
				_M_impl._M_key_compare = __x._M_impl._M_key_compare;
				if (__x._M_root())
				{
					_M_root() = _M_copy(__x._M_begin(), _M_end());
					_M_leftmost() = _S_minimum(_M_root());
					_M_rightmost() = _S_maximum(_M_root());
					_M_impl._M_node_count = __x._M_impl._M_node_count;
				}
			}
			return *this;
		}
	
		allocator_type			get_allocator() const { return allocator_type(_M_get_Node_allocator()); }
		
		/*Accessors*/
		_Compare				key_comp() const { return _M_impl._M_key_compare; }
		iterator				begin() { return iterator(static_cast<_Link_type>(this->_M_impl._M_header._M_left)); }
		const_iterator			begin() const { return const_iterator(static_cast<_Link_type>(this->_M_impl._M_header._M_left)); }
		iterator				end() { return iterator(static_cast<_Link_type>(&this->_M_impl._M_header)); }
		const_iterator			end() const { return const_iterator(static_cast<_Const_Link_type>(&this->_M_impl._M_header)); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }
		bool					empty() const { return _M_impl._M_node_count == 0; }
		size_type				size() const { return _M_impl._M_node_count; }
		size_type				max_size() const { return _M_get_Node_allocator().max_size(); }
		void					swap(_Rb_tree& __t)
		{
			if (!_M_root())
			{
				if (__t._M_root())
				{
					_M_root() = __t._M_root();
					_M_leftmost() = __t._M_leftmost();
					_M_rightmost() = __t._M_rightmost();
					_M_root()->_M_parent = _M_end();
					
					__t._M_root() = 0;
					__t._M_leftmost() = __t._M_end();
					__t._M_rightmost() = __t._M_end();
				}
			}
			else if (!__t._M_root())
			{
				__t._M_root() = _M_root();
				__t._M_leftmost() = _M_leftmost();
				__t._M_rightmost() = _M_rightmost();
				__t._M_root()->_M_parent = __t._M_end();

				_M_root() = 0;
				_M_leftmost() = _M_end();
				_M_rightmost() = _M_end();
			}
			else
			{
				std::swap(_M_root(), __t._M_root());
				std::swap(_M_leftmost(), __t._M_leftmost());
				std::swap(_M_rightmost(), __t._M_rightmost());
				_M_root()->_M_parent = _M_end();
				__t._M_root()->_M_parent = __t._M_end();
			}
			std::swap(this->_M_impl._M_node_count, __t._M_impl._M_node_count);
			std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);
			// std::__alloc_swap<_Node_allocator>::_S_do_it(_M_get_Node_allocator(), __t._M_get_Node_allocator());
		}

		ft::pair<iterator, bool>	_M_insert_unique(const value_type& __v)// insert with search position of v from the beginning of the tree
		{
			_Link_type __x = _M_begin();
			_Link_type __y = _M_end();
			bool __comp = true;
			while (__x)
			{
				__y = __x;
				__comp = _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__x));
				__x = __comp ? _S_left(__x) : _S_right(__x);
			}
			iterator __j = iterator(__y);
			if (__comp)
			{
				if (__j == begin())
					return ft::pair<iterator, bool>(_M_insert_(__x, __y, __v), true);
				else
					--__j;
			}
			if (_M_impl._M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))
				return ft::pair<iterator, bool>(_M_insert_(__x, __y, __v), true);
			return ft::pair<iterator, bool>(__j, false);
				
		}
		iterator					_M_insert_equal(const value_type& __v)
		{
			_Link_type __x = _M_begin();
			_Link_type __y = _M_end();
			while (__x)
			{
				__y = __x;
				__x = _M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__x)) ? _S_left(__x) : _S_right(__x);
			}
			return _M_insert_(__x, __y, __v);
		}
		iterator					_M_insert_unique_(const_iterator __position, const value_type& __v)
		{
			if (__position._M_node == _M_end())
			{
				if (size() > 0 && _M_impl._M_key_compare(_S_key(_M_rightmost()), _KeyOfValue()(__v)))
					return _M_insert_(0, _M_rightmost(), __v);// insert right of rightmost
				else
					return _M_insert_unique(__v).first;
			}
			else if (_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))
			{
				const_iterator __before = __position; // v is before position
				if (__position._M_node == _M_leftmost())
					return (_M_insert_(_M_leftmost(), _M_leftmost(), __v));// insert left of first node
				else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), _KeyOfValue()(__v)))
				{
					if (_S_right(__before._M_node) == 0)
						return _M_insert_(0, __before._M_node, __v);// insert right of previous node of position
					else
						return _M_insert_(__position._M_node, __position._M_node, __v); // insert left of position
				}
				else
					return _M_insert_unique(__v).first;
			}
			else if (_M_impl._M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
			{
				const_iterator __after = __position; // v is after position
				if (__position._M_node == _M_rightmost())
					return _M_insert_(0, _M_rightmost(), __v);
				else if (_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key((++__after)._M_node)))
				{
					if (_S_right(__position._M_node) == 0)
						return _M_insert_(0, __position._M_node, __v);
					else
						return _M_insert_(__after._M_node, __after._M_node, __v);
				}
				else
					return _M_insert_unique(__v).first;
			}
			else
				return __position._M_const_cast();
		}
		iterator					_M_insert_equal_(const_iterator __position, const value_type& __v)
		{
			if (__position._M_node == _M_end())
			{
				if (size() > 0 && !_M_impl.initialize(_KeyOfValue()(__v), _S_key(_M_rightmost())))
					return _M_insert_(0, _M_rightmost(), __v);
				else
					return _M_insert_equal(__v);
			}
			else if (!_M_impl._M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
			{
				const_iterator __before = __position;
				if (__position._M_node == _M_leftmost())
					return _M_insert_(_M_leftmost(). _M_leftmost(), __v);
				else if (!_M_impl._M_key_compare(_KeyOfValue()(__v), _S_key((--__before)._M_node)))
				{
					if (_S_right(__before._M_node) == 0)
						return _M_insert_(0, __before._M_node, __v);
					else
						return _M_insert_(__position._M_node, __position._M_node, __v);
				}
				else
					return _M_insert_equal(__v);
			}
			else
			{
				const_iterator __after = __position;
				if (__position._M_node == _M_rightmost())
					return _M_insert_(0, _M_rightmost(), __v);
				else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), _KeyOfValue()(__v)))
				{
					if (_S_right(__position._M_node) == 0)
						return _M_insert_(0, __position._M_node, __v);
					else
						return _M_insert_(__after._M_node, __after._M_node, __v);
				}
				else
					return _M_insert_equal_lower(__v);
			}
		}
		template<typename _InputIterator>
		void						_M_insert_unique(_InputIterator __first, _InputIterator __last)
		{
			for (; __first != __last; ++__first)
				_M_insert_unique_(end(), *__first);
		}
		template<typename _InputIterator>
		void						_M_insert_equal(_InputIterator __first, _InputIterator __last)
		{
			for (; __first != __last; ++__first)
				_M_insert_equal_(end(), *__first);
		}
		void						erase(iterator __position) { _M_erase_aux(__position); }
		void						erase(const_iterator __position) { _M_erase_aux(__position); }
		size_type					erase(const key_type& __x)
		{
			ft::pair<iterator, iterator> __p = equal_range(__x);
			const size_type	__old_size = size();
			erase(__p.first, __p.second);
			return __old_size - size();
		}
		void						erase(iterator __first, iterator __last) { _M_erase_aux(__first, __last); }
		void						erase(const_iterator __first, const_iterator __last) { _M_erase_aux(__first, __last); }
		void						erase(const key_type* __first, const key_type* __last)
		{
			while (__first != __last)
				erase(*__first++);
		}
		void						clear()
		{
			_M_erase(_M_begin());
			_M_leftmost() = _M_end();
			_M_root() = 0;
			_M_rightmost() = _M_end();
			_M_impl._M_node_count = 0;
		}
		iterator					find(const key_type& __k)
		{
			iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
			return (__j == end()|| _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
		}
		const_iterator				find(const key_type& __k) const
		{
			const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
			return (__j == end()|| _M_impl._M_key_compare(__k, _S_key(__j._M_node))) ? end() : __j;
		}
		size_type					count(const key_type& __k) const
		{
			ft::pair<const_iterator, const_iterator> __p = equal_range(__k);
			const size_type __n = std::distance(__p.first, __p.second);
			return __n;
		}
		iterator					lower_bound(const key_type& __k) { return _M_lower_bound(_M_begin(), _M_end(), __k); }
		const_iterator				lower_bound(const key_type& __k) const { return _M_lower_bound(_M_begin(), _M_end(), __k); }
		iterator					upper_bound(const key_type& __k) { return _M_upper_bound(_M_begin(), _M_end(), __k); }
		const_iterator				upper_bound(const key_type& __k) const { return _M_upper_bound(_M_begin(), _M_end(), __k); }
		ft::pair<iterator, iterator>				equal_range(const key_type& __k)
		{
			return ft::pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
		}
		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& __k) const
		{
			return pair<const_iterator, const_iterator>(lower_bound(__k), upper_bound(__k));
		}

		bool __rb_verify() const
		{
			if (_M_impl._M_node_count == 0 || begin() == end())
				return _M_impl._M_node_count == 0 && begin() == end()
						&& this->_M_impl._M_header._M_left == _M_end() && this->_M_impl._M_header._M_right == _M_end();
			unsigned int __len = _Rb_tree_black_count(_M_leftmost(), _M_root());
			for (const_iterator __it = begin(); __it != end(); ++__it)
			{
				_Const_Link_type __x = static_cast<_Const_Link_type>(__it._M_node);
				_Const_Link_type __L = _S_left(__x);
				_Const_Link_type __R = _S_right(__x);
				
				if (__x->_M_color == _S_red)
					if ((__L && __L->_M_color == _S_red) || (__R && __R->_M_color == _S_red))
						return false;
				if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
					return false;
				if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__L)))
					return false;
				if (!__L && !__R && _Rb_tree_black_count(__x, _M_root()) != __len)
					return false;
			}
			if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
				return false;
			if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
				return false;
			return true;
		}

	protected:

		static const_reference	_S_value(_Const_Link_type __x) { return __x->_M_value_field; }
		static const _Key&		_S_key(_Const_Link_type __x) { return _KeyOfValue()(_S_value(__x)); }
		static _Link_type		_S_left(_Base_ptr __x) { return static_cast<_Link_type>(__x->_M_left); }
		static _Const_Link_type _S_left(_Const_Base_ptr __x) { return static_cast<_Const_Link_type>(__x->_M_left); }
		static _Link_type		_S_right(_Base_ptr __x) { return static_cast<_Link_type>(__x->_M_right); }
		static _Const_Link_type	_S_right(_Const_Base_ptr __x) { return static_cast<_Const_Link_type>(__x->_M_right); }
		static const_reference	_S_value(_Const_Base_ptr __x) { return static_cast<_Const_Link_type>(__x)->_M_value_field; }
		static const _Key&		_S_key(_Const_Base_ptr __x) { return _KeyOfValue()(_S_value(__x)); }
		static _Base_ptr		_S_minimum(_Base_ptr __x) { return _Rb_tree_node_base::_S_minimum(__x); }
		static _Const_Base_ptr	_S_minimum(_Const_Base_ptr __x) { return _Rb_tree_node_base::_S_minimum(__x); }
		static _Base_ptr 		_S_maximum(_Base_ptr __x) { return _Rb_tree_node_base::_S_maximum(__x); }
		static _Const_Base_ptr	_S_maximum(_Const_Base_ptr __x) { return _Rb_tree_node_base::_S_maximum(__x); }
	};
	
	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool	operator==(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
							const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{
		return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
	}

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool	operator<(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
							const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{
		return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool	operator!=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
							const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{ return !(__x == __y); }

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool	operator>(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
							const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{ return __y < __x; }

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool	operator<=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
							const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{ return !(__y < __x); }

	template<typename _Key, typename _Val, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline bool	operator>=(const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __x,
							const _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>& __y)
	{ return !(__x < __y); }

}

#endif