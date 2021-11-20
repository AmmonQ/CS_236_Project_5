//
// Created by ammon on 11/19/21.
//

#ifndef CS_236_PROJECT_5_GRAPH_H
#define CS_236_PROJECT_5_GRAPH_H

#include <set>
#include <map>
#include "Rule.h"
#include <iostream>

using namespace std;

class Graph {
private:
    map<int, set<int>> adjacencyList;
    map<int, set<int>> reverseAdjacencyList;
public:
    Graph();
    set<int> getAdjacencySet(int vertex);
    void addAdjacencyToSet(int key, int newValue, map<int, set<int>>& workingAdjacencyList);
    void addAdjacencyLine(int key, set<int> newListLine, map<int, set<int>>& workingAdjacencyList);
    map<int, set<int>> returnAdjacencyList();
    // add vertex without adjacency set
    void addVertex(int newVertex, map<int, set<int>>& workingAdjacencyList);

    void createDependencyGraph(vector<Rule> rulesFromDatalog);
    void createReverseDependencyGraph();

    void PrintAdjacencyList(bool printReverse = false);
};


#endif //CS_236_PROJECT_5_GRAPH_H
