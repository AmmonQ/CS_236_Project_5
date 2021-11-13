//
// Created by cppq on 9/23/2021.
//

#ifndef CS_236_PROJECT_2_PREDICATE_H
#define CS_236_PROJECT_2_PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    string name;
    vector<Parameter> parameters;
public:
    Predicate();
    Predicate(string predicateName, vector<Parameter> parameters);
    string toString();
    vector<Parameter> getParameters();
    vector<string> getParametersString();
    int getParameterSize();
    Parameter getParameter(int index);
    void setName(string newName);
    void addParameter(Parameter parameter);
    string getName() const;
};


#endif //CS_236_PROJECT_2_PREDICATE_H
