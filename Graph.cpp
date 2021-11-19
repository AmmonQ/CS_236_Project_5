//
// Created by ammon on 11/19/21.
//

#include "Graph.h"

Graph::Graph() {

}

map<int, set<int>> Graph::returnAdjacencyList() {
    return adjacencyList;
}

set<int> Graph::getAdjacencySet(int vertex) {
    return adjacencyList.at(vertex);
}

void Graph::addAdjacencyToSet(int vertex, int adjacentVertex) {
    adjacencyList.at(vertex).insert(adjacentVertex);
}

void Graph::addAdjacencyLine(int key, set<int> listOfAdjacentVertices) {
    adjacencyList.insert(pair<int, set<int>>(key, listOfAdjacentVertices));
}

void Graph::createDependencyGraph(vector<Rule> rulesFromDatalog) {
    // for loop to push rules into ruleNumbers OR PUSH RULES_FROM_DATALOG INTO ADJACENTY LIST VERTEX COLUMN
    for (int i = 0; i < rulesFromDatalog.size(); i++) {
        ruleNumbers.push_back(i);
    }

    // first for loop: go through rules (the ones from the datalog program)
    for (int i = 0; i < rulesFromDatalog.size(); i++) {
        // second for loop: go through the body predicates
        for (int j = 0; j < rulesFromDatalog.at(i).getPredicateListSize(); j++) {
            // third for loop: search rules again to see if bodyPredicate is a rule
            // and get the name
            for (int k = 0; k < rulesFromDatalog.size(); k++) {
                if (rulesFromDatalog.at(i).getPredicate(j).getName() == rulesFromDatalog.at(i).getHeadPredicate().getName()) {
                    // adjacent vertex to adjacency list
                }
            }
        }
    }
}

void Graph::createReverseDependencyGraph(vector<Rule> rulesFromDatalog) {

}