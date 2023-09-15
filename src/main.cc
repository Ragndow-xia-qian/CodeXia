#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include "../include/Tokenizer.h"
#include "../include/ExpressionNode.h"
#include "../src/Tokenizer.cc"
#include "../src/ExpressionNode.cc"

auto main(int argc, char *argv[]) -> int
{
    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::exception;
    using std::getline;
    using std::ifstream;
    using std::remove_if;
    using std::shared_ptr;
    using std::string;
    using std::vector;

    if (argc < 2)
    {
        string expr;
        cout << "Enter expression: " << endl;
        cout << "Enter 'exit()' to exit" << endl;
        while (getline((cout << ">>> ", cin), expr) && expr != "exit()")
        {
            if (expr == "exit")
            {
                cout << "Please Enter 'exit()' to exit" << endl;
                continue;
            }
            if (expr.empty()) {
                continue;
            }
            try
            {
                shared_ptr<ExpressionNode> expression = ExpressionNode::parse(expr);
                if (!expression) {
                    continue;
                }
                cout << expression->evaluate() << endl;
            }
            catch (const char *e)
            {
                cerr << "This isn't a expression!" << endl;
                cerr << e << endl;
            }
        }
        return 0;
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
