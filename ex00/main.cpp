# include "BitcoinExchange.hpp"

int	main(int ac, char **av) {

	BitcoinExchange	exchange;

	if (ac != 2) {
		std::cerr << "Usage: ./ex00 [filename]" << std::endl;
		return 1;
	}
	if (!exchange.loadFromFile(av[1])) {
		std::cerr << "Error: could not load file" << std::endl;
		return 1;
	}
	exchange.display();
	return 0;

}