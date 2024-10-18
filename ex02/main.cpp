#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    std::vector<int>    firstContainer = check<int, std::vector<int> >(ac, av);
    std::deque<int>     secondContainer(firstContainer.begin(), firstContainer.end());
    clock_t             timer;

    print<int>(firstContainer, "Before");
    timer = clock();
    sort<int>(firstContainer);
    double timeFirstContainer = static_cast<double>(clock() - timer) / CLOCKS_PER_SEC * 1000000;

    print<int>(firstContainer, "After");
    timer = clock();
    sort<int>(secondContainer);
    double timeSecondContainer = static_cast<double>(clock() - timer) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector" << " : " << timeFirstContainer << " us" << std::endl;
    std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque" << " : " << timeSecondContainer << " us" << std::endl;
    return 0;
}