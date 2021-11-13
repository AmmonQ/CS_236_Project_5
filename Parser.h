//
// Created by cppq on 9/11/2021.
//

#ifndef CS_236_PROJECT_2_PARSER_H
#define CS_236_PROJECT_2_PARSER_H

#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "DatalogProgram.h"

class Parser {
private:
    std::vector<Token *> tokens;
    int currentTokenIndex;
    DatalogProgram datalogProgram;

    DatalogProgram parseDatalogProgram();
    vector<Predicate> parseSchemeList();
    vector<Predicate> parseFactList();
    vector<Rule> parseRuleList();
    vector<Predicate> parseQueryList();
    Predicate parseScheme();
    Predicate parseFact();
    Rule parseRule();
    Predicate parseQuery();
    Predicate parseHeadPredicate();
    Predicate parsePredicate();
    void parsePredicateList(Rule& rule);
    void parseParameterList(Predicate &predicate);
    void parseStringList(Predicate &factPredicate);
    void parseIdList(Predicate& myPredicate);
    Parameter parseParameter();
    Token* getNextToken();
public:
    Parser();
    ~Parser();
    string Parse(std::vector<Token *> newTokens);
    void matchAndIncrement(TokenType tokenToCompare);
    Token* getCurrentToken();
    DatalogProgram getDatalogProgram();
};


#endif //CS_236_PROJECT_2_PARSER_H
