/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:18:34 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 20:51:40 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <sys/time.h>
#include <cstdio>
#include <iomanip>

#if TEST == 1
	namespace ft = std;
	#include <stack>
#else
	#include "../stack.hpp"
#endif

template<typename T>
void	print_stack(std::ofstream& file, ft::stack<T> s, size_t id = 0, const std::string& delimiter = "\n")
{
	size_t n_elems = s.size();
	file << "stack" << id << ":\n";
	for (; !s.empty(); --n_elems)
	{
		file << "[ " << s.top() << " ]" << delimiter;
		s.pop();
	}
}

void	test_stack(std::ofstream& file)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::ios_base::sync_with_stdio(false);

	file << "[Stack Test - stack<string> - member functions]\n\n";
	
	ft::vector<std::string> v1 (2,"vector");
	std::deque<std::string> d1 (4, "deque");
	
	ft::stack<std::string, ft::vector<std::string> > empty;
	ft::stack<std::string, ft::vector<std::string> > vector_stack (v1);
	ft::stack<std::string, std::deque<std::string> > deque_stack (d1);

	file << "Test case: constructer and empty() and size()\n";
	file << "Output:\n";
	file << "Init a vector(2, \"vector\") and a stack(4, \"deque\")\n";
	file << "First stack is constructed without using other containers, the size is" << empty.size() << "\n";
	file << "Second stack is constructed using vector, the size is " << vector_stack.size() << "\n";
	file << "Third stack is constructed using deque, the size is " << deque_stack.size() << "\n";
	file << "Is the first stack empty? " << empty.empty() << "\n\n";

	vector_stack.push("new!");
	file << "Test case: push() and top()\n";
	file << "Output: stack using vector's newly pushed element is... " << vector_stack.top() << " and the size is " << vector_stack.size() << "\n\n";

	vector_stack.pop();
	file << "Test case: pop()\n";
	file << "Output: after pop() the top is... " << vector_stack.top() << " and the size is " << vector_stack.size() << "\n\n";

	file << "Test case: relational operators \n";
	file << "Output: ";
	if (vector_stack > empty)
		file << "vector stack is larger than empty stack, ";
	if (empty == empty)
		file << "empty stack euqals to itself, ";
	if (vector_stack != empty)
		file << "empty stack does not equal to deque stack\n\n";

	ft::stack<int> stack0;
	stack0.push(1);
	stack0.push(2);
	stack0.push(3);
	stack0.push(4);
	print_stack(file, stack0, 0);

	ft::stack<int> stack1 = stack0;
	print_stack(file, stack1, 1);

	ft::stack<int> stack2(stack1);
	print_stack(file, stack2, 2);

	stack1.pop();

	stack2.pop();
	stack2.pop();

	file << stack0.top() << std::endl;
	file << stack1.top() << std::endl;
	file << stack2.top() << std::endl;

	stack2.pop();
	stack2.pop();
	file << std::boolalpha << "Stack2 is empty: " << stack2.empty() << '\n';
	file << std::boolalpha << "Stack0 is empty: " << stack0.empty() << '\n';
	file << "Stack2 size: " << stack2.size() << '\n';
	file << "Stack0 size: " << stack0.size() << '\n';

	file << "1) " << std::boolalpha << (stack0 == stack1) << std::endl;
	file << "2) " << std::boolalpha << (stack0 != stack1) << std::endl;
	file << "3) " << std::boolalpha << (stack0 <  stack1) << std::endl;
	file << "4) " << std::boolalpha << (stack0 >  stack1) << std::endl;
	file << "5) " << std::boolalpha << (stack0 >= stack1) << std::endl;
	file << "6) " << std::boolalpha << (stack0 <= stack1) << std::endl;

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by STACK is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}