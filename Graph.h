//
// Created by ammon on 11/19/21.
//

#ifndef CS_236_PROJECT_5_GRAPH_H
#define CS_236_PROJECT_5_GRAPH_H

#include <set>
#include <map>
#include "Rule.h"
#include <iostream>
#include <algorithm>

using namespace std;

class Graph {
private:
    map<int, set<int>> adjacencyList;
    map<int, set<int>> reverseAdjacencyList;
    vector<int> visitedVertices;
public:
    Graph();
    set<int> getAdjacencySet(int vertex, bool reverse = false);
    void addAdjacencyToSet(int key, int newValue, map<int, set<int>>& workingAdjacencyList);
    void addAdjacencyLine(int key, set<int> newListLine, map<int, set<int>>& workingAdjacencyList);
    void addAdjacencyLineTesting(int key, set<int> newListLine);
    map<int, set<int>> returnAdjacencyList();
    map<int, set<int>>& returnAdjacencyListByReference();
    // add vertex without adjacency set
    void addVertex(int newVertex, map<int, set<int>>& workingAdjacencyList);

    void createDependencyGraph(vector<Rule> rulesFromDatalog);
    void createReverseDependencyGraph();

    map<int, set<int>> getReverseDependencyGraph();

    void PrintAdjacencyList(bool printReverse = false);

    vector<int> getPostOrderOnTree(map<int, set<int>> graph);
    void depthFirstSearch(int ruleNumber, vector<int>& postOrderVector, map<int, set<int>> graph);
    vector<int> getPostOrderOnForest(vector<map<int, set<int>>> forest);
    vector<map<int, set<int>>> depthFirstSearchForest(map<int, set<int>> tree);
    map<int, set<int>> depthFirstSearchForTree(int ruleNumber, map<int, set<int>> graph);
    void depthFirstSearchTree(int ruleNumber, map<int, set<int>> &tree, map<int, set<int>> graph);

    vector<map<int, set<int>>> getStronglyConnectedComponents();

    // for testing
    void printSCCs(map<int, set<int>> tree);
    int getAdjacencyListSize();
};


#endif //CS_236_PROJECT_5_GRAPH_H
