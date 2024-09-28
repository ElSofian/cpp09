# include <iostream>
# include <string>
# include <stack>

# define RED		"\033[1;31m"
# define DEFAULT	"\033[1;37m"

class RPN {
	private:
		std::stack<int>	stack;

	public:
		RPN();
		~RPN();
		RPN(RPN const &src);
		RPN & operator=(RPN const &src);

		int		stoi(std::string const &str);
		bool	isOperator(char c);
		int		calculate(char oper, float a, float b);
		int		check(std::string const &str);
		int		parse(std::string const &str);
};