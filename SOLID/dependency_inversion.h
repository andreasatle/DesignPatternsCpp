#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "solid.h"

using namespace std;

class DependencyInversion : public Solid {};

enum class Relationship {
    parent,
    child,
    sibling
};

string relstr(Relationship r) {
    switch(r) {
    case Relationship::parent:
        return "parent";
    case Relationship::child:
        return "child";
    case Relationship::sibling:
        return "sibling";
    }

    return "NA";
}
struct Person {
    string name;
};

typedef tuple<Person, Relationship, Person> RelationTuple;

class RelationshipBrowser : public DependencyInversion {
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};
/// Class Relationship is a low-level abstraction.

/// We have explicitly defined a vector.
class Relationships : public RelationshipBrowser {
private:

public:
    vector<RelationTuple> relations;
    void add_parent_and_child(const Person& parent, const Person& child) {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    void add_siblings(const Person& sibling1, const Person& sibling2) {
        relations.push_back({sibling1, Relationship::sibling, sibling2});
        relations.push_back({sibling2, Relationship::sibling, sibling1});
    }

    string str() {
        stringstream buffer;
        buffer << "Relationships" << endl;
        for (auto& r : relations) {
            buffer
                << get<0>(r).name
                << " is a "
                << relstr(get<1>(r))
                << " of "
                << get<2>(r).name
                << "."
                << endl;
        }
        return buffer.str();
    }

    vector<Person> find_all_children_of(const string& name) override {
        vector<Person> result;
        for (auto&& [first, rel, second] : relations) {
            if (first.name == name && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};

/// Class ResearchBad violate the Dependency Inversion Principle.

/// The class use the internal structure of a low-level class.
/// We loop over a vector defined in the low-level class.
class ResearchBad : public DependencyInversion {
public:
    ResearchBad(Relationships &relationships) {
        for (auto&& [first, rel, second] : relationships.relations) {
            if (rel == Relationship:: parent) {
                cout << first.name << " is a parent of " << second.name << "." << endl;
            }
        }
    }
};

/// Class ResearchGood obeys the Dependency Inversion Principle.

class ResearchGood : public DependencyInversion {
public:
    ResearchGood(Relationships &relationships) {
        const string name = "Andreas";
        for (auto&& child : relationships.find_all_children_of(name)) {
            cout << name << " is a parent of " << child.name << "." << endl;
        }
    }
};
