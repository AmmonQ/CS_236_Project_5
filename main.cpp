#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "Interpreter.h"
#include "Graph.h"

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
        cout << datalogProgram.PrintAdjacencyList() << endl;
    }*/

    // testing project 5 as we go
    Graph testGraph = Graph();
    testGraph.createDependencyGraph(datalogProgram1.getRules());
    cout << "\nAdjacency List:\n";
    testGraph.PrintAdjacencyList();
    testGraph.createReverseDependencyGraph();
    cout << "\nReverse Adjacency List:\n";
    testGraph.PrintAdjacencyList(true);

    vector<int> testPostOrderVector = testGraph.getPostOrderOnTree();

    cout << "\ntest post order vector: \n";

    for (auto const& v : testPostOrderVector) {
        cout << v << " ";
    }

    delete lexer;

    return 0;
}