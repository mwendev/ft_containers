/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:27:25 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:20:57 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <cstdio>
#include <iomanip>

#if TEST == 1
	namespace ft = std;
	#include <set>
#else
	#include "../set.hpp"
#endif

void	test_set(std::ofstream& file)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::ios_base::sync_with_stdio(false);

	file << "[Set Test - set<std::string> - member functions]\n\n";
	
	ft::set<std::string> first;

	std::string list[] = {"Hi", "you", "have", "constructed", "a", "set"};

	ft::set<std::string> second (list, list + 6);

	ft::set<std::string> third (second);

	file << "Test case: constructers\n";
	file << "Output:\n";
	for (ft::set<std::string> ::iterator it = third.begin(); it != third.end(); ++it)
		file << " " << *it;
	file << "\n\n";

	std::string list2[] = {"cat", "is", "complaining"};
	ft::set<std::string> copy(list2, list2 + 3);
	first = copy;

	file << "Test case: copy operator\n";
	file << "Output: init an new set and make it = old set: ";
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << " " << *it;
	file << "\n\n";

	file << "Test case: begin() and end()\n";
	file << "Output:";
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << " " << *it;
	file << "\n\n";

	file << "Test case: rbegin() and end()\n";
	file << "Output:";
	for (ft::set<std::string> ::reverse_iterator it = first.rbegin(); it != first.rend(); ++it)
		file << " " << *it;
	file << "\n\n";

	ft::set<std::string> empty;
	file << "Test case: empty() \n";
	file << "Output: is the set empty? " << first.empty() << "\n";
	file << "Output: is a new set empty? " << empty.empty() << "\n\n";

	file << "Test case: size() and max_size()\n";
	file << "Output: the size of the first set is " << second.size() << ", and the max_size is " << second.max_size() <<"\n";
	file << "Output: the size of the second set is " << copy.size() << ", and the max_size is " << copy.max_size() <<"\n\n";

	first.insert("newly inserted");
	file << "Test case: insert()\n";
	file << "Output - pair<iterator,bool> insert (const value_type& val)\n";
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << *it << " ";
	file << "\n\n";

	file << "Output - iterator insert (iterator position, const value_type& val)\n";
	ft::set<std::string>::iterator itf = first.insert(first.begin(), "yoooo");
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << *it << " ";
	file << "\n";
	file << "newly inserted string is " << *itf << "\n\n";

	file << "Output - range insert\n";
	third.insert(copy.begin(), copy.end());
	for (ft::set<std::string> ::iterator it = third.begin(); it != third.end(); ++it)
		file << *it << " ";
	file << "\n\n";

	file << "Test case: erase()\n";
	file << "Output - void erase (iterator position)\n";
	ft::set<std::string>::iterator it = first.find("is");
	first.erase(it);
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << *it << " ";
	file << "\n\n";

	file << "Output - size_type erase (const key_type& k)\n";
	first.erase("hi");
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << *it << " ";
	file << "\n\n";

	file << "Output - void erase (iterator first, iterator last)\n";
	first.erase(++first.begin(), first.end()--);
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << *it << " ";
	file << "\n\n";

	file << "Test case: swap()\n";
	file << "Output: swaping the old set with the new\n";
	second.swap(first);
	file << "The old one is now :\n";
	for (ft::set<std::string> ::iterator it = second.begin(); it != second.end(); ++it)
		file << *it << " ";
	file << "\n";
	file << "The new one is now :\n";
	for (ft::set<std::string> ::iterator it = first.begin(); it != first.end(); ++it)
		file << *it << " ";
	file << "\n";

	file << "Test case: clear()\n";
	file << "Output: clear current set and check if it's empty\n";
	first.clear();
	file << "Output: is the set empty? " << first.empty() << "\n\n";

	file << "Test case: key_comp()\n";
	ft::set<std::string>::key_compare comp = third.key_comp();
	file << "Output: \n";
	if (comp(*third.begin(), *(--third.end())))
		file << "First key is smaller than last key\n\n";

	file << "Test case: value_comp()\n";
	ft::set<std::string>::value_compare vcomp = third.value_comp();
	file << "Output: \n";
	if (vcomp(*third.begin(), *(--third.end())))
		file << "First value o is smaller than last value\n";

	file << "Test case: find()\n";
	file << "Output: tring to find value of \"Hi\"... " << *third.find("Hi") << "\n\n";

	file << "Test case: count()\n";
	file << "Output: number of element of \"Hi\" is " << third.count("Hi") << "\n\n";

	file << "Test case: lower_bound()\n";
	file << "Output: lower bound of \"Hi\" is " << *third.lower_bound("Hi") << "\n\n";

	file << "Test case: upper_bound()\n";
	file << "Output: upper bound of \"Hi\" is " << *third.upper_bound("Hi") << "\n\n";

	file << "Test case: euqal_range()\n";
	file << "Output: equal range of \"Hi\" is " << *third.equal_range("Hi").first << ", " << *third.equal_range("Hi").second << "\n\n";

	file << "Test case: get_allocator()\n";
	std::string* p = first.get_allocator().allocate(5);
	if (!p)
	{
		file << "MALLOC FAILED";
		return;
	}
	for(int i = 0; i < 5; i++)
		p[i] = "get_allocator";
	file << "Output:\n";
	for(int i = 0; i < 5; i++)
		file << p[i] << ' ';
	file << "\n\n";
	first.get_allocator().deallocate(p,5);

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by SET is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}
