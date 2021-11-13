//
// Created by cppq on 9/23/2021.
//

#ifndef CS_236_PROJECT_2_PARAMETER_H
#define CS_236_PROJECT_2_PARAMETER_H


#include <string>

class Parameter {
private:
    // parameter -> STRING | ID
    std::string value;
public:
    Parameter();
    Parameter(std::string stringOrId);
    std::string toString();
    void setValue(std::string newValue);
};


#endif //CS_236_PROJECT_2_PARAMETER_H
