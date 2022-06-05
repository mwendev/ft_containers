/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:39:20 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 17:33:48 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <deque>

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit stack (const container_type& ctnr = container_type()) { c = ctnr; }

		bool				empty() const { return c.empty(); }
		size_type			size() const { return c.size(); }
		value_type&			top() { return *(--c.end()); }
		const value_type&	top() const { return *(--c.end()); }
		void				push(const value_type& val) { c.push_back(val); }
		void				pop() { c.pop_back(); }

		friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.c == rhs.c; }
		
		friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs == rhs); }

  		friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.c < rhs.c; }

		friend bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.c > rhs.c; }

		friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs > rhs); }

		friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs < rhs); }

	protected:
		container_type	c;
	};
}

#endif