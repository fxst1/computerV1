/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:53:24 by fxst1             #+#    #+#             */
/*   Updated: 2018/06/13 17:19:46 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computer.h>

using namespace fx::computer;

static void	usage(void)
{
	std::cout << "Usage : [expression]" << std::endl;
	std::cout << "Expression is a polynome" << std::endl;
	std::cout << "\texample: 1 + 6 * X + X^2" << std::endl;
}

int 		main(int argc, char **argv)
{
	std::string		s = "";
	Computer		c;

	if (argc > 1)
	{
		argv++;
		while (*argv)
		{
			c.executeCode(std::string(*argv));
			argv++;
		}
	}
	else
		usage();

	return (1);
}
