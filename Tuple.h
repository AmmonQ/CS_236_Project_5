//
// Created by cppq on 10/8/2021.
//

#ifndef CS_236_PROJECT_3_TUPLE_H
#define CS_236_PROJECT_3_TUPLE_H

#include <vector>
#include <string>

using namespace std;

class Tuple {
private:
    vector<string> values;
public:
    bool operator< (const Tuple &other) const {
        if (values < other.values) {
            return true;
        } else {
            return false;
        }
    };
    Tuple();
    ~Tuple();
    vector<string> getValues();
    string getValue(int index) const;
    void addValue(string newValue);
    void setValues(vector<string> newValuesVector);
    int getValuesSize() const;
};


#endif //CS_236_PROJECT_3_TUPLE_H
