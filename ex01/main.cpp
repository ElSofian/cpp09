# include "RPN.hpp"

int	main(int ac, char **av) {
	
	if (ac != 2) {
		std::cout << RED << "[ERROR] " << DEFAULT << "Usage: ./rpn <expression>" << std::endl;
		return 1;
	}

	RPN	rpn;
	int	result;

	if (rpn.check(av[1]) == -1)
		return 1;

	result = rpn.parse(av[1]);
	if (result == -1)
		return 1;
	std::cout << "Result: " << result << std::endl;
	return 0;
}