#include <computer.h>

using namespace fx::computer;

static void	usage(void)
{
	std::cout << "Usage : [expression]" << std::endl;
	std::cout << "Expression is a polynome" << std::endl;
	std::cout << "\texample: 1 + X ^ 2 + 6 * X" << std::endl;
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
