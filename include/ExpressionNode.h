#include <memory>
#include <string>

#ifndef EXPRESSIONTREEEVALUATOR_H
#define EXPRESSIONTREEEVALUATOR_H

class ExpressionNode
{
public:
    virtual double evaluate() const = 0;
};

class OperandNode : public ExpressionNode
{
private:
    double value;

public:
    OperandNode(double val);

    double evaluate() const override;
};

class OperatorNode : public ExpressionNode
{
private:
    std::string op;
    std::unique_ptr<ExpressionNode> left;
    std::unique_ptr<ExpressionNode> right;

public:
    OperatorNode(const std::string &oper, std::unique_ptr<ExpressionNode> l, std::unique_ptr<ExpressionNode> r);

    double evaluate() const override;

    int getPrecedence() const;

    bool hasHigherPrecedence(const OperatorNode &other) const;
};

#endif // EXPRESSIONTREEEVALUATOR_H
