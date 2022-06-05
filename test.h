/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 20:09:16 by mwen              #+#    #+#             */
/*   Updated: 2022/06/04 17:24:01 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include <iostream>
#include <fstream>
#include <string>

void	test_iterator(std::ofstream& file);
void	test_vector(std::ofstream& file);
void	test_pair(std::ofstream& file);
void	test_map(std::ofstream& file);
void	test_stack(std::ofstream& file);
void	test_set(std::ofstream& file);

#endif