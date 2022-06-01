/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:46 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:21:19 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <cstdio>
#include <iomanip>

#if TEST == 1
	namespace ft = std;
	#include <map>
#else
	#include "../map.hpp"
#endif

bool fncomp (char lhs, char rhs) { return lhs<rhs; }

struct classcomp {
bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

void	test_map(std::ofstream& file)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::ios_base::sync_with_stdio(false);

	file << "[Map Test - map<char, int> - member functions]\n\n";
	
	ft::map<char,int> first;

	first['a'] = 10;
	first['b'] = 50;
	first['c'] = 20;
	first['d'] = 70;

	ft::map<char,int> second (first.begin(),first.end());

	ft::map<char,int> third (second);

	ft::map<char,int,classcomp> fourth;

	bool(*fn_pt)(char,char) = fncomp; // class as Compare
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	file << "Test case: constructers\n";
	file << "Output:\n";
	for (ft::map<char,int>::iterator it = third.begin(); it != third.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << '\n';
	file << "\n";

	ft::map<char,int> copy;

	copy['x'] = 42;
	copy['c'] = 42;
	copy['p'] = 42;
	copy['e'] = 42;
	copy['h'] = 42;
	third = copy;

	file << "Test case: copy operator\n";
	file << "Output: init an new map and make it = old map:\n";
	for (ft::map<char,int>::iterator it = third.begin(); it != third.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	file << "Test case: begin() and end()\n";
	file << "Output:\n";
	for (ft::map<char,int>::iterator it = third.begin(); it != third.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	file << "Test case: rbegin() and end()\n";
	file << "Output:\n";
	for (ft::map<char,int>::reverse_iterator it = third.rbegin(); it != third.rend(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	ft::map<char,int> empty;
	file << "Test case: empty() \n";
	file << "Output: is the map empty? " << first.empty() << "\n";
	file << "Output: is a new map empty? " << empty.empty() << "\n\n";

	file << "Test case: size() and max_size()\n";
	file << "Output: the size of the first map is " << first.size() << ", and the max_size is " << first.max_size() <<"\n";
	file << "Output: the size of the second map is " << copy.size() << ", and the max_size is " << copy.max_size() <<"\n\n";

	file << "Test case: operator[] and at()\n";
	file << "Output: map['b'] is " << first['b'] << ", at('d') is " << first.at('d') << "\n\n";
	// file << "Out of range test: " << first.at('x') << "\n";

	int	i = 2;
	for (char c = 'a'; c != 'z' + 1; c++)
		first.insert(ft::pair<char, int>(c, i *= 2));

	file << "Test case: insert()\n";
	file << "Output - pair<iterator,bool> insert (const value_type& val)\n";
	for (ft::map<char,int>::iterator it = first.begin(); it != first.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	file << "Output - iterator insert (iterator position, const value_type& val)\n";
	ft::pair<ft::map<char,int>::iterator,bool> ret;
  	ret = first.insert(ft::pair<char,int>('z',500));
  	if (ret.second==false)
	{
		file << "Element 'z' already existed";
		file << " with a value of " << ret.first->second << "\n\n";
	}

	file << "Output - range insert\n";
	fourth.insert(copy.begin(), copy.end());
	for (ft::map<char,int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	file << "Test case: erase()\n";
	file << "Output - void erase (iterator position)\n";
	ft::map<char, int>::iterator it = fourth.find('c');
	fourth.erase(it);
	for (ft::map<char,int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";

	file << "Output - size_type erase (const key_type& k)\n";
	fourth.erase('p');
	for (ft::map<char,int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";

	file << "Output - void erase (iterator first, iterator last)\n";
	it = fourth.find('x');
	fourth.erase(it, fourth.end());
	for (ft::map<char,int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	empty.insert(fourth.begin(), fourth.end());
	file << "Test case: swap()\n";
	file << "Output: swaping the old map with the new\n";
	first.swap(empty);
	file << "The old one is now :\n";
	for (ft::map<char,int>::iterator it = first.begin(); it != first.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "The new one is now :\n";
	for (ft::map<char,int>::iterator it = empty.begin(); it != empty.end(); ++it)
		file << " <" << it->first << ", " << it->second << '>' << "\n";
	file << "\n";

	file << "Test case: clear()\n";
	file << "Output: clear new map and check if it's empty\n";
	empty.clear();
	file << "Output: is the map empty? " << empty.empty() << "\n\n";

	file << "Test case: key_comp()\n";
	ft::map<char, int>::key_compare comp = first.key_comp();
	file << "Output: \n";
	if (comp(first.begin()->first, (--first.end())->first))
		file << "Key 'e' is smaller than key 'h'\n\n";

	file << "Test case: value_comp()\n";
	ft::map<char, int>::value_compare vcomp = first.value_comp();
	file << "Output: \n";
	if (vcomp(ft::pair<char, int>('e', 42), ft::pair<char, int>('h', 42)))
		file << "Value of 'e' is smaller than value of 'h'\n";
	else
		file << "Value of 'e' is not smaller than value of 'h'\n\n";

	file << "Test case: find()\n";
	file << "Output: value of 'e' is " << first.find('e')->second << "\n\n";

	file << "Test case: count()\n";
	file << "Output: number of element of 'e' is " << first.count('e') << "\n\n";

	file << "Test case: lower_bound()\n";
	file << "Output: lower bound of 'e' is " << first.lower_bound('e')->first << ", " << first.lower_bound('e')->second << "\n\n";

	file << "Test case: upper_bound()\n";
	file << "Output: upper bound of 'e' is " << first.upper_bound('e')->first << ", " << first.upper_bound('e')->second << "\n\n";

	file << "Test case: euqal_range()\n";
	file << "Output: equal range of 'e' is " << first.equal_range('e').first->first << ", " << first.equal_range('e').first->second << "\n\n";

	file << "Test case: get_allocator()\n";
	int	psize;
	ft::pair<const char,int>* p = first.get_allocator().allocate(5);
	if (!p)
	{
		file << "MALLOC FAILED";
		return;
	}
	psize = sizeof(ft::map<char,int>::value_type)*5;
	file << "Output: The allocated array has a size of " << psize << " bytes.\n";
	first.get_allocator().deallocate(p,5);

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by MAP is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}
