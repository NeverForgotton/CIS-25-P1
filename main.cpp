#include "markov.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>

int main()
{
    std::string testWords[] = {"the", "cat", "sat", "down"};

    // Check the assignment examples, including exact spacing.
    assert(joinWords(testWords, 0, 2) == "the cat");
    assert(joinWords(testWords, 1, 3) == "cat sat down");

    // Check zero words, one word, and the whole array.
    assert(joinWords(testWords, 0, 0) == "");
    assert(joinWords(testWords, 3, 1) == "down");
    assert(joinWords(testWords, 0, 4) == "the cat sat down");

    std::cout << joinWords(testWords, 0, 2) << '\n';
    std::cout << joinWords(testWords, 1, 3) << '\n';
    std::cout << "All joinWords tests passed.\n";
    return 0;
}
