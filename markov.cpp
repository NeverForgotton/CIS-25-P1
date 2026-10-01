#include "markov.h"

#include <fstream>
#include <cstdlib>

// Remaining functions are placeholders. Add parameter names when implementing them.
// The corresponding parameter names are listed in markov.h.

std::string joinWords(const std::string words[], int startIndex, int count)
{
    std::string result;

    for (int i = 0; i < count; i++)
    {
        result += words[startIndex + i];
        if (i < count - 1)
        {
            result += " ";
        }
    }

    return result;
}

int readWordsFromFile(std::string, std::string[], int)
{
    // TODO: Step 3 - read words from the input file.
    return 0;
}

int buildMarkovChain(const std::string[], int, int,
                     std::string[], std::string[], int)
{
    // TODO: Step 4 - store each prefix and its following word.
    return 0;
}

std::string getRandomSuffix(const std::string[], const std::string[],
                            int, std::string)
{
    // TODO: Step 5 - randomly choose a suffix matching the current prefix.
    return "";
}

std::string getRandomPrefix(const std::string[], int)
{
    // TODO: Step 6 - randomly choose a stored prefix.
    return "";
}

std::string generateText(const std::string[], const std::string[], int, int, int)
{
    // TODO: Step 7 - follow the chain up to the requested word limit.
    return "";
}
