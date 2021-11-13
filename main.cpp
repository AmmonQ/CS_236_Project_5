#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char** argv) {
    Lexer* lexer = new Lexer();

    string fileName = argv[1];
    ifstream input(fileName);

    string inputString;

    if (!input.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
    }

    while (input.peek() != EOF) {
        // get next character
        inputString += input.get();
    }

    lexer->Run(inputString);

    vector<Token *> tokens = lexer->GetTokens();

    Parser parser = Parser();
    string result = parser.Parse(tokens);

    //cout << result << endl;

    DatalogProgram datalogProgram1 = parser.getDatalogProgram();

    Interpreter interpreter = Interpreter(datalogProgram1);
    interpreter.evaluateAllRules();
    interpreter.evaluateAllQueries();

    /*if (result == "Success!") {
        DatalogProgram datalogProgram = parser.getDatalogProgram();
        cout << datalogProgram.toString() << endl;
    }*/

    delete lexer;

    return 0;
}