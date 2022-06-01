/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:44:54 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 19:50:43 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.hpp"

namespace ft
{
	_Rb_tree_node_base* _Rb_tree_increment(_Rb_tree_node_base* __x)
	{
		if (__x->_M_right != 0)
		{
			__x = __x->_M_right;
			while (__x->_M_left != 0)
				__x = __x->_M_left;
		}
		else 
		{
			_Rb_tree_node_base* __y = __x->_M_parent;
			while (__x == __y->_M_right) 
			{
				__x = __y;
				__y = __y->_M_parent;
			}
			if (__x->_M_right != __y)
				__x = __y;
		}
			return __x;
	}

	const _Rb_tree_node_base* _Rb_tree_increment(const _Rb_tree_node_base* __x)
	{
		return _Rb_tree_increment(const_cast<_Rb_tree_node_base*>(__x));
	}

	_Rb_tree_node_base* _Rb_tree_decrement(_Rb_tree_node_base* __x)
	{
		if (__x->_M_color == _S_red && __x->_M_parent->_M_parent == __x)
			__x = __x->_M_right;
		else if (__x->_M_left != 0) 
		{
			_Rb_tree_node_base* __y = __x->_M_left;
			while (__y->_M_right != 0)
				__y = __y->_M_right;
			__x = __y;
		}
		else 
		{
			_Rb_tree_node_base* __y = __x->_M_parent;
			while (__x == __y->_M_left) 
			{
				__x = __y;
				__y = __y->_M_parent;
			}
			__x = __y;
		}
			return __x;
		}
		
	const _Rb_tree_node_base* _Rb_tree_decrement(const _Rb_tree_node_base* __x)
	{
		return _Rb_tree_decrement(const_cast<_Rb_tree_node_base*>(__x));
	}

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
}