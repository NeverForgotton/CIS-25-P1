#include "markov.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

int main()
{
    std::srand(std::time(0));

    std::string filename;
    std::cout << "Enter input filename: ";
    if (!std::getline(std::cin, filename))
    {
        return 0;
    }

    int order;
    std::string input;
    while (true)
    {
        std::cout << "Enter order (1, 2, or 3): ";
        if (!std::getline(std::cin, input))
        {
            return 0;
        }

        std::istringstream inputStream(input);
        char extra;
        if (!(inputStream >> order) || (inputStream >> extra))
        {
            std::cout << "Please enter a whole number for the order.\n";
        }
        else if (order < 1 || order > 3)
        {
            std::cout << "Order must be 1, 2, or 3. Please try again.\n";
        }
        else
        {
            break;
        }
    }

    int numWords;
    while (true)
    {
        std::cout << "Enter maximum number of words to generate: ";
        if (!std::getline(std::cin, input))
        {
            return 0;
        }

        std::istringstream inputStream(input);
        char extra;
        if (!(inputStream >> numWords) || (inputStream >> extra))
        {
            std::cout << "Please enter a whole number for the word count.\n";
        }
        else if (numWords < order)
        {
            std::cout << "The word count must be at least " << order
                      << ". Please try again.\n";
        }
        else
        {
            break;
        }
    }

    const int MAX_WORDS = 5000;
    std::string words[MAX_WORDS], prefixes[MAX_WORDS], suffixes[MAX_WORDS];
    int count = readWordsFromFile(filename, words, MAX_WORDS);

    if (count == -1)
    {
        std::cout << "Could not open input file: " << filename << std::endl;
        return 1;
    }
    if (count <= order)
    {
        std::cout << "At least " << order + 1
                  << " training words are needed for order " << order << ".\n";
        return 1;
    }

    int chainSize = buildMarkovChain(words, count, order, prefixes, suffixes, MAX_WORDS);
    if (chainSize <= 0)
    {
        std::cout << "No prefix-suffix pairs were built. Cannot generate text.\n";
        return 1;
    }
    if (count == MAX_WORDS)
    {
        std::cout << "At most " << MAX_WORDS
                  << " input words were used; additional words, if any, were ignored.\n";
    }

    std::string output = generateText(prefixes, suffixes, chainSize, order, numWords);
    std::cout << output << std::endl;

    std::istringstream outputStream(output);
    std::string word;
    int actualCount = 0;
    while (outputStream >> word)
    {
        actualCount++;
    }

    std::cout << "Generated " << actualCount << " of at most " << numWords << " words.";
    if (actualCount < numWords)
    {
        std::cout << " Stopped early: the current prefix has no successor.";
    }
    std::cout << std::endl;

    return 0;
}
