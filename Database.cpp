//
// Created by cppq on 10/8/2021.
//

#include "Database.h"

Database::Database() {

}

Database::~Database() {

}

int Database::getTupleAmount() {
    int total = 0;
    map<string, Relation>::iterator it;

    for (it = relations.begin(); it != relations.end(); it++) {
        total += it->second.getRows().size();
    }

    return total;
}

int Database::getTupleAmountInRelation(string key) {
    return relations.at(key).getRows().size();
}

void Database::setRelations(map<string, Relation> newRelation) {
    relations = newRelation;
}

map<string, Relation> Database::getRelations() {
    return relations;
}

map<string, Relation> &Database::getRelationsByReference() {
    return relations;
}

Relation &Database::getRelationByReference(string key) {
    return relations.at(key);
}

Relation Database::getRelation(string key) {
    return relations.at(key);
}

void Database::addRelation(string name, Relation newRelation) {
    relations.insert(pair<string, Relation>(name, newRelation));
}