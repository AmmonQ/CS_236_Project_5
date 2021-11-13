//
// Created by cppq on 9/11/2021.
//

#include "Parser.h"

#include <utility>

Parser::Parser() {
    // only increment when next thing is a terminal
    currentTokenIndex = 0;
}

Parser::~Parser() {
    return;
}

DatalogProgram Parser::getDatalogProgram() {
    return datalogProgram;
}

void Parser::matchAndIncrement(TokenType tokenToCompare) {
    if (tokens.at(currentTokenIndex)->getType() == tokenToCompare) {
        currentTokenIndex++;
        return;
    } else {
        throw getCurrentToken()->toString();
    }
}

Token *Parser::getCurrentToken() {
    return this->tokens.at(currentTokenIndex);
}

Token *Parser::getNextToken() {
    int index = 1 + currentTokenIndex - 1;

    return this->tokens.at(index);
}

string Parser::Parse(std::vector<Token *> newTokens) {
    tokens = newTokens;

    try {
        datalogProgram = parseDatalogProgram();
    } catch (string error) {
        return "Failure!\n  " + error;
    }

    return "Success!";
}

DatalogProgram Parser::parseDatalogProgram() {

    DatalogProgram program = DatalogProgram();

    matchAndIncrement(TokenType::SCHEMES);
    matchAndIncrement(TokenType::COLON);

    Predicate scheme = parseScheme();
    vector<Predicate> schemeList = parseSchemeList();

    schemeList.insert(schemeList.begin(), scheme);

    matchAndIncrement(TokenType::FACTS);
    matchAndIncrement(TokenType::COLON);

    vector<Predicate> factList = parseFactList();

    matchAndIncrement(TokenType::RULES);
    matchAndIncrement(TokenType::COLON);

    vector<Rule> ruleList = parseRuleList();

    matchAndIncrement(TokenType::QUERIES);
    matchAndIncrement(TokenType::COLON);

    Predicate query = parseQuery();

    vector<Predicate> queryList = parseQueryList();

    queryList.insert(queryList.begin(), query);

    matchAndIncrement(TokenType::EOF_TOKEN);

    return DatalogProgram(schemeList, factList, ruleList, queryList);
}

vector<Predicate> Parser::parseSchemeList() {
    static vector<Predicate> schemeVector;

    if (getNextToken()->getType() == TokenType::ID) {
        schemeVector.push_back(parseScheme());
        parseSchemeList();
    } else if (getNextToken()->getType() == TokenType::FACTS) {         // lambda
        return schemeVector;
    } else {
        throw getCurrentToken()->toString();
    }

    return schemeVector;
}

vector<Predicate> Parser::parseFactList() {
    static vector<Predicate> factVector;

    if (getNextToken()->getType() == TokenType::ID) {
        factVector.push_back(parseFact());
        parseFactList();
    } else if (getNextToken()->getType() == TokenType::RULES) {
        return factVector;
    } else {
        throw getCurrentToken()->toString();
    }

    return factVector;
}

vector<Rule> Parser::parseRuleList() {
    static vector<Rule> ruleVector;

    if (getNextToken()->getType() == TokenType::ID) {
        ruleVector.push_back(parseRule());
        parseRuleList();
    } else if (getNextToken()->getType() == TokenType::QUERIES) {
        return ruleVector;
    } else {
        throw getCurrentToken()->toString();
    }

    return ruleVector;
}

vector<Predicate> Parser::parseQueryList() {
    static vector<Predicate> queryVector;

    if (getNextToken()->getType() == TokenType::ID) {
        queryVector.push_back(parseQuery());
        parseQueryList();
    } else if (getNextToken()->getType() == TokenType::EOF_TOKEN) {
        return queryVector;
    } else {
        throw getCurrentToken()->toString();
    }

    return queryVector;
}

Predicate Parser::parseScheme() {
    Predicate schemePredicate = Predicate();

    matchAndIncrement(TokenType::ID);

    schemePredicate.setName(tokens.at(currentTokenIndex - 1)->getValue());

    matchAndIncrement(TokenType::LEFT_PAREN);
    matchAndIncrement(TokenType::ID);

    schemePredicate.addParameter(tokens.at(currentTokenIndex - 1)->getValue());

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseIdList(schemePredicate);
    }

    matchAndIncrement(TokenType::RIGHT_PAREN);

    return schemePredicate;
}

Predicate Parser::parseFact() {
    Predicate factPredicate = Predicate();

    matchAndIncrement(TokenType::ID);

    factPredicate.setName(tokens.at(currentTokenIndex - 1)->getValue());

    matchAndIncrement(TokenType::LEFT_PAREN);
    matchAndIncrement(TokenType::STRING);

    factPredicate.addParameter(tokens.at(currentTokenIndex - 1)->getValue());

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseStringList(factPredicate);
    } else if (getNextToken()->getType() == TokenType::RIGHT_PAREN) {
        matchAndIncrement(TokenType::RIGHT_PAREN);
        matchAndIncrement(TokenType::PERIOD);

        return factPredicate;
    } else {
        throw getCurrentToken()->toString();
    }

    matchAndIncrement(TokenType::RIGHT_PAREN);
    matchAndIncrement(TokenType::PERIOD);

    return factPredicate;
}

