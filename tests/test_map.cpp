/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:46 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 21:21:54 by mwen             ###   ########.fr       */
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

template<typename T, typename U>
void	print_map(std::ofstream& file, const ft::map<T, U>& m, std::string comment = "")
{
	file << comment;
	for (typename ft::map<T, U>::const_iterator it = m.begin(); it != m.end(); it++)
		file << it->first << " = " << it->second << "; ";
	file << '\n';
}

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

	ft::map<std::string, int> m1;
	file << m1.empty() << std::endl;

	m1["CPU"] = 10;
	m1["GPU"] = 15;
	m1["RAM"] = 20;

	file << m1.empty() << std::endl;

	print_map(file, m1, "Initial map: ");

	m1["CPU"] = 25;
	m1["SSD"] = 30;
	print_map(file, m1, "Updated map: ");

	file << "m1[UPS] = " << m1["UPS"] << '\n';
	print_map(file, m1, "Updated map: ");

	m1.erase("GPU");
	print_map(file, m1, "After erase: ");

	file << "m.size() = " << m1.size() << '\n';

	ft::map<std::string, int> m2 = m1;
	print_map(file, m2, "Copy constructed map: ");

	file << std::boolalpha << "m1 and m2 are equivalent: " << (m1 == m2) << '\n';
	m2["PSU"] = 34;
	m2["sPeripherals"] = 12;
	print_map(file, m2, "Updated map: ");
	file << std::boolalpha << "m1 and m2 are equivalent: " << (m1 == m2) << '\n';

	m1.swap(m2);
	print_map(file, m2, "Swapped map: ");

	ft::map<std::string, int> m3(m1);
	ft::map<std::string, int>::iterator mit01 = m3.begin();
	ft::map<std::string, int>::iterator mit02 = m3.end();
	mit02--;

	ft::map<std::string, int>::reverse_iterator rmit01 = m3.rbegin();
	ft::map<std::string, int>::reverse_iterator rmit02 = m3.rend();
	rmit02--;

	print_map(file, m3, "m3: ");

	file << "Begin --- Key: " << mit01->first << " | Value: " << mit01->second << std::endl;
	file << "End   --- Key: " << mit02->first << " | Value: " << mit02->second << std::endl;
	file << "Reverse Begin --- Key: " << rmit01->first << " | Value: " << rmit01->second << std::endl;
	file << "Reverse End   --- Key: " << rmit02->first << " | Value: " << rmit02->second << std::endl;

	ft::map<std::string, int> m4(mit01, mit02);
	print_map(file, m4, "m4: ");
	file << "m4 size = " << m4.size() << std::endl;
	file << "m4 size = " << m4.max_size() << std::endl;

	// ft::map<std::string, int>::allocator_type mapalloc = m4.get_allocator();

	ft::map<std::string, int> m5 = m4;

	m2["Mousepad"] = 5;
	m5.insert(m2.begin(), m2.end());
	print_map(file, m2, "m2: ");
	print_map(file, m5, "m5: ");

	ft::map<std::string, int> m6 = m5;
	m6.erase(m6.begin());
	print_map(file, m6, "m6: ");
	print_map(file, m2, "m2: ");

	file << "M6 size is " << m6.size() << std::endl;
	m6.erase(m6.begin(), m6.end());
	print_map(file, m6, "erased: m6: ");

	m6.swap(m5);
	print_map(file, m6, "m6: ");
	print_map(file, m5, "swapped with m5: ");

	file << m5.count("RAM") << std::endl;
	file << m5.count("HDD") << std::endl;

	if (m5.find("RAM") == m5.end())
			file << "RAM not found" << std::endl;
	if (m5.find("UPS") == m5.end())
			file << "UPS not found" << std::endl;
	print_map(file, m5, "m5: ");
	ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator> range00 = m6.equal_range("PSU");

	file << range00.first->first << " = " << range00.first->second << std::endl;
	file << range00.second->first << " = " << range00.second->second << std::endl;
	file << (*m6.lower_bound("PSU")).first << " = " << (*m6.lower_bound("PSU")).second << std::endl;
	file << (*m6.upper_bound("PSU")).first << " = " << (*m6.upper_bound("PSU")).second << std::endl;
	file << "1) " << std::boolalpha << (m3 == m5) << std::endl;
	file << "2) " << std::boolalpha << (m3 != m5) << std::endl;
	file << "3) " << std::boolalpha << (m3 <  m5) << std::endl;
	file << "4) " << std::boolalpha << (m3 >  m5) << std::endl;
	file << "5) " << std::boolalpha << (m3 >= m5) << std::endl;
	file << "6) " << std::boolalpha << (m3 <= m5) << std::endl;

	ft::map<std::string, int>::key_compare key_comp_map = m1.key_comp();
	ft::map<std::string, int>::value_compare val_comp_map = m1.value_comp();

	file << std::boolalpha << "Python is lexicographically less than C: " << key_comp_map("Python", "C") << '\n';
	file << (std::string("Python") < std::string("C")) << '\n';

	ft::map<std::string, int>::value_type value1_map = ft::make_pair("C", 2);
	ft::map<std::string, int>::value_type value2_map = ft::make_pair("C++", 7);

	file << std::boolalpha << "C is lexicographically less than C++: " << val_comp_map(value1_map, value2_map) << '\n';
	file << "C comp C++ : " << (std::string("C") < std::string("C++")) << '\n';

	ft::map<std::string, int>::iterator it01 = m1.find("SSD");
	(void)it01;
	file << "Key \"SSD\" is in the map: " << m1.count("SSD") << '\n';
	file << "Key \"Stereo\" is in the map: " << m1.count("Stereo") << '\n';
	m1.clear();
	file << std::boolalpha << "Map is empty: " << m1.empty() << '\n';

	ft::map<std::string, int>::reverse_iterator mrev2;
	ft::map<std::string, int>::const_iterator mci1;
	ft::map<std::string, int>::iterator mi1;

	file << m1.empty() << std::endl;

	m1["CPU"] = 10;
	m1["GPU"] = 15;
	m1["RAM"] = 20;

	file << m1.empty() << std::endl;

	print_map(file, m1, "Initial map: ");

	m1["CPU"] = 25;
	m1["SSD"] = 30;
	print_map(file, m1, "Updated map: ");

	file << "m1[UPS] = " << m1["UPS"] << '\n';
	print_map(file, m1, "Updated map: ");
	mci1 = m1.begin();
	file << "const iterator" << std::endl;
	while (mci1 != m1.end())
	{
		file << (*mci1).first << std::endl;
		mci1++;
	}
	file << "iterator" << std::endl;
	mi1 = m1.begin();
	while (mi1 != m1.end())
	{
		file << (*mi1).first << std::endl;
		mi1++;
	}
	file << "reverse_iterator" << std::endl;
	mrev2 = m1.rbegin();
	while (mrev2 != m1.rend())
	{
		file << (*mrev2).first << std::endl;
		mrev2++;
	}
	
	file << "const_reverse_iterator" << std::endl;
	ft::map<std::string, int>::const_reverse_iterator mrev1;
	ft::map<std::string, int>::const_reverse_iterator mrev3;
	mrev1 = m1.rbegin();
	mrev3 = m1.rend();
	while (mrev1 != m1.rend())
	{
		file << (*mrev1).first << std::endl;
		mrev1++;
	}

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by MAP is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}
