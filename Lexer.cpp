#include "Automaton.h"
#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "PeriodAutomaton.h"
#include "CommaAutomaton.h"
#include "QMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "UndefinedStringAutomaton.h"
#include "UndefinedBlockCommentAutomaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // clean up the memory in `automata` and `tokens`
    for (Automaton *a: automata) {
        delete a;
    }
    automata.clear();

    for (Token *t: tokens) {
        delete t;
    }
    tokens.clear();
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new UndefinedStringAutomaton());
    automata.push_back(new UndefinedBlockCommentAutomaton());
}

std::vector<Token*> Lexer::GetTokens() {
    return tokens;
}

void Lexer::PrintTokens() {
    for (Token *token : tokens) {
        std::cout << token->toString() << std::endl;
    }
    std::cout << "Total Tokens = " << tokens.size();

    return;
}

void Lexer::Run(std::string& input) {
    int maxRead;
    int lineNumber;
    Automaton *maxAutomaton;

    lineNumber = 1;
    // While there are more characters to tokenize
    while (!input.empty()) {
        while (input.size() > 0) {
            maxRead = 0;
            maxAutomaton = automata[0];

            // handle whitespace in between tokens
            while (isspace(input[0])) {
                if (input[0] == '\n') {
                    lineNumber++;
                }
                input.erase(0, 1);
            }

            // Here is the "Parallel" part of the algorithm
            for (Automaton *a: automata) {
                int inputRead = a->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = a;
                }
            }

            // Here is the "Max" part of the algorithm
            if (maxRead > 0) {
                string properFormatInput = input.substr(0, maxRead);

                Token *newToken = maxAutomaton->CreateToken(properFormatInput, lineNumber);
                lineNumber += maxAutomaton->NewLinesRead();

                // do not save comment tokens
                if (newToken->getType() != TokenType::COMMENT) {
                    tokens.push_back(newToken);
                }
            } else {
                if (input.empty()) {
                    break;
                }

                maxRead = 1;

                Token *newToken = new Token(TokenType::UNDEFINED, std::string(1, input[0]), lineNumber);
                tokens.push_back(newToken);
            }

            input.erase(0, maxRead);
        }
    }

    tokens.push_back(new Token(TokenType::EOF_TOKEN, "", lineNumber));
}