#include "markov.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::string testWords[] = {"the", "cat", "sat", "down"};


    std::cout << joinWords(testWords, 0, 2) << '\n';
    std::cout << joinWords(testWords, 1, 3) << '\n';
    return 0;
}
