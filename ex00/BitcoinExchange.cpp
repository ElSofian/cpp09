# include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	std::ifstream	file("data.csv");
	std::string		line;

	if (!file.is_open()) {
		std::cerr << RED << "[ERROR] " << DEFAULT << "Could not load data file." << std::endl;
		return;
	}
	while (std::getline(file, line)) {
		std::size_t pos = line.find(",");
		if (pos == std::string::npos) {
			std::cerr << RED << "[ERROR] " << DEFAULT << "Invalid format in data file. Expected 'yyyy-mm-dd,rate'." << std::endl;
			return;
		}
		std::string data = line.substr(0, pos);
		std::string value = line.substr(pos + 1);

		float rate;
		std::istringstream iss(value);
		iss >> std::noskipws >> rate;

		btcData.insert(std::pair<std::string, float>(data, rate));
	}
	file.close();
}

BitcoinExchange::~BitcoinExchange() {
	btcData.clear();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
	if (this != &src) {
		this->btcData.clear();
		this->btcData = src.btcData;
	}
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &src) {
	if (this != &src) {
		this->btcData.clear();
		this->btcData = src.btcData;
	}
	return *this;
}

bool	BitcoinExchange::loadFromInputFile(const std::string &filename) {
	std::ifstream	file(filename.c_str());
	std::string		line;
	unsigned int	i;

	if (!file.is_open()) {
		std::cerr << RED << "[ERROR] " << DEFAULT << "Could not load file (an input.txt file has already been created.)" << std::endl;
		return false;
	}
	i = 0;
	while (std::getline(file, line)) {
		if (!checkInputFile(line, i)) continue;
		else display(line);
		i++;
	}
	_filename = filename;
	file.close();
	return true;
}

bool isValidDate(const std::string &date) {
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	char numbers[] = {date[0], date[1], date[2], date[3], date[5], date[6], date[8], date[9]};
	int year = (numbers[0] - '0') * 1000 + (numbers[1] - '0') * 100 + (numbers[2] - '0') * 10 + (numbers[3] - '0');
	int month = (numbers[4] - '0') * 10 + (numbers[5] - '0');
	int day = (numbers[6] - '0') * 10 + (numbers[7] - '0');

	if (month < 1 || month > 12 || year < 2009)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

	if (isLeapYear)
		daysInMonth[1] = 29;
	if (day < 1 || day > daysInMonth[month - 1])
		return false;
	return true;
}


bool isValidFloat(const std::string &value, float &rate) {
	std::istringstream iss(value);
	iss >> std::noskipws >> rate;
	return iss.eof() && !iss.fail();
}

bool	BitcoinExchange::checkInputFile(std::string line, int i) {
	if (i == 0 && line != "date | value") {
		std::cerr << "Error: The file should start by \"date | value\" line." << std::endl;
		return false;
	}
	if (i > 0) {
		std::size_t pos = line.find(" | ");
		if (pos == std::string::npos) {
			std::cerr << "Error: Invalid format. Expected 'yyyy-mm-dd | value'." << std::endl;
			return false;
		}

		std::string date = line.substr(0, pos);
		std::string value = line.substr(pos + 3);

		if (!isValidDate(date)) {
			std::cerr << "Error: Invalid date or date format. Expected 'yyyy-mm-dd'." << std::endl;
			return false;
		}

		float rate;
		if (!isValidFloat(value, rate)) {
			std::cerr << "Error: Invalid value format. Expected a float." << std::endl;
			return false;
		}

		if (rate < 0 || rate > 1000) {
			std::cerr << "Error: Value out of range. Expected between 0 and 1000." << std::endl;
			return false;
		}
	}
	return true;
}

float BitcoinExchange::getValue(std::string date, float rate) const {
    std::map<std::string, float>::const_iterator it = btcData.upper_bound(date);
    if (it == btcData.begin())
        return 0;

    --it;

    return rate * it->second;
}

void	BitcoinExchange::display(std::string line) const {
	if (line == "date | value")
		return;
	std::size_t pos = line.find(" | ");
	if (pos == std::string::npos)
		return;
	std::string date = line.substr(0, pos);
	std::string value = line.substr(pos + 3);

	float rate;
	std::istringstream iss(value);
	iss >> std::noskipws >> rate;

	std::cout << date << " => " << rate << " = " << getValue(date, rate) << std::endl;
}

void	BitcoinExchange::getData(std::map<std::string, float> &data) const {
	data = btcData;
}

std::ostream	&operator<<(std::ostream &os, const BitcoinExchange &exchange) {
	std::map<std::string, float>	data;

	exchange.getData(data);
	for (std::map<std::string, float>::const_iterator it = data.begin(); it != data.end(); it++) {
		os << it->first << " => " << it->second << std::endl;
	}
	return os;
}