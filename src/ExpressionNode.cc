#include "../include/ExpressionNode.h"
#include <cmath>

OperandNode::OperandNode(double val) : value(val) {}

double OperandNode::evaluate() const
{
    return value;
}

OperatorNode::OperatorNode(const std::string &oper, std::unique_ptr<ExpressionNode> l, std::unique_ptr<ExpressionNode> r)
    : op(oper), left(std::move(l)), right(std::move(r)) {}

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
        return fmod(leftVal, rightVal);
    }
    else if (op == "^")
    {
        return pow(leftVal, rightVal);
    }

    return 0;
}

int OperatorNode::getPrecedence() const
{
    if (op == "+" || op == "-")
    {
        return 1;
    }
    else if (op == "*" || op == "/" || op == "%")
    {
        return 2;
    }
    else if (op == "^")
    {
        return 3;
    }

    return 0;
}

bool OperatorNode::hasHigherPrecedence(const OperatorNode &other) const
{
    return getPrecedence() > other.getPrecedence();
}
