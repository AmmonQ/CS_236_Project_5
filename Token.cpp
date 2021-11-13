#include "Token.h"

using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    lineNum = line;
    value = description;
    tokenType = type;
}

TokenType Token::getType() {
    return tokenType;
}

int Token::getLineNum() {
    return lineNum;
}

string Token::getTokenTypeAsString() {
    switch(tokenType) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::ADD:
            return "ADD";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::RULES:
            return "RULES";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::ID:
            return "ID";
        case TokenType::STRING:
            return "STRING";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        case TokenType::EOF_TOKEN:
            return "EOF";
        default:
            return "OTHER";
    }
}

string Token::toString() {
    string tokenTypeString = getTokenTypeAsString();

    string returnString = "(" + tokenTypeString + ",\"" + value + "\"," + to_string(lineNum) + ")";

    return returnString;
}

string Token::getValue() {
    return value;
}