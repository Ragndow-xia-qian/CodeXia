#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

class ExpressionNode
{
public:
    virtual ~ExpressionNode() = default;

    virtual double evaluate() const = 0;
    static std::shared_ptr<ExpressionNode> parse(const std::string &expression);

private:
    static const std::unordered_map<std::string, int> precedence;
};

class ValueNode : public ExpressionNode
{
private:
    double value;

public:
    explicit ValueNode(double val);

    double evaluate() const override;
};

class OperatorNode : public ExpressionNode
{
private:
    std::string op;
    std::shared_ptr<ExpressionNode> left;
    std::shared_ptr<ExpressionNode> right;

public:
    OperatorNode(std::string oper, const std::shared_ptr<ExpressionNode> &l, const std::shared_ptr<ExpressionNode> &r);

    double evaluate() const override;
};

#endif // EXPRESSIONNODE_H
