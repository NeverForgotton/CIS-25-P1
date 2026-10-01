#include "markov.h"

#include <fstream>
#include <cstdlib>



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
    return 0;
}

int buildMarkovChain(const std::string[], int, int,
                     std::string[], std::string[], int)
{
    return 0;
}

std::string getRandomSuffix(const std::string[], const std::string[],
                            int, std::string)
{
    return "";
}

std::string getRandomPrefix(const std::string[], int)
{
    return "";
}

std::string generateText(const std::string[], const std::string[], int, int, int)
{
    return "";
}
