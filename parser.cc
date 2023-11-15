#include <memory>

#include "ast.cc" // TODO: Move to a header file
#include "lexer.cc" // TODO: Move to a header file

static int CurrentToken;

static int getNextToken() {
    return CurrentToken = getToken();
}

std::unique_ptr<ExpressionAst> LogError(const std::string &str) {

    std::cerr << "Error: " << str << "\n";
    return nullptr;
}

std::unique_ptr<PrototypeAst> LogErrorPrototype(const std::string &str) {

    LogError(str);
    return nullptr;
}

static std::unique_ptr<ExpressionAst> ParseNumberExpression() {

    auto result = std::make_unique<NumberExpressionAst>(NumVal);
    getNextToken();
    
    return std::move(result);
}

static std::unique_ptr<ExpressionAst> ParseParanExpression() {

    getNextToken();
    auto V = ParseExpression();

    if(!V) 
        return nullptr;

    if(CurrentToken != ')')
        return LogError("expected ')'");

    getNextToken();
    return V;
}

static std::unique_ptr<ExpressionAst> ParseIdentifierExpression() {

    std::string idName = IdentifierStr;
    getNextToken();

    if(CurrentToken != '(') 
        return std::make_unique<VariableExpressionAst>(idName);

    getNextToken();

    std::vector<std::unique_ptr<ExpressionAst>> args;

    if(CurrentToken != ')') {

        while(true) {

            if(auto arg = ParseExpression())
                args.push_back(std::move(arg));
            else
                return nullptr;

            if(CurrentToken == ')')
                break;

            if(CurrentToken != ",")
                return LogError(" expected ')' or ',' in arglist");

            getNextToken();
        }
    }

    getNextToken();

    return std::make_unique<FunctionCallExpressionAst>(idName, std::move(args));
}

static std::unique_ptr<ExpressionAst> ParsePrimary() {

    switch(CurrentToken) {

        case token_id:
            return ParseIdentifierExpression();

        case token_number:
            return ParseNumberExpression();

        case '(':
            return ParseParanExpression();

        default:
            return LogError("Unknown token!");
    }
}