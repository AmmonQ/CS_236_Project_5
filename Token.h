#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TOKEN
};

class Token
{
private:
    string value;
    int lineNum;         // line number token starts on
    TokenType tokenType;
public:
    Token(TokenType type, std::string description, int line);
    string toString();
    int getLineNum();
    TokenType getType();
    string getTokenTypeAsString();
    string getValue();
};

#endif // TOKEN_H

