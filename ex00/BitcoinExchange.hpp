# include <iostream>
# include <fstream>
# include <iomanip>
# include <cctype>
# include <string>
# include <map>
# include <sstream>
# include <cstdlib>

# define RED		"\033[1;31m"
# define DEFAULT	"\033[1;37m"

class BitcoinExchange {
	private:
		std::map<std::string, float>	btcData;
		std::string						_filename;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange	&operator=(const BitcoinExchange &src);

		bool	loadFromInputFile(const std::string &filename);
		bool	checkInputFile(std::string line, int i);
		float	getValue(std::string date, float rate) const;
		void	display(std::string line) const;

		void	getData(std::map<std::string, float> &data) const;
};

std::ostream	&operator<<(std::ostream &os, const BitcoinExchange &exchange);