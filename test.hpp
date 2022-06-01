/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:09:16 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 21:20:30 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "tests/test_iterator.cpp"
#include "tests/test_map.cpp"
#include "tests/test_pair.cpp"
#include "tests/test_set.cpp"
#include "tests/test_stack.cpp"
#include "tests/test_vector.cpp"

void	test_iterator(std::ofstream& file);
void	test_vector(std::ofstream& file);
void	test_pair(std::ofstream& file);
void	test_map(std::ofstream& file);
void	test_stack(std::ofstream& file);
void	test_set(std::ofstream& file);

#endif