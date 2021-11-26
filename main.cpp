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

    Graph graph = Graph();
    graph.createDependencyGraph(datalogProgram1.getRules());
    graph.createReverseDependencyGraph();
    vector<int> postOrder = graph.getPostOrderOnTree(graph.getReverseDependencyGraph());

    /*cout << "\npost order: ";

    for (auto i : postOrder) {
        cout << i << " ";
    }*/

    vector<map<int, set<int>>> SCCs = graph.getStronglyConnectedComponents();
    graph.PrintAdjacencyList();
    cout << endl << "Rule Evaluation" << endl;
    /*cout << "\n\nSCCs:\n";

    for (auto i : SCCs) {
        graph.printSCCs(i);
    }*/
    interpreter.evaluateAllRulesSCCs(SCCs);

    cout << endl;
    interpreter.evaluateAllQueries();

    /*if (result == "Success!") {
        DatalogProgram datalogProgram = parser.getDatalogProgram();
        cout << datalogProgram.PrintAdjacencyList() << endl;
    }*/

    // testing project 5 as we go
    /*Graph graph = Graph();
    graph.addAdjacencyLineTesting(0, set<int>());
    graph.addAdjacencyLineTesting(1, set<int>{2});
    graph.addAdjacencyLineTesting(2, set<int>{0,1,3});
    graph.addAdjacencyLineTesting(3, set<int>{0,1,3});
    graph.addAdjacencyLineTesting(4, set<int>{0,1,2,3});
    graph.addAdjacencyLineTesting(5, set<int>());
    graph.addAdjacencyLineTesting(6, set<int>{4,5,7,8});
    graph.addAdjacencyLineTesting(7, set<int>{5,6,7,8});
    graph.addAdjacencyLineTesting(8, set<int>{5,7,8});

    // step 1
    graph.PrintAdjacencyList();

    // step 2
    graph.createReverseDependencyGraph();
    graph.PrintAdjacencyList(true);

    // step 3
    vector<int> postOrder = graph.getPostOrderOnTree(graph.getReverseDependencyGraph());

    cout << "\npost order: ";
    for (auto i : postOrder) {
        cout << i << " ";
    }

    // step 4
    vector<map<int, set<int>>> SCCs = graph.getStronglyConnectedComponents();

    cout << "\n\nSCCs:\n";

    for (auto i : SCCs) {
        graph.printSCCs(i);
    }*/

    delete lexer;

    return 0;
}