#include "pch.h"
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <vector>
#include<fstream>

using namespace std;

class Journal {
public:
	Journal(const string& title) : m_title{ title } {

	}
	string get_title() { return m_title; }
	vector<string> get_entries() { return m_entries; }
	void add(const string& entry);

	// persistence is a separete concern
	void save(const string& filename);

private:
	string m_title;
	vector<string> m_entries;
};

void Journal::add(const string& entry) {
	static int count = 1;
	m_entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
}

void Journal::save(const string& filename) {
	ofstream ofs(filename);
	for (auto& s : m_entries)
		ofs << s << endl;
}

class PersistenceManager {
public:
	static void save(Journal& j, const string& filename) {
		ofstream ofs(filename);
		for (string& s : j.get_entries())
			ofs << s << endl;
	}
};

int main()
{
	// stack allocation
	Journal journal{ "Dear Diary" };
	journal.add("I ate a bug");
	journal.add("I cried today");

	// journal.save("diary.txt");

	PersistenceManager::save(journal, "diary.txt");

}
