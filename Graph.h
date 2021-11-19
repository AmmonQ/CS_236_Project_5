//
// Created by ammon on 11/19/21.
//

#ifndef CS_236_PROJECT_5_GRAPH_H
#define CS_236_PROJECT_5_GRAPH_H

#include <set>
#include <map>
#include "Rule.h"

using namespace std;

class Graph {
private:
    map<int, set<int>> adjacencyList;
    vector<int> ruleNumbers;
public:
    Graph();
    set<int> getAdjacencySet(int vertex);
    void addAdjacencyToSet(int key, int newValue);
    void addAdjacencyLine(int key, set<int> newListLine);
    map<int, set<int>> returnAdjacencyList();

    void createDependencyGraph(vector<Rule> rulesFromDatalog);
    void createReverseDependencyGraph(vector<Rule> rulesFromDatalog);
};


#endif //CS_236_PROJECT_5_GRAPH_H
