//
// Created by cppq on 10/8/2021.
//

#ifndef CS_236_PROJECT_3_HEADER_H
#define CS_236_PROJECT_3_HEADER_H

#include <vector>
#include <string>

using namespace std;

class Header {
private:
    vector<string> attributes;
public:
    Header();
    ~Header();
    vector<string> getAttributes();
    void setAttributes(vector<string> newAttributes);
    void addAttribute(string newAttribute);
    string getAttribute(int index);
    void setAttribute(int index, string newAttribute);
    int getAttributesSize();
};


#endif //CS_236_PROJECT_3_HEADER_H
