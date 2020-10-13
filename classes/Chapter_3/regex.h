#ifndef REGEX_H
#define REGEX_H

#include <string>

class regex
{

private:
    int wordCount;
    std::string text;

public:
    regex(std::string pathToFile);
    int getWordCount();
};

#endif