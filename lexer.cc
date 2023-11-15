#include <iostream>
#include <string>
#include <locale>
#include <cstdio>
#include <cctype>

enum Token {

    token_eof = -1,
    token_def = -2,
    token_extern = -3,
    token_id  = -4,
    token_number = -5,
};

// TODO: Possible improvement, add these into a class.

static std::string IdentifierStr;
static double NumVal;

static int getToken() {

    static int lastChar = ' ';

    while(std::isspace(lastChar))
        lastChar = std::getchar();

    if(std::isalpha(lastChar)) {

        IdentifierStr = lastChar;

        while(std::isalnum((lastChar = std::getchar())))
            IdentifierStr += lastChar;

        if(IdentifierStr == "def")
            return token_def;

        if(IdentifierStr == "extern")
            return token_extern;

        return token_id;
    }

    if(std::isdigit(lastChar) || lastChar == '.') {

        std::string numStr;

        do {

            numStr += lastChar;
            lastChar = std::getchar();
        } while(std::isdigit(lastChar) || lastChar == '.');

        // BUG: Check if numStr contains multiple decimal points
        NumVal = std::strtod(numStr.c_str(), 0);
        return token_number; 
    }

    if(lastChar == '#') {

        do 
            lastChar = std::getchar();
        while(
            lastChar != EOF &&
            lastChar != '\n' &&
            lastChar != '\r'
        );

        if(lastChar != EOF)
            return getToken();
    }

    if(lastChar == EOF) 
        return token_eof;

    int thisChar = lastChar;
    lastChar = std::getchar();
    return thisChar;
}

int main(void) {
    return 0;
}