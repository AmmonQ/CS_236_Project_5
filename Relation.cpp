//
// Created by cppq on 10/8/2021.
//

#include <algorithm>
#include "Relation.h"

Relation::Relation() {
    //header = nullptr;
}

Relation::~Relation() {

}

void Relation::addHeaderAttribute(string input) {
    header.addAttribute(input);
}

void Relation::setHeader(Header newHeader) {
    header = newHeader;
}

Relation Relation::select(int position, string value) {
    Relation newRelation;

    newRelation.setName(name);
    newRelation.setHeader(header);


    for (const Tuple &t: rows) {
        if (t.getValue(position) == value) {
            newRelation.addTuple(t);
        }
    }

    return newRelation;
}

Relation Relation::select(int position1, int position2) {
    Relation newRelation;

    newRelation.setName(name);
    newRelation.setHeader(header);

    for (const Tuple &t: rows) {
        if (t.getValue(position1) == t.getValue(position2)) {
            newRelation.addTuple(t);
        }
    }

    return newRelation;
}

Relation Relation::rename(vector<string> newHeaderValues) {
    Relation newRelation;
    Header newHeader;

    newRelation.setName(name);

    for (unsigned int i = 0; i < newHeaderValues.size(); i++) {
        newHeader.addAttribute(newHeaderValues.at(i));
    }

    newRelation.setHeader(newHeader);

    newRelation.setRows(rows);

    return newRelation;
}

Relation Relation::project(vector<int> columnPositions) {
    Relation newRelation;

    vector<int> seenHeaders;

    newRelation.setName(name);

    for (unsigned int i = 0; i < columnPositions.size(); i++) {
        if (find(seenHeaders.begin(), seenHeaders.end(), columnPositions.at(i)) == seenHeaders.end()) {
            newRelation.addHeaderAttribute(header.getAttribute(columnPositions.at(i)));
            seenHeaders.push_back(columnPositions.at(i));
        }
    }

    vector<string> seenTupleValues;

    for (const Tuple &t: rows) {
        Tuple x;

        for (unsigned int i = 0; i < columnPositions.size(); i++) {
            x.addValue(t.getValue(columnPositions.at(i)));
        }

        newRelation.addTuple(x);
    }

    return newRelation;
}

Relation Relation::project(vector<string> columnNames) {
    vector<int> indexes;

    for (unsigned int i = 0; i < columnNames.size(); i++) {
        for (int j = 0; j < header.getAttributesSize(); j++) {
            // if the header attribute (aka column names) are the same
            if (columnNames.at(i) == header.getAttribute(j)) {
                indexes.push_back(j);
            }
        }
    }

    return project(indexes);

}

void Relation::setName(string newName) {
    name = newName;
}

string Relation::getName() {
    return name;
}

bool Relation::addTuple(Tuple newTuple) {
    return rows.insert(newTuple).second;
}

set<Tuple> Relation::getRows() {
    return rows;
}

void Relation::setRows(set<Tuple> newTupleSet) {
    rows = newTupleSet;
}

Header Relation::getHeader() {
    return header;
}

string Relation::toString(bool allConstants) {
    string returnString;

    if (rows.empty()) {
        returnString += "No\n";
    } else if (allConstants) {
        returnString += "Yes(" + to_string(rows.size()) + ")\n";
    } else {
        returnString += "Yes(" + to_string(rows.size()) + ")\n";

        for (const Tuple &t: rows) {
            returnString += "  ";

            int variableSize = 0;

            vector<string> uniqueHeaders;
            vector<int> uniqueTuplesPos;

            for (int i = 0; i < getHeaderAttributeSize(); i++) {
                if (find(uniqueHeaders.begin(), uniqueHeaders.end(), getHeader().getAttribute(i)) ==
                    uniqueHeaders.end()) {
                    uniqueHeaders.push_back(getHeader().getAttribute(i));
                    uniqueTuplesPos.push_back(i);
                }
            }

            for (unsigned int i = 0; i < uniqueHeaders.size(); i++) {
                if (uniqueHeaders.at(i)[0] != '\'') {
                    variableSize++;
                }
            }

            for (unsigned int i = 0; i < uniqueHeaders.size(); i++) {
                if (uniqueHeaders.at(i)[0] != '\'') {
                    returnString += uniqueHeaders.at(i) + "=" + t.getValue(uniqueTuplesPos.at(i));
                    returnString += ", ";
                }
            }

            // remove commas at the end of lines
            returnString.pop_back();
            returnString.pop_back();

            returnString += "\n";
        }
    }

    return returnString;
}

