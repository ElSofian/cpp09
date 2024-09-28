# include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(RPN const &src) {
	if (this != &src)
		*this = src;
}

RPN & RPN::operator=(RPN const &src) {
	if (this != &src) {
		this->stack = src.stack;
	}
	return *this;
}

int	RPN::stoi(std::string const &str) {
	int			result = 0;
	int			sign = 1;
	std::size_t	i = 0;

	if (str[0] == '-') {
		sign = -1;
		i = 1;
	}
	while (i < str.size()) {
		result = result * 10 + str[i] - '0';
		++i;
	}
	return result * sign;
}

int	RPN::check(std::string const &str) {
	if (str.empty())
	{
		std::cerr << RED << "[ERROR] " << DEFAULT << "Empty string provided." << std::endl;
		return -1;
	}
	for (std::size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			continue;
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			continue;
		if (str[i] >= '0' && str[i] <= '9')
			continue;
		return -1;
	}
	return 0;
}

bool RPN::isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::calculate(char oper, float a, float b) {
    switch (oper) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/':
            if (b == 0) {
                std::cerr << RED << "[ERROR] " << DEFAULT << "Division by zero." << std::endl;
                return -1;
            }
            stack.push(a / b);
            break;
    }
	return 0;
}

int RPN::parse(std::string const &str) {
    for (std::size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ') continue;

        if (isOperator(str[i])) {
            if (stack.size() < 2) {
                std::cerr << RED << "[ERROR] " << DEFAULT << "Not enough operands." << std::endl;
                return -1;
            }
            float a = stack.top(); stack.pop();
            float b = stack.top(); stack.pop();
            if (calculate(str[i], b, a) == -1)
				return -1;
        } else if (std::isdigit(str[i]) || (str[i] == '-' && std::isdigit(str[i + 1]))) {
            std::string operand;
            if (str[i] == '-') operand += str[i++];
            while (i < str.length() && std::isdigit(str[i])) {
                operand += str[i];
                i++;
            }
            stack.push(stoi(operand));
            i--;
        }
    }

    if (stack.size() != 1) {
        std::cerr << RED << "[ERROR] " << DEFAULT << "An error occured while processing the last calcul. Check carefully if the expression is correct." << std::endl;
        return -1;
    }

    return stack.top();
}