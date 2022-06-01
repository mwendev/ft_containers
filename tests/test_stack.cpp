/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:18:34 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:21:25 by mwen             ###   ########.fr       */
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

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by STACK is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}