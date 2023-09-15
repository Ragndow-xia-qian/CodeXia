#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/Tokenizer.h"
#include "../src/Tokenizer.cc"

auto main(int argc, char *argv[]) -> int
{
    using std::cerr;
    using std::endl;
    using std::ifstream;
    using std::string;
    using std::vector;

    if (argc < 2)
    {
        cerr << "No Input File" << endl;
        return -1;
    }

    ifstream in(argv[1]);
    if (!in.is_open())
    {
        cerr << "Cannot open file" << endl;
        return -1;
    }

    vector<string> tokens = Tokenizer::tokenizeFile(in);

    vector<vector<string>> lineTokens = Tokenizer::groupTokensByLine(tokens);

    Tokenizer::printTokens(lineTokens);

    return 0;
}
