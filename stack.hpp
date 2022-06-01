/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:39:20 by mwen              #+#    #+#             */
/*   Updated: 2022/05/30 22:43:33 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit stack (const container_type& ctnr = container_type()) { self = ctnr; }

		bool				empty() const { return self.empty(); }
		size_type			size() const { return self.size(); }
		value_type&			top() { return *(--self.end()); }
		const value_type&	top() const { return *(--self.end()); }
		void				push(const value_type& val) { self.push_back(val); }
		void				pop() { self.pop_back(); }

		friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.self == rhs.self; }
		
		friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs == rhs); }

  		friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.self < rhs.self; }

		friend bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return lhs.self > rhs.self; }

		friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs > rhs); }

		friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{ return !(lhs < rhs); }

	private:
		container_type	self;
	};
}

#endif