#include "../include/ExpressionNode.h"
#include <cmath>
#include <sstream>
#include <string>
#include <cctype>
#include <utility>

const std::unordered_map<std::string, int> ExpressionNode::precedence = {
    {"**", 3},
    {"*", 2},
    {"/", 2},
    {"%", 2},
    {"+", 1},
    {"-", 1},
    {"(", 0},
    {")", 0}};

ValueNode::ValueNode(double val) : value(val) {}

double ValueNode::evaluate() const
{
    return value;
}

OperatorNode::OperatorNode(std::string oper, const std::shared_ptr<ExpressionNode> &l, const std::shared_ptr<ExpressionNode> &r)
    : op(std::move(oper)), left(l), right(r) {}

double OperatorNode::evaluate() const
{
    double leftVal = left->evaluate();
    double rightVal = right->evaluate();

    if (op == "+")
    {
        return leftVal + rightVal;
    }
    else if (op == "-")
    {
        return leftVal - rightVal;
    }
    else if (op == "*")
    {
        return leftVal * rightVal;
    }
    else if (op == "/")
    {
        return leftVal / rightVal;
    }
    else if (op == "%")
    {
        return std::fmod(leftVal, rightVal);
    }
    else if (op == "**")
    {
        return std::pow(leftVal, rightVal);
    }

    return 0;
}

std::shared_ptr<ExpressionNode> ExpressionNode::parse(
    const std::string &expression)
{
    std::string expr = expression;

    std::string nexpr;

    int idx = 0;
    while (isspace(expr[idx]))
    {
        idx++;
    }

    if (expr[idx] == '-')
    {
        expr = '0' + expr;
    }

    for (int i = 0; i < expr.length(); ++i)
    {
        nexpr += expr[i];
        if (expr[i] == '+' ||
            expr[i] == '-' ||
            (expr[i] == '*' && expr[i + 1] != '*') ||
            expr[i] == '/' ||
            expr[i] == '%' ||
            (std::isdigit(expr[i]) && !std::isdigit(expr[i + 1])) ||
            expr[i] == '(' ||
            expr[i] == ')')
        {
            nexpr += ' ';
        }
    }
    // std::cout << nexpr << std::endl;
    std::istringstream iss(nexpr);
    std::stack<std::shared_ptr<ExpressionNode>> nodeStack;
    std::stack<std::string> opStack;
    std::string token;

    while (iss >> token)
    {
        if (std::isdigit(token[0]))
        {
            double value = std::stod(token);
            nodeStack.push(std::make_shared<ValueNode>(value));
        }
        else if (token == "(")
        {
            opStack.emplace("(");
        }
        else if (token == ")")
        {
            while (!opStack.empty() && opStack.top() != "(")
            {
                std::string op = opStack.top();
                opStack.pop();

                std::shared_ptr<ExpressionNode> right = nodeStack.top();
                nodeStack.pop();

                std::shared_ptr<ExpressionNode> left = nodeStack.top();
                nodeStack.pop();

                nodeStack.push(std::make_shared<OperatorNode>(op, left, right));
            }

            opStack.pop(); // 弹出左括号
        }
        else
        { // 运算符
            while (!opStack.empty() && opStack.top() != "(" && precedence.at(token) <= precedence.at(opStack.top()))
            {
                std::string op = opStack.top();
                opStack.pop();

                std::shared_ptr<ExpressionNode> right = nodeStack.top();
                nodeStack.pop();

                std::shared_ptr<ExpressionNode> left = nodeStack.top();
                nodeStack.pop();

                nodeStack.push(std::make_shared<OperatorNode>(op, left, right));
            }

            opStack.push(token);
        }
    }

    while (!opStack.empty())
    {
        std::string op = opStack.top();
        opStack.pop();

        if (nodeStack.empty())
        {
            throw std::runtime_error("error");
        }
        std::shared_ptr<ExpressionNode> right = nodeStack.top();
        nodeStack.pop();

        if (nodeStack.empty())
        {
            throw std::runtime_error("error");
        }
        std::shared_ptr<ExpressionNode> left = nodeStack.top();
        nodeStack.pop();

        nodeStack.push(std::make_shared<OperatorNode>(op, left, right));
    }

    if (nodeStack.empty())
    {
        return nullptr;
    }
    return nodeStack.top();
}
