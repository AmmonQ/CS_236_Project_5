//
// Created by cppq on 10/8/2021.
//

#include "Tuple.h"

Tuple::Tuple() {

}

Tuple::~Tuple() {

}

vector<string> Tuple::getValues() {
    return values;
}

string Tuple::getValue(int index) const {
    return values.at(index);
}

void Tuple::addValue(string newValue) {
    values.push_back(newValue);
}

void Tuple::setValues(vector<string> newValuesVector) {
    values = newValuesVector;
}

int Tuple::getValuesSize() const {
    return values.size();
}