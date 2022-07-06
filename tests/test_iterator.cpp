/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:08:31 by mwen              #+#    #+#             */
/*   Updated: 2022/07/06 12:07:10 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <map>
#include <sys/time.h>
#include <cstdio>
#include <iomanip>

#if TEST == 1
	namespace ft = std;
#else
	#include "../iterator.hpp"
#endif

void test_iterator(std::ofstream& file)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::ios_base::sync_with_stdio(false);

	std::vector<int> myvector;
	for (int i=0; i<10; i += 2) myvector.push_back(i);

	file << "[Reverse Iterator Test - vector<int> - non member functions]\n\n";

	std::vector<int>::iterator from = myvector.begin();
	file << "Original iterator: ";
	while (from != myvector.end())
		file << ' ' << *from++;
	file << "\n\n";

	ft::reverse_iterator<std::vector<int>::iterator> rev_until (myvector.begin());
	ft::reverse_iterator<std::vector<int>::iterator> rev_from (myvector.end());

	file << "Test case: substraction operator (1)\n";
	file << "Output: there are " << (rev_until - rev_from) << " elements.\n\n";

	file << "Test case: addition operator (1)\n";
	file << "Output: value of 3 + the begin of reverse_iterator is " << *(3 + rev_from) << "\n\n";

	file << "Test case: relational operators (==, !=, <, >, <=, >=)\n";
	file << "Output: reverse_iterator of the original iterator is";
	while (rev_from != rev_until)
		file << ' ' << *rev_from++;
	file << "\n\n";

	file << "[Reverse Iterator Test - vector<int> - member functions]\n\n";

	file << "Test case: constructers and dereference (*)\n\n";
	ft::reverse_iterator<std::vector<int>::iterator> rev_it (--myvector.end());
	file << "Output: initialization " << *rev_it.base() << "\n\n";
	ft::reverse_iterator<std::vector<int>::iterator> rev_copy (rev_it);
	file << "Output: copy " << *rev_copy.base() << "\n\n";

	file << "Test case: base()\n";
	file << "Output: the base of reverse_iterator_begin is " << *rev_it.base() << "\n\n";

	file << "Test case: addition operator (2)\n";
	file << "Output: reverse_iterator_begin + 3 is " << *(rev_it + 3) << "\n\n";

	file << "Test case: increment (++)\n";
	ft::reverse_iterator<std::vector<int>::iterator> rev_post (myvector.end());
	file << "Output (pre): ++reverse_iterator_begin is " << *(++rev_it) << '\n';
	file << "Output (post): reverse_iterator_begin++ is " << *(rev_post++) << "\n\n";

	file << "Test case: advance iterator\n";
	ft::reverse_iterator<std::vector<int>::iterator> rev_ad (myvector.end());
	rev_ad += 3;
	file << "Output: reverse_iterator_begin += 3 is " << *(rev_ad) << "\n\n";

	file << "Test case: substraction operator\n";
	file << "Output: reverse_iterator_end - 3 is " << *(rev_until - 3) << "\n\n";

	file << "Test case: decrease (--)\n";
	file << "Output (pre): --reverse_iterator_end is " << *(--rev_until) << '\n';
	file << "Output (post): reverse_iterator_end-- is " << *(rev_until--) << "\n\n";

	file << "Test case: retrocede iterator (end -= 3)\n";
	ft::reverse_iterator<std::vector<int>::iterator> rev_re (myvector.begin());
	rev_re -= 3;
	file << "Output: reverse_iterator_end -= 3" << *(rev_re) << "\n\n";

	file << "Test case: dereference with offset\n";
	ft::reverse_iterator<std::vector<int>::iterator> rev_off (myvector.end());
	file << "Output: reverse_iterator[3] is " << rev_off[3] << "\n\n";

	file << "[Reverse Iterator Test - map<int, string>]\n\n";

	std::map<int,std::string> numbers;
	numbers.insert (std::make_pair(1,"apple"));
	numbers.insert (std::make_pair(2,"orange"));
	numbers.insert (std::make_pair(3,"banana"));
	
	typedef std::map<int,std::string>::iterator map_iter;
	ft::reverse_iterator<map_iter> rev_end (numbers.begin());
	ft::reverse_iterator<map_iter> rev_iterator (numbers.end());

	std::map<int, std::string>::iterator from_map = numbers.begin();
	file << "Original iterator: \n";
	for ( ; from_map != numbers.end() ; ++from_map )
		file << from_map->first << ' ' << from_map->second << '\n';
	file << '\n';

	file << "Test case: dereference iterator (->)\n";
	file << "Output: \n";
	for ( ; rev_iterator != rev_end ; ++rev_iterator )
		file << rev_iterator->first << ' ' << rev_iterator->second << '\n';
	file << '\n';

	file << "[Reverse Iterator Test - vector<char>\n\n";
	std::vector<std::string> strVec;
	strVec.push_back("hello");
	strVec.push_back("world");
	file << "Output:";
	for (std::vector<std::string>::iterator it = strVec.begin(); it != strVec.end(); ++it)
		file << ' ' << *it;
	file << "\n\n";

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by ITERATOR is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}
