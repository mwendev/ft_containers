/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:29:37 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 23:21:31 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <cstdio>
#include <iomanip>

#if TEST == 1
	namespace ft = std;
	#include <vector>
#else
	#include "../vector.hpp"
#endif

void	test_vector_string(std::ofstream& file)
{
	file << "[Vector Test - vector<string> - member functions]\n\n";

	ft::vector<std::string> myvector;
	ft::vector<std::string> second (4,"strange");
	ft::vector<std::string> third (second.begin(),second.end());
	ft::vector<std::string> fourth (third);
	file << "Test case: constructers\n";
	file << "Output:";
	for (ft::vector<std::string>::iterator it = third.begin(); it != third.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  third.size() << ", capacity is " << third.capacity();
	file << "\n\n";

	ft::vector<std::string> fifth (6,"why");
	myvector = fifth;
	file << "Test case: copy operator\n";
	file << "Output:";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	myvector.insert(myvector.begin() + 6, "end");
	file << "Test case: begin() and end()\n";
	file << "Output:";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	file << ' ' << *it;
	file << "\n\n";

	file << "Test case: rbegin() and rend()\n";
	file << "Output: " << *myvector.rbegin() << ' ' << *myvector.rend() << "\n\n";

	myvector.push_back("confused");
	file << "Test case: push_back(), size(), max_size(), capacity() \n";
	file << "Output:";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", max size is " << myvector.max_size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	ft::vector<std::string> empty;
	file << "Test case: empty() \n";
	file << "Output: is the vector empty? " << myvector.empty() << "\n";
	file << "Output: is a new vector empty? " << empty.empty() << "\n\n";

	file << "Test case: resize() \n";
	file << "Output: n > _size ";
	myvector.resize(25);
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n";
	file << "Output: n < _size ";
	myvector.resize(8);
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	file << "Test case: operator[] \n";
	file << "Output: the 6th element in the vector is " << myvector[6] << "\n\n";

	file << "Test case: at() \n";
	try
	{
		myvector.at(50) = 100;
	}
	catch (const std::out_of_range& oor)
	{
		file << "Output: " << "Trying to reach the 50th element " << oor.what() << "\n\n";
	}

	file << "Test case: front() back() \n";
	file << "Output: front is " << myvector.front() << " , back is " << myvector.back() << "\n\n";

	ft::vector<std::string> newvector;
	file << "Test case: assign() \n";
	newvector.assign(3, "new");
	file << "Output: " << "init a new vector with 2 elements ";
	for (ft::vector<std::string>::iterator it = newvector.begin(); it != newvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  newvector.size() << ", capacity is " << newvector.capacity();
	file << "\n";

	newvector.assign(myvector.begin(), myvector.begin() + 3);
	file << "Output: " << "the new vector takes 3 elements of the old vector ";
	for (ft::vector<std::string>::iterator it = newvector.begin(); it != newvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  newvector.size() << ", capacity is " << newvector.capacity();
	file << "\n";

	myvector.assign(5, "Added");
	file << "Output: " << "assign the old vector to be have 5 of new elements";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	ft::vector<std::string>::iterator iter = myvector.insert(myvector.begin() + 3, "hi");
	file << "Test case: insert() \n";
	file << "Output: " << "insert at position 3 -";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << ", return value "<< *iter << "\n";

	myvector.insert(myvector.begin() + 3, 5 , "hi");
	file << "Output: " << "insert at position 3 for 5 time -";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n";

	myvector.insert(myvector.begin(), newvector.begin(), newvector.end());
	file << "Output: " << "insert with input iterator -";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	ft::vector<std::string>::iterator iter2 = myvector.erase(myvector.begin() + 3);
	file << "Test case: erase() \n";
	file << "Output: " << "erase at position 3 -";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", return value "<< *iter2 << "\n\n";

	myvector.swap(newvector);
	file << "Test case: swap() \n";
	file << "Output: " << "swap with the new vector from assign() ";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	myvector.clear();
	myvector.push_back("newly pushed");
	file << "Test case: clear() \n";
	file << "Output: " << "clear and push_back 1 element ";
	for (ft::vector<std::string>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  myvector.size() << ", capacity is " << myvector.capacity();
	file << "\n\n";

	ft::vector<std::string> newvector2;
	std::string* str;
	str = newvector2.get_allocator().allocate(1);
	newvector2.get_allocator().construct(&str[0], "yeah");
	file << "Test case: get_allocator() \n";
	file << "Output: " << "allocate and construct 1 element " << str[0] << "\n\n";
	newvector2.get_allocator().destroy(&str[0]);
	newvector2.get_allocator().deallocate(str, 1);

	file << "Test case: relational operators \n";
	file << "Output: ";
	if (myvector > newvector2)
		file << "swap() vector is larger than clear() vector, ";
	if (newvector2 == newvector2)
		file << "clear() vector euqals to itself, ";
	if (newvector2 != myvector)
		file << "swap() vector does not equal to clear() vector\n\n";
}

void	test_vector_int(std::ofstream& file)
{
	file << "[Vector Test - vector<int> - member functions]\n\n";

	ft::vector<int> first;
	ft::vector<int> second (4,100);
	ft::vector<int> third (second.begin(),second.end());
	ft::vector<int> fourth (third);
	file << "Test case: constructers\n";
	file << "Output:";
	for (ft::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  third.size() << ", capacity is " << third.capacity();
	file << "\n\n";
	ft::vector<int> fifth (6,88);
	first = fifth;
	file << "Test case: copy operator\n";
	file << "Output:";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	first.insert(first.begin() + 9, 10);
	file << "Test case: begin() and end()\n";
	file << "Output:";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
	file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	file << "Test case: rbegin() and rend()\n";
	file << "Output: " << *first.rbegin() << ' ' << *first.rend() << "\n\n";

	first.push_back(999);
	file << "Test case: push_back(), size(), max_size(), capacity() \n";
	file << "Output:";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", max size is " << first.max_size() << ", capacity is " << first.capacity();
	file << "\n\n";

	ft::vector<int> empty;
	file << "Test case: empty() \n";
	file << "Output: is the vector empty? " << first.empty() << "\n";
	file << "Output: is a new vector empty? " << empty.empty() << "\n\n";

	file << "Test case: resize() \n";
	file << "Output: n > _size ";
	first.resize(25);
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n";
	file << "Output: n < _size ";
	first.resize(8);
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	file << "Test case: operator[] \n";
	file << "Output: the 6th element in the vector is " << first[6] << "\n\n";

	file << "Test case: at() \n";
	try
	{
		first.at(50) = 100;
	}
	catch (const std::out_of_range& oor)
	{
		file << "Output: " << "Trying to reach the 50th element " << oor.what() << "\n\n";
	}

	file << "Test case: front() back() \n";
	file << "Output: front is " << first.front() << " , back is " << first.back() << "\n\n";

	ft::vector<int> newvector;
	file << "Test case: assign() \n";
	newvector.assign(3, 42);
	file << "Output: " << "init a new vector with 2 elements ";
	for (ft::vector<int>::iterator it = newvector.begin(); it != newvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  newvector.size() << ", capacity is " << newvector.capacity();
	file << "\n";

	newvector.assign(first.begin(), first.begin() + 3);
	file << "Output: " << "the new vector takes 3 elements of the old vector ";
	for (ft::vector<int>::iterator it = newvector.begin(); it != newvector.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  newvector.size() << ", capacity is " << newvector.capacity();
	file << "\n";

	first.assign(5, 1);
	file << "Output: " << "assign the old vector to be have 5 of new elements";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	ft::vector<int>::iterator iter = first.insert(first.begin() + 3, 5);
	file << "Test case: insert() \n";
	file << "Output: " << "insert at position 3 -";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << ", return value "<< *iter << "\n";

	first.insert(first.begin() + 3, 5 , 42);
	file << "Output: " << "insert at position 3 for 5 time -";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n";

	first.insert(first.begin(), newvector.begin(), newvector.end());
	file << "Output: " << "insert with input iterator -";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	ft::vector<int>::iterator iter2 = first.erase(first.begin() + 3);
	file << "Test case: erase() \n";
	file << "Output: " << "erase at position 3 -";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", return value "<< *iter2 << "\n\n";

	first.swap(newvector);
	file << "Test case: swap() \n";
	file << "Output: " << "swap with the new vector from assign() ";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	first.clear();
	first.push_back(1218);
	file << "Test case: clear() \n";
	file << "Output: " << "clear and push_back 1 element ";
	for (ft::vector<int>::iterator it = first.begin(); it != first.end(); ++it)
		file << ' ' << *it;
	file << ", now the size is " <<  first.size() << ", capacity is " << first.capacity();
	file << "\n\n";

	ft::vector<int> newvector2;
	int* str;
	str = newvector2.get_allocator().allocate(1);
	if (!str)
	{
		file << "MALLOC FAILED";
		return;
	}
	newvector2.get_allocator().construct(&str[0], 999);
	file << "Test case: get_allocator() \n";
	file << "Output: " << "allocate and construct 1 element " << str[0] << "\n\n";
	newvector2.get_allocator().destroy(&str[0]);
	newvector2.get_allocator().deallocate(str, 1);

	file << "Test case: relational operators \n";
	file << "Output: ";
	if (first > newvector2)
		file << "swap() vector is larger than clear() vector, ";
	if (newvector2 == newvector2)
		file << "clear() vector euqals to itself, ";
	if (newvector2 != first)
		file << "swap() vector does not equal to clear() vector\n\n";
}

void	test_vector(std::ofstream& file)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);
	std::ios_base::sync_with_stdio(false);
	test_vector_int(file);
	test_vector_string(file);

	gettimeofday(&end, NULL);
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << "Time taken by VECTOR is : " << std::fixed << time_taken << std::setprecision(6);
	std::cout << " sec\n";
}