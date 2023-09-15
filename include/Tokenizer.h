#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer
{
public:
    static std::vector<std::string> tokenizeFile(std::ifstream &);
    static std::vector<std::vector<std::string>> groupTokensByLine(const std::vector<std::string> &);
    static std::vector<std::vector<std::string>> delete_comment(const std::vector<std::vector<std::string>> &);
    static void printTokens(const std::vector<std::vector<std::string>> &);
};

#endif // TOKENIZER_H
