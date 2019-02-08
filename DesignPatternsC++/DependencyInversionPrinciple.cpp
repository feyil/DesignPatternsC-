#include "pch.h"
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <vector>
#include<fstream>
#include <tuple>

using namespace std;

// A. High levle modules should not depend on low-level modules.
// Both should depend on abstractions.
// B. Abstractions should not depend on details.
// Details should depend on abstractions

enum class Relationship {
	parent, 
	child,
	sibling
};

class Person {
private:
	string m_name;
public:
	Person(string name) : m_name(name) {

	}
public:
	string get_name() { return m_name; }
	void set_name(string name) { this->m_name = name; }
};

struct IRelationshipBrowser {
	virtual vector<Person> find_all_children_of(const string& name) = 0;
};

class Relationships : public IRelationshipBrowser {
	// low level
private:
	vector<tuple<Person, Relationship, Person>> relations;
public:
	void add_parent_and_child(const Person& parent, const Person& child) {
		relations.push_back({ parent, Relationship::parent, child });
		relations.push_back({ child, Relationship::child, parent });
	}

	vector<Person> find_all_children_of(const string &name) override {
		vector<Person> result;
		for (auto&& a : relations) {
			Person first = get<0>(a);
			Relationship rel = get<1>(a);
			Person second = get<2>(a);
			
			if (first.get_name() == name && rel == Relationship::parent) {
				result.push_back(second);
			}
		}
		return result;
	}
};

class Research {
	// high level
public:
	Research(IRelationshipBrowser& browser) {
		for (auto& child : browser.find_all_children_of("John")) {
			cout << "John has a child called " << child.get_name() << endl;
		}
	}

	//  Research(const Relationships& relationships)
	//  {
	//    auto& relations = relationships.relations;
	//    for (auto&& [first, rel, second] : relations)
	//    {
	//      if (first.name == "John" && rel == Relationship::parent)
	//      {
	//        cout << "John has a child called " << second.name << endl;
	//      }
	//    }
	//  }

};

int main() {
	Person parent{ "John" };
	Person child1{ "Chris" };
	Person child2{ "Matt" };

	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships);
}