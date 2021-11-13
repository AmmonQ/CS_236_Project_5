//
// Created by cppq on 9/23/2021.
//

#include "Predicate.h"

Predicate::Predicate(string predicateName, vector<Parameter> parameters) {
    this->name = predicateName;
    this->parameters = parameters;
}

Predicate::Predicate() {
    return;
}

Parameter Predicate::getParameter(int index) {
    return parameters.at(index);
}

int Predicate::getParameterSize() {
    return parameters.size();
}

string Predicate::getName() const {
    return name;
}

vector<Parameter> Predicate::getParameters() {
    return parameters;
}

vector<string> Predicate::getParametersString() {
    vector<string> returnVector;

    for (unsigned int i = 0; i < parameters.size(); i++) {
        returnVector.push_back(parameters.at(i).toString());
    }

    return returnVector;
}

void Predicate::setName(string newName) {
    name = newName;
}

void Predicate::addParameter(Parameter parameter) {
    parameters.push_back(parameter);
}

string Predicate::toString() {
    string finalString;

    // predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    finalString += name;
    finalString += "(";

    for (unsigned int i = 0; i < parameters.size(); i++) {
        finalString += parameters.at(i).toString();

        // trailing commas for all but the last one
        if (i < parameters.size() - 1) {
            finalString += ",";
        }
    }

    finalString += ")";

    return finalString;
}