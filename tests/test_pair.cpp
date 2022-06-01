/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pair.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 23:07:05 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:21:12 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>
#include <cstdio>
#include <iomanip>

#if TEST == 1
	namespace ft = std;
	#include <utility>
#else
	#include "../util.hpp"
#endif

void	test_pair(std::ofstream& file)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::ios_base::sync_with_stdio(false);

	file << "[Pair Test - pair<string, double> & make_pair() - member functions]\n\n";
	ft::pair <std::string,double> product1;
	ft::pair <std::string,double> product2 ("tomatoes",2.30);
	ft::pair <std::string,double> product3 (product2);

	product1 = ft::make_pair(std::string("lightbulbs"),0.99);

	product2.first = "shoes";
	product2.second = 39.90;

	file << "Test case: constructers & copy assignment operator\n";
	file << "Output:\n";
	file << "The price of " << product1.first << " is $" << product1.second << '\n';
	file << "The price of " << product2.first << " is $" << product2.second << '\n';
	file << "The price of " << product3.first << " is $" << product3.second << "\n\n";

	file << "[Pair Test - pair<int, char> - relational operators]\n\n";
	file << "Test case: \n";
	ft::pair<int,char> foo (10,'z');
	ft::pair<int,char> bar (90,'a');
	file << "Pair foo is " << foo.first << ", " << foo.second << '\n';
	file << "Pair bar is " << bar.first << ", " << bar.second << '\n';
	file << "Output:\n";
	if (foo==bar) file << "foo and bar are equal\n";
	if (foo!=bar) file << "foo and bar are not equal\n";
	if (foo< bar) file << "foo is less than bar\n";
	if (foo> bar) file << "foo is greater than bar\n";
	if (foo<=bar) file << "foo is less than or equal to bar\n";
	if (foo>=bar) file << "foo is greater than or equal to bar\n\n\n";

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by PAIR is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}