Rule Parser::parseRule() {
    Rule rule = Rule();

    if (getNextToken()->getType() == TokenType::ID) {
        rule.setHeadPredicate(parseHeadPredicate());
    } else {
        throw getCurrentToken()->toString();
    }

    matchAndIncrement(TokenType::COLON_DASH);

    if (getNextToken()->getType() == TokenType::ID) {
        rule.addPredicateToList(parsePredicate());
    } else {
        throw getCurrentToken()->toString();
    }

    if (getNextToken()->getType() == TokenType::COMMA) {
        parsePredicateList(rule);
    }

    matchAndIncrement(TokenType::PERIOD);

    return rule;
}

Predicate Parser::parseQuery() {
    Predicate query;

    if (getNextToken()->getType() == TokenType::ID) {
        query = parsePredicate();
    } else {
        throw getCurrentToken()->toString();
    }

    matchAndIncrement(TokenType::Q_MARK);

    return query;
}

Predicate Parser::parseHeadPredicate() {
    Predicate headPredicate = Predicate();

    matchAndIncrement(TokenType::ID);

    headPredicate.setName(tokens.at(currentTokenIndex - 1)->getValue());

    matchAndIncrement(TokenType::LEFT_PAREN);
    matchAndIncrement(TokenType::ID);

    headPredicate.addParameter(tokens.at(currentTokenIndex - 1)->getValue());

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseIdList(headPredicate);
    }

    matchAndIncrement(TokenType::RIGHT_PAREN);

    return headPredicate;
}

Predicate Parser::parsePredicate() {
    Predicate newPredicate = Predicate();

    matchAndIncrement(TokenType::ID);
    newPredicate.setName(tokens.at(currentTokenIndex - 1)->getValue());
    matchAndIncrement(TokenType::LEFT_PAREN);

    if (getNextToken()->getType() == TokenType::STRING || getNextToken()->getType() == TokenType::ID) {
        newPredicate.addParameter(parseParameter());
    } else {
        throw getCurrentToken()->toString();
    }

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseParameterList(newPredicate);
    }

    if (getNextToken()->getType() == TokenType::RIGHT_PAREN) {
        currentTokenIndex++;
        return newPredicate;
    } else {
        throw getCurrentToken()->toString();
    }

}

void Parser::parsePredicateList(Rule &rule) {
    matchAndIncrement(TokenType::COMMA);

    if (getNextToken()->getType() == TokenType::ID) {
        rule.addPredicateToList(parsePredicate());
    } else {
        throw getCurrentToken()->toString();
    }

    if (getNextToken()->getType() == TokenType::COMMA) {
        parsePredicateList(rule);
    }
    if (getNextToken()->getType() == TokenType::PERIOD) {
        return;
    } else {
        throw getCurrentToken()->toString();
    }
}

void Parser::parseParameterList(Predicate &predicate) {
    matchAndIncrement(TokenType::COMMA);

    if (getNextToken()->getType() == TokenType::STRING || getNextToken()->getType() == TokenType::ID) {
        predicate.addParameter(parseParameter());
    } else {
        throw getCurrentToken()->toString();
    }

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseParameterList(predicate);
    }

    if (getNextToken()->getType() == TokenType::RIGHT_PAREN) {
        return;
    } else {
        throw getCurrentToken()->toString();
    }
}

void Parser::parseStringList(Predicate &factPredicate) {
    matchAndIncrement(TokenType::COMMA);
    matchAndIncrement(TokenType::STRING);

    factPredicate.addParameter(tokens.at(currentTokenIndex - 1)->getValue());

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseStringList(factPredicate);
    } else if (getNextToken()->getType() == TokenType::RIGHT_PAREN) {
        return;
    } else {
        throw getCurrentToken()->toString();
    }
}

void Parser::parseIdList(Predicate &myPredicate) {
    matchAndIncrement(TokenType::COMMA);
    matchAndIncrement(TokenType::ID);

    myPredicate.addParameter(tokens.at(currentTokenIndex - 1)->getValue());

    if (getNextToken()->getType() == TokenType::COMMA) {
        parseIdList(myPredicate);
    } else if (getNextToken()->getType() == TokenType::RIGHT_PAREN) {
        return;
    } else {
        throw getCurrentToken()->toString();
    }
}

Parameter Parser::parseParameter() {
    Parameter newParameter = Parameter();

    if (getNextToken()->getType() == TokenType::STRING || getNextToken()->getType() == TokenType::ID) {
        newParameter.setValue(getNextToken()->getValue());
        currentTokenIndex++;
        return newParameter;
    } else {
        throw getCurrentToken()->toString();
    }
}