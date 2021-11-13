//
// Created by cppq on 9/23/2021.
//

#include "Parameter.h"

Parameter::Parameter() {
    return;
}

Parameter::Parameter(std::string stringOrId) {
    this->value = stringOrId;
}

std::string Parameter::toString() {
    return value;
}

void Parameter::setValue(std::string newValue) {
    value = newValue;
}