Header Relation::combineHeaders(Header h1) {
    Header newHeader;

    vector<string> attributes;

    for (int i = 0; i < header.getAttributesSize(); i++) {
        attributes.push_back(header.getAttribute(i));
    }

    for (int i = 0; i < h1.getAttributesSize(); i++) {
        bool found = false;

        for (int j = 0; j < this->header.getAttributesSize(); j++) {
            if (h1.getAttribute(i) == header.getAttribute(j)) {
                found = true;
                break;
            }
        }

        if (!found) {
            attributes.push_back(h1.getAttribute(i));
        }
    }

    newHeader.setAttributes(attributes);

    return newHeader;
}

bool Relation::isJoinable(Tuple t1, Tuple t2, vector<int> r1Pos, vector<int> r2Pos) {
    // if the position vectors are not the same size
    if (r1Pos.size() != r2Pos.size()) {
        return false;
    }

    for (unsigned int i = 0; i < r1Pos.size(); i++) {
        if (t1.getValue(r1Pos.at(i)) != t2.getValue(r2Pos.at(i))) {
            return false;
        }
    }

    return true;
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2, vector<int> indexes2) {
    Tuple newTuple;

    vector<string> values;

    for (int i = 0; i < t1.getValuesSize(); i++) {
        //newTuple.addValue(t1.getValue(i));
        values.push_back(t1.getValue(i));
    }

    for (int i = 0; i < t2.getValuesSize(); i++) {
        bool found = false;

        for (unsigned int j = 0; j < indexes2.size(); j++) {
            if (i == indexes2.at(j)) {
                found = true;
                break;
            }
        }

        if (!found) {
            values.push_back(t2.getValue(i));
        }
    }

    newTuple.setValues(values);

    return newTuple;
}

Relation Relation::join(Relation inputRelation) {
    Relation newRelation;

    vector<int> table1Pos;
    vector<int> table2Pos;

    // 1. Combine the two Headers
    Header combinedHeaders = combineHeaders(inputRelation.getHeader());
    newRelation.setHeader(combinedHeaders);

    // 2. Go through every pair of tuples
    // figure out the indexes of the header attributes that match
    for (int i = 0; i < header.getAttributesSize(); i++) {
        for (int j = 0; j < inputRelation.getHeaderAttributeSize(); j++) {
            if (header.getAttribute(i) == inputRelation.getHeader().getAttribute(j)) {
                //if (find(table1Pos.begin(), table1Pos.end(), i) == table1Pos.end()) {
                table1Pos.push_back(i);
                //}
                //if (find(table2Pos.begin(), table2Pos.end(), j) == table2Pos.end()) {
                table2Pos.push_back(j);
                //}
            }
        }
    }
    for (const Tuple &t1: rows) {
        for (const Tuple &t2: inputRelation.rows) {

            // 2a. see if you can combine the tuples
            if (isJoinable(t1, t2, table1Pos, table2Pos)) {
                // 2b. if the tuples can be combined, combine them
                Tuple newTuple = combineTuples(t1, t2, table2Pos);
                newRelation.addTuple(newTuple);
            }
        }
    }

    return newRelation;
}

Relation Relation::Union(Relation ruleEvalResult) {
    Relation newRelation;

    for (int i = 0; i < header.getAttributesSize(); i++) {
        newRelation.addHeaderAttribute(header.getAttribute(i));
    }

    for (const Tuple &t: rows) {
        newRelation.addTuple(t);
    }

    for (const Tuple &t: ruleEvalResult.rows) {
        if (rows.insert(t).second) {
            newRelation.addTuple(t);
        }
    }

    return newRelation;
}

int Relation::getHeaderAttributeSize() {
    return header.getAttributesSize();
}