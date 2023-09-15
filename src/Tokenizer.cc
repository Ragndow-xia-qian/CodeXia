#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include "../include/Tokenizer.h"

std::vector<std::string> Tokenizer::tokenizeFile(std::ifstream &in)
{
    using std::istream_iterator;
    using std::istreambuf_iterator;
    using std::istringstream;
    using std::remove_const_t;
    using std::string;
    using std::vector;

    vector<string>
        tokens;

    string code(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>());

    for (int i = 0; i < code.size(); ++i)
    {
        if (code[i] == '@')
        {
            while (code[i] != '\n')
            {
                code.erase(i, 1);
            }
        }
    }

    for (int i = 0; i < code.size(); ++i)
    {
        if (code[i] == '$')
        {
            code.erase(i, 1);
            while (code[i] != '$')
            {
                code.erase(i, 1);
            }
            code.erase(i, 1);
        }
    }

    // std::cout << code << std::endl;

    remove_const_t<decltype(string::npos)> idx = code.find("\n");
    while (idx != string::npos)
    {
        code.replace(idx, 1, " ");
        idx = code.find("\n", idx + 1);
    }

    for (size_t i = 1; i < code.size(); ++i)
    {
        if (code[i - 1] == ' ' && code[i] == ' ')
        {
            code.erase(i, 1);
            --i;
        }
    }

    istringstream iss(code);
    tokens = vector<string>(
        istream_iterator<string>(iss),
        istream_iterator<string>());

    return tokens;
}

std::vector<std::vector<std::string>> Tokenizer::groupTokensByLine(
    const std::vector<std::string> &tokens)
{
    using std::move;
    using std::string;
    using std::vector;

    vector<vector<string>> lineTokens;

    vector<string> lines;
    for (const auto &token : tokens)
    {
        lines.push_back(token);
        if (token.back() == ';' || token.back() == '[' || token.back() == ']')
        {
            lineTokens.emplace_back(move(lines));
            lines.clear();
        }
    }

    return lineTokens;
}

void Tokenizer::printTokens(const std::vector<std::vector<std::string>> &tokens)
{
    using std::cout;
    using std::endl;
    for (const auto &line : tokens)
    {
        for (const auto &token : line)
        {
            cout << token << " ";
        }
        cout << endl;
    }
}
