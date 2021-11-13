//
// Created by cppq on 10/8/2021.
//

#ifndef CS_236_PROJECT_3_RELATION_H
#define CS_236_PROJECT_3_RELATION_H

#include <string>
#include <set>
#include "Header.h"
#include "Tuple.h"
#include "Relation.h"

using namespace std;

class Relation {
private:
    string name;
    Header header;
    set<Tuple> rows;
public:
    Relation();
    ~Relation();
    Relation select(int position, string value);
    Relation select(int position1, int position2);
    Relation project(vector<int> columnPositions);
    Relation project(vector<string> columnNames);
    Relation rename(vector<string> newHeaderValues);
    string toString(bool allConstants);
    string getName();
    void setName(string newName);
    Header getHeader();
    void addHeaderAttribute(string input);
    void setHeader(Header newHeader);
    set<Tuple> getRows();
    void setRows(set<Tuple> newTupleSet);
    bool addTuple(Tuple newTuple);
    int getHeaderAttributeSize();

    // project 4 methods
    Relation Union(Relation ruleEvalResult);
    Relation join(Relation inputRelation);
    Header combineHeaders(Header h1);
    bool isJoinable(Tuple t1, Tuple t2, vector<int> r1Pos, vector<int> r2Pos);
    Tuple combineTuples(Tuple t1, Tuple t2, vector<int>indexes2);
};


#endif //CS_236_PROJECT_3_RELATION_H
