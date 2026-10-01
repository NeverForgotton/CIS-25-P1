#include "markov.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    const int MAX_WORDS = 1000;
    std::string words[MAX_WORDS];
    int count = readWordsFromFile("test.txt", words, MAX_WORDS);

    if (count == -1)
    {
        std::cout << "Could not open test.txt.\n";
        return 1;
    }

    std::cout << "Read " << count << " words\n";
    for (int i = 0; i < 10 && i < count; i++)
    {
        std::cout << words[i] << '\n';
    }

    return 0;
}
