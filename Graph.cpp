//
// Created by ammon on 11/19/21.
//

#include "Graph.h"

Graph::Graph() {

}

map<int, set<int>> Graph::returnAdjacencyList() {
    return adjacencyList;
}

set<int> Graph::getAdjacencySet(int vertex, bool reverse) {
    if (reverse) {
        return reverseAdjacencyList.at(vertex);
    } else {
        return adjacencyList.at(vertex);
    }
}

void Graph::addAdjacencyToSet(int vertex, int adjacentVertex, map<int, set<int>> &workingAdjacencyList) {
    workingAdjacencyList.at(vertex).insert(adjacentVertex);
}

void Graph::addAdjacencyLineTesting(int key, set<int> newListLine) {
    adjacencyList.insert(pair<int, set<int>>(key, newListLine));
}

void Graph::addAdjacencyLine(int key, set<int> listOfAdjacentVertices, map<int, set<int>> &workingAdjacencyList) {
    workingAdjacencyList.insert(pair<int, set<int>>(key, listOfAdjacentVertices));
}

void Graph::addVertex(int newVertex, map<int, set<int>> &workingAdjacencyList) {
    addAdjacencyLine(newVertex, set<int>(), workingAdjacencyList);
}

void Graph::PrintAdjacencyList(bool printReverse) {
    cout << "Dependency Graph\n";

    map<int, set<int>> workingAdjacencyList;

    if (printReverse) {
        workingAdjacencyList = reverseAdjacencyList;
    } else {
        workingAdjacencyList = adjacencyList;
    }

    string output;

    for (auto line: workingAdjacencyList) {
        output += "R" + to_string(line.first) + ":";
        for (auto dependency: line.second) {
            output += "R" + to_string(dependency) + ",";
        }

        if (output.back() == ',') {
            output.pop_back();
        }

        output += "\n";
    }

    cout << output;
}

void Graph::createDependencyGraph(vector<Rule> rulesFromDatalog) {
    // PUSH RULES_FROM_DATALOG INTO ADJACENCY LIST VERTEX COLUMN
    for (unsigned int i = 0; i < rulesFromDatalog.size(); i++) {
        addVertex(i, adjacencyList);
    }

    // first for loop: go through rules (the ones from the datalog program)
    for (unsigned int i = 0; i < rulesFromDatalog.size(); i++) {
        // second for loop: go through the body predicates
        for (int j = 0; j < rulesFromDatalog.at(i).getPredicateListSize(); j++) {
            // third for loop: search rules again to see if bodyPredicate is a rule
            // and get the name
            for (unsigned int k = 0; k < rulesFromDatalog.size(); k++) {
                if (rulesFromDatalog.at(i).getPredicate(j).getName() ==
                    rulesFromDatalog.at(k).getHeadPredicate().getName()) {
                    // adjacent vertex to adjacency list
                    addAdjacencyToSet(i, k, adjacencyList);
                }
            }
        }
    }
}

// only call this after createDependencyGraph()
void Graph::createReverseDependencyGraph() {
    for (unsigned int i = 0; i < adjacencyList.size(); i++) {
        addVertex(i, reverseAdjacencyList);
    }

    // first for loop: go through each vertex in the adjacency list
    for (auto const &line: adjacencyList) {
        // second for loop: go through the adjacency vertices
        for (auto adjacency_vertex: line.second) {
            // third for loop: find where terminal vertex matches initial vertex,
            // then add initial vertex to reverse adjacency list
            for (int i = 0; i < getAdjacencyListSize(); i++) {
                if (adjacency_vertex == i) {
                    addAdjacencyToSet(adjacency_vertex, line.first, reverseAdjacencyList);
                }
            }
        }
    }
}

int Graph::getAdjacencyListSize() {
    return adjacencyList.size();
}

vector<int> Graph::getPostOrderOnTree(map<int, set<int>> graph) {
    vector<int> postOrder;

    for (auto const &line: reverseAdjacencyList) {
        depthFirstSearch(line.first, postOrder, graph);
    }

    return postOrder;
}

void Graph::depthFirstSearch(int ruleNumber, vector<int> &postOrderVector, map<int, set<int>> graph) {
    if (find(visitedVertices.begin(), visitedVertices.end(), ruleNumber) != visitedVertices.end()) {
        return;
    } else {
        // mark v
        visitedVertices.push_back(ruleNumber);

        // for each vertex w adjacent from v
        if (graph.at(ruleNumber).size() == 0) {
            postOrderVector.push_back(ruleNumber);
        } else {
            for (const auto &adjacentVertex: graph.at(ruleNumber)) {
                // if w is not marked
                if (find(visitedVertices.begin(), visitedVertices.end(), adjacentVertex) == visitedVertices.end()) {
                    depthFirstSearch(adjacentVertex, postOrderVector, graph);
                }
            }
            postOrderVector.push_back(ruleNumber);
        }
    }
}

vector<int> Graph::getPostOrderOnForest(vector<map<int, set<int>>> forest) {
    vector<int> postOrder = {};

    for (unsigned int i = 0; i < forest.size(); i++) {
        vector<int> tempOrder = {};
        tempOrder = getPostOrderOnTree(forest.at(i));
        postOrder.insert(postOrder.end(), tempOrder.begin(), tempOrder.end());
    }

    return postOrder;
}

vector<map<int, set<int>>> Graph::depthFirstSearchForest(map<int, set<int>> tree) {
    visitedVertices.clear();

    vector<map<int, set<int>>> forest;

    for (auto const& vertex : tree) {
        if (find(visitedVertices.begin(), visitedVertices.end(), vertex.first) == visitedVertices.end()) {
            visitedVertices.push_back(vertex.first);

            map<int, set<int>> outputTree = depthFirstSearchForTree(vertex.first, tree);

            forest.push_back(outputTree);
        }
    }

    return forest;
}

map<int, set<int>> Graph::depthFirstSearchForTree(int ruleNumber, map<int, set<int>> graph) {
    map<int, set<int>> tree;

    depthFirstSearchTree(ruleNumber, tree, graph);

    if (tree.size() == 0) {
        tree.insert(pair<int, set<int>>(ruleNumber, set<int>()));
    }

    return tree;
}

void Graph::depthFirstSearchTree(int ruleNumber, map<int, set<int>> &tree, map<int, set<int>> graph) {
    if (graph.at(ruleNumber).size() == 0) {
        return;
    }

    for (auto const& vertex : graph.at(ruleNumber)) {
        if (find(visitedVertices.begin(), visitedVertices.end(), vertex) == visitedVertices.end()) {
            visitedVertices.push_back(vertex);

            if (tree.find(ruleNumber) == tree.end()) {
                tree.insert(pair<int, set<int>>(ruleNumber, set<int>()));
            }

            tree.at(ruleNumber).insert(vertex);
            depthFirstSearchTree(vertex, tree, graph);
        }
    }
}

vector<map<int, set<int>>> Graph::getStronglyConnectedComponents() {
    vector<int> reversedGraphPostOrder = {};
    vector<map<int, set<int>>> sccForest = {};

    visitedVertices.clear();

    reversedGraphPostOrder = getPostOrderOnTree(reverseAdjacencyList);

    visitedVertices.clear();

    for (int i = reversedGraphPostOrder.size() - 1; i >= 0; i--) {
        if (find(visitedVertices.begin(), visitedVertices.end(), reversedGraphPostOrder.at(i)) == visitedVertices.end()) {
            visitedVertices.push_back(reversedGraphPostOrder.at(i));

            map<int, set<int>> outputTree = depthFirstSearchForTree(reversedGraphPostOrder.at(i), adjacencyList);

            sccForest.push_back(outputTree);
        }
    }

    return sccForest;
}

map<int, set<int>> Graph::getReverseDependencyGraph() {
    return reverseAdjacencyList;
}

void Graph::printSCCs(map<int, set<int>> tree) {
    cout << "===========================\n";

    for (auto line: tree) {
        cout << line.first << "\t| ";
        for (auto dependency: line.second) {
            cout << dependency << " ";
        }
        cout << endl;
    }
}