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

void Graph::addAdjacencyLine(int key, set<int> listOfAdjacentVertices, map<int, set<int>> &workingAdjacencyList) {
    workingAdjacencyList.insert(pair<int, set<int>>(key, listOfAdjacentVertices));
}

void Graph::addVertex(int newVertex, map<int, set<int>> &workingAdjacencyList) {
    addAdjacencyLine(newVertex, set<int>(), workingAdjacencyList);
}

void Graph::PrintAdjacencyList(bool printReverse) {
    cout << "\nVertex | Adjacency Vertices\n===========================\n";

    map<int, set<int>> workingAdjacencyList;

    if (printReverse) {
        workingAdjacencyList = reverseAdjacencyList;
    } else {
        workingAdjacencyList = adjacencyList;
    }

    for (auto line: workingAdjacencyList) {
        cout << line.first << "\t| ";
        for (auto dependency: line.second) {
            cout << dependency << " ";
        }
        cout << endl;
    }
}

void Graph::createDependencyGraph(vector<Rule> rulesFromDatalog) {
    // PUSH RULES_FROM_DATALOG INTO ADJACENCY LIST VERTEX COLUMN
    for (int i = 0; i < rulesFromDatalog.size(); i++) {
        addVertex(i, adjacencyList);
    }

    // first for loop: go through rules (the ones from the datalog program)
    for (int i = 0; i < rulesFromDatalog.size(); i++) {
        // second for loop: go through the body predicates
        for (int j = 0; j < rulesFromDatalog.at(i).getPredicateListSize(); j++) {
            // third for loop: search rules again to see if bodyPredicate is a rule
            // and get the name
            for (int k = 0; k < rulesFromDatalog.size(); k++) {
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
    for (int i = 0; i < adjacencyList.size(); i++) {
        addVertex(i, reverseAdjacencyList);
    }

    // first for loop: go through each vertex in the adjacency list
    for (auto const &line: adjacencyList) {
        // second for loop: go through the adjacency vertices
        for (auto const &adjacency_vertex: line.second) {
            // third for loop: find where terminal vertex matches initial vertex,
            // then add initial vertex to reverse adjacency list
            for (int i = 0; i < adjacencyList.size(); i++) {
                if (adjacency_vertex == i) {
                    addAdjacencyToSet(adjacency_vertex, line.first, reverseAdjacencyList);
                }
            }
        }
    }
}

vector<int> Graph::getPostOrderOnTree() {
    vector<int> postOrder;

    for (auto const &line: reverseAdjacencyList) {
        depthFirstSearch(line.first, postOrder);
    }

    return postOrder;
}

void Graph::depthFirstSearch(int ruleNumber, vector<int> &postOrderVector) {
    if (find(visitedVertices.begin(), visitedVertices.end(), ruleNumber) != visitedVertices.end()) {
        return;
    } else {
        // mark v
        visitedVertices.push_back(ruleNumber);

        // for each vertex w adjacent from v
        if (getAdjacencySet(ruleNumber, true).size() == 0) {
            postOrderVector.push_back(ruleNumber);
        } else {
            for (const auto &adjacentVertex: getAdjacencySet(ruleNumber, true)) {
                // if w is not marked
                if (find(visitedVertices.begin(), visitedVertices.end(), adjacentVertex) == visitedVertices.end()) {
                    depthFirstSearch(adjacentVertex, postOrderVector);
                }
            }
            postOrderVector.push_back(ruleNumber);
        }
    }
}