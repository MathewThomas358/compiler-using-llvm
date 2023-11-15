#include <string>
#include <memory>
#include <vector>

class ExpressionAst {

public:
    virtual ~ExpressionAst() = default;
    //TODO: Add other accessor methods
};

class NumberExpressionAst : public ExpressionAst{

private:
    double val;

public:
    NumberExpressionAst(double val) : val(val) {}
};

class VariableExpressionAst : public ExpressionAst {

private:
    std::string name;

public:
    VariableExpressionAst(const std::string &name) : name(name) {}
};

class BinaryExpressionAst : public ExpressionAst {

private:
    char op;
    std::unique_ptr<ExpressionAst> lhs;
    std::unique_ptr<ExpressionAst> rhs;

public:
    BinaryExpressionAst(
        char op,
        std::unique_ptr<ExpressionAst> lhs,
        std::unique_ptr<ExpressionAst> rhs
    ) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class FunctionCallExpressionAst : public ExpressionAst {

private:
    std::string callee;
    std::vector<std::unique_ptr<ExpressionAst>> args;

public:
    FunctionCallExpressionAst(
        const std::string &callee,
        std::vector<std::unique_ptr<ExpressionAst>> args
    ) : callee(callee), args(std::move(args)) {}
};

class PrototypeAst {

private:
    std::string name;
    std::vector<std::string> args;

public:
    PrototypeAst(
        const std::string &name,
        std::vector<std::string> args
    ) : name(name), args(std::move(args)) {}

    const std::string &GetName() const {
        return name;
    }
};

class FunctionAst {

private:
    std::unique_ptr<PrototypeAst> proto;
    std::unique_ptr<ExpressionAst> body;

public:
    FunctionAst(
        std::unique_ptr<PrototypeAst> proto,
        std::unique_ptr<ExpressionAst> body
    ) : proto(std::move(proto)), body(std::move(body)) {}
};

int main(void) {
    return 0;
}