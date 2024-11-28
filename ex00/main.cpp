# include "BitcoinExchange.hpp"

int	main(int ac, char **av) {

	BitcoinExchange	exchange;

	if (ac != 2) {
		std::cerr << RED << "[ERROR] " << DEFAULT << "Usage: ./btc [filename]" << std::endl;
		return 1;
	}
	if (!exchange.loadFromInputFile(av[1]))
		return 1;
	return 0;

}