//
// Created by cppq on 10/8/2021.
//

#ifndef CS_236_PROJECT_3_DATABASE_H
#define CS_236_PROJECT_3_DATABASE_H

#include <map>
#include "Relation.h"

class Database {
private:
    map<string, Relation> relations;
public:
    Database();
    ~Database();
    void setRelations(map<string, Relation> newRelation);
    map<string, Relation> getRelations();
    map<string, Relation>& getRelationsByReference();
    void addRelation(string name, Relation newRelation);
    Relation& getRelationByReference(string key);
    Relation getRelation(string key);
    int getTupleAmount();
};


#endif //CS_236_PROJECT_3_DATABASE_H
