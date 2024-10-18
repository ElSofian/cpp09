#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>

#define RED "\033[1;31m"
#define CLEAR "\033[1;37m"

template <typename T, typename Container>
void print(Container &sequence, const std::string &str)
{
    typename Container::iterator start = sequence.begin();

    std::cout << str << ": ";
    while (start != sequence.end())
    {
        std::cout << *start << " ";
        start++;
    }
    std::cout << std::endl;
}

template <typename T, typename Container>
Container check(int ac, char **av)
{
    Container sequence;

    if (ac < 2)
    {
        std::cout << RED << "[Error] " << CLEAR << "No sequence provided." << std::endl;
        exit(1);
    }
    for (int i = 1; i < ac; ++i)
    {
        std::string arg(av[i]);

        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]) && arg[j] != '-')
            {
                std::cout << RED << "[Error] " << CLEAR << "Invalid argument '" << av[i] << "'." << std::endl;
                sequence.clear();
                exit(1);
            }
        }
        sequence.push_back(std::atoi(av[i]));
    }
    return sequence;
}

template <typename T, typename Container>
void sort(Container &sequence)
{
    Container   tmp;

    if (sequence.size() < 2)
        return;
    tmp.push_back(sequence[0]);
    for (size_t i = 1; i < sequence.size(); ++i)
    {
        T current = sequence[i];
        size_t j = i;
        tmp.push_back(tmp[j - 1]);
        while (j > 0 && tmp[j - 1] > current)
        {
            tmp[j] = tmp[j - 1];
            --j;
        }
        tmp[j] = current;
    }
    sequence.swap(tmp);
    tmp.clear();
}