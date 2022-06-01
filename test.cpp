/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwen <mwen@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:15:38 by mwen              #+#    #+#             */
/*   Updated: 2022/05/31 21:47:47 by mwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

int	main()
{
	std::ofstream file;

	if (TEST)
		file.open("STL_output.txt", std::ios::out);
	else
		file.open("ft_containers_output.txt", std::ios::out);

	if (file.is_open())
	{
		test_vector(file);
		test_pair(file);
		test_map(file);
		test_stack(file);
		test_set(file);
		test_iterator(file);

		file.close();
	}
	else
		std::cout << "\033[1;32mUnable to open file\033[0m\n";

}
