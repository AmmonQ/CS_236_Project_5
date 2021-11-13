//
// Created by cppq on 10/8/2021.
//

#include "Header.h"

#include <utility>

Header::Header() {
    //attributes = vector<string>();
}

Header::~Header() {

}

int Header::getAttributesSize() {
    return attributes.size();
}

vector<string> Header::getAttributes() {
    return attributes;
}

void Header::addAttribute(string newAttribute) {
    attributes.push_back(newAttribute);
}

void Header::setAttributes(vector<string> newAttributes) {
    attributes = std::move(newAttributes);
}

string Header::getAttribute(int index) {
    return attributes.at(index);
}

void Header::setAttribute(int index, string newAttribute) {
    attributes.at(index) = newAttribute;
}