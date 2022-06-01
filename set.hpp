/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:58:36 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 22:25:10 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "iterator.hpp"
#include "rb_tree.hpp"
#include <functional>

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	public:
		typedef T												key_type;
		typedef T												value_type;
		typedef Compare											key_compare;
		typedef Compare											value_compare;
		typedef Alloc											allocator_type;
		typedef typename Alloc::reference						reference;
		typedef typename Alloc::const_reference					const_reference;
		typedef typename Alloc::pointer							pointer;
		typedef typename Alloc::const_pointer					const_pointer;

	private:
		typedef typename ft::_Rb_tree<key_type, value_type, ft::_Identity<value_type>, key_compare, Alloc> _Rep_type;
		_Rep_type	tree;

	public:
		typedef typename _Rep_type::iterator					iterator;
		typedef typename _Rep_type::const_iterator				const_iterator;
		typedef typename _Rep_type::reverse_iterator			reverse_iterator;
		typedef typename _Rep_type::const_reverse_iterator		const_reverse_iterator;
		typedef typename _Rep_type::size_type					size_type;
		typedef typename _Rep_type::difference_type				difference_type;

		explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{(void)comp, (void)alloc;}
		template <class InputIterator>
		set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),  const allocator_type& alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
			tree._M_insert_unique(first, last);
		}
		set (const set& x) : tree(x.tree) {}
		~set() {}

		iterator					begin() { return tree.begin(); }
		const_iterator				begin() const { return tree.begin(); }
		iterator					end() { return tree.end(); }
		const_iterator				end() const { return tree.end(); }
		reverse_iterator			rbegin() { return tree.rbegin(); }
		const_reverse_iterator		rbegin() const { return tree.rbegin(); }
		reverse_iterator			rend() { return tree.rend(); }
		const_reverse_iterator		rend() const { return tree.rend(); }

		bool						empty() const { return tree.empty(); }
		size_type					size() const { return tree.size(); }
		size_type					max_size() const { return tree.max_size(); }

		ft::pair<iterator, bool>	insert(const value_type& val) { return tree._M_insert_unique(val); }
		iterator					insert(iterator position, const value_type& val) { return tree._M_insert_unique_(position, val); }
		template <class InputIterator>
		void						insert(InputIterator first, InputIterator last) { return tree._M_insert_unique(first, last); }

		void						erase(iterator position) { tree.erase(position); }
		size_type					erase(const key_type& k) { return tree.erase(k); }
		void						erase(iterator first, iterator second) { tree.erase(first, second); }

		void						swap(set& x) { tree.swap(x.tree); }
		void						clear() { tree.clear(); }

		key_compare					key_comp() const { return tree.key_comp(); }
		value_compare				value_comp() const { return value_compare(tree.key_comp()); }
		iterator					find(const key_type& k) { return tree.find(k); }
		const_iterator				find(const key_type& k) const { return tree.find(k); }
		size_type					count(const key_type& k) const { return tree.find(k) == tree.end() ? 0 : 1; }
		iterator					lower_bound(const key_type& k) { return tree.lower_bound(k); }
		const_iterator				lower_bound(const key_type& k) const { return tree.lower_bound(k); }
		iterator					upper_bound(const key_type& k) { return tree.upper_bound(k); }
		const_iterator				upper_bound(const key_type& k) const { return tree.upper_bound(k); }
		ft::pair<iterator, iterator>				equal_range(const key_type& k) { return tree.equal_range(k); }
		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const { return tree.equal_range(k); }

		allocator_type				get_allocator() const { return tree.get_allocator(); }

	};
}

#endif