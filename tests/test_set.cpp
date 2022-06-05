/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:27:25 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 21:40:05 by mwen             ###   ########.fr       */
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

template<typename T>
void print_set(std::ofstream& file, ft::set<T>& s, std::string comment = "")
{
	file << comment;
	for (typename ft::set<T>::const_iterator it = s.begin(); it != s.end(); it++)
		file << *it << " -> ";
	file << "(end)" << std::endl;
}

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

	file << std::endl << "SET" << std::endl << std::endl; 

	ft::set<std::string> s1;
	file << s1.empty() << std::endl;

	s1.insert("CPU");
	s1.insert("GPU");
	s1.insert("RAM");
	
	file << s1.empty() << std::endl;
	
	print_set(file, s1, "Initial set: ");
	
	s1.insert("CPU");
	s1.insert("SSD");
	print_set(file, s1, "Updated set: ");
	
	s1.erase("GPU");
	print_set(file, s1, "After erase: ");
	
	file << "m.size() = " << s1.size() << '\n';
	
	ft::set<std::string> s2 = s1;
	print_set(file, s2, "Copy constructed set: ");
		
	file << std::boolalpha << "s1 and s2 are equivalent: " << (s1 == s2) << '\n';
	s2.insert("PSU");
	s2.insert("Peripherals");
	print_set(file, s2, "Updated set: ");
	file << std::boolalpha << "s1 and s2 are equivalent: " << (s1 == s2) << '\n';
	
	s1.swap(s2);
	print_set(file, s2, "Swapped set: ");
	
	ft::set<std::string>::key_compare key_comp_set = s1.key_comp();
	ft::set<std::string>::value_compare val_comp_set = s1.value_comp();
	
	file << std::boolalpha << "Python is lexicographically less than C: " << key_comp_set("Python", "C") << '\n';
	file << (std::string("Python") < std::string("C")) << '\n';
	
	ft::set<std::string>::value_type value1_set = (std::string)"C";
	ft::set<std::string>::value_type value2_set = (std::string)"C++";
	
	file << std::boolalpha << "C is lexicographically less than C++: " << val_comp_set(value1_set, value2_set) << '\n';
	file << (std::string("C") < std::string("C++")) << '\n';
	
	ft::set<std::string>::iterator it01_set = s1.find("SSD");
	(void)it01_set;
	file << "Key \"SSD\" is in the set: " << s1.count("SSD") << '\n';
	file << "Key \"Stereo\" is in the set: " << s1.count("Stereo") << '\n';
	
	ft::set<std::string> s3(s1);
	ft::set<std::string>::iterator sit01 = s3.begin();
	ft::set<std::string>::iterator sit02 = s3.end();
	sit02--;
	ft::set<std::string>::reverse_iterator rsit01 = s3.rbegin();
	ft::set<std::string>::reverse_iterator rsit02 = s3.rend();
	rsit02--;
	print_set(file, s3, "s3: ");

	file << "Begin --- Key: " << *sit01 << std::endl;
	file << "End   --- Key: " << *sit02 << std::endl;
	file << "Reverse Begin --- Key: " << *rsit01 << std::endl;
	file << "Reverse End   --- Key: " << *rsit02 << std::endl;

	ft::set<std::string> s4(sit01, sit02);
	print_set(file, s4, "s4: ");
	file << "s4 size = " << s4.size() << std::endl;
	file << "s4 size = " << s4.max_size() << std::endl;

	// ft::set<std::string>::allocator_type setalloc = s4.get_allocator();

	ft::set<std::string> s5 = s4;

	s5.insert(s2.begin(), s2.end());
	print_set(file, s2, "s2: ");
	print_set(file, s5, "s5: ");

	ft::set<std::string> s6 = s5;
	s6.erase(s6.begin());
	print_set(file, s6, "s6: ");

	s6.erase(s6.begin(), s6.end());
	print_set(file, s6, "s6: ");

	s6.swap(s5);
	print_set(file, s6, "s6: ");

	file << s5.count("RAM") << std::endl;
	file << s5.count("HDD") << std::endl;

	//Dangerous !! find will return end() iterator if nothing was found
	//trying to dereference end() will cause undefined behavior (UB)
	file << (*s6.find("RAM")) << std::endl;
	file << (*s6.find("PSU")) << std::endl;

	//better this way !
	if (s6.find("USP") == s6.end())
			file << "USP not found" << std::endl;
	else
			file << "USP found" << std::endl;

	//same here, equal_range returns a pair of iterators, take care that you
	//are not going to try dereferencing end()
	ft::pair<ft::set<std::string>::iterator, ft::set<std::string>::iterator> srange00 = s6.equal_range("PSU");

	file << *(srange00.first) << " = " << *(srange00.first) << std::endl;
	file << *(srange00.first) << " = " << *(srange00.second) << std::endl;
	file << (*s6.lower_bound("PSU")) << " = " << (*s6.lower_bound("PSU")) << std::endl;
	file << (*s6.upper_bound("PSU")) << " = " << (*s6.upper_bound("PSU")) << std::endl;

	file << std::boolalpha << (s3 == s5) << std::endl;
	file << std::boolalpha << (s3 != s5) << std::endl;
	file << std::boolalpha << (s3 <  s5) << std::endl;
	file << std::boolalpha << (s3 >  s5) << std::endl;
	file << std::boolalpha << (s3 >= s5) << std::endl;
	file << std::boolalpha << (s3 <= s5) << std::endl;
	
	s1.clear();
	file << std::boolalpha << "Set is empty: " << s1.empty() << '\n';

	ft::set<std::string>::reverse_iterator srev2;
	ft::set<std::string>::const_iterator sci1;
	ft::set<std::string>::iterator si1;

	file << s1.empty() << std::endl;

	s1.insert("CPU");
	s1.insert("GPU");
	s1.insert("RAM");

	file << s1.empty() << std::endl;

	print_set(file, s1, "Initial set: ");

	sci1 = s1.begin();
	file << "const iterator" << std::endl;
	while (sci1 != s1.end())
	{
		file << (*sci1) << std::endl;
		sci1++;
	}
	file << "iterator" << std::endl;
	si1 = s1.begin();
	while (si1 != s1.end())
	{
		file << (*si1) << std::endl;
		si1++;
	}
	file << "reverse_iterator" << std::endl;
	srev2 = s1.rbegin();
	while (srev2 != s1.rend())
	{
		file << (*srev2) << std::endl;
		srev2++;
	}
	file << "const_reverse_iterator" << std::endl;
	ft::set<std::string>::const_reverse_iterator srev1;
	ft::set<std::string>::const_reverse_iterator srev3;
	srev1 = s1.rbegin();
	srev3 = s1.rend();
	while (srev1 != s1.rend()) //rev3)
	{
		file << (*srev1) << std::endl;
		srev1++;
	}

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by SET is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}
