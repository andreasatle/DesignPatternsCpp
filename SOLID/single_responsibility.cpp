#include "single_responsibility.h"

Journal::Journal(const string& _title) : title(_title) {}

void Journal::add_entry(const string& entry) {
    static int count = 1;
    entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
}

string Journal::str() const {
    stringstream buffer;
    buffer << title << endl;
    for (auto& e : entries)
        buffer << "  " << e << endl;
    return buffer.str();
}

void Journal::bad_save(const string& filename) {
        ofstream ofs(filename);
    ofs << this->str();
}

void PersistenceManager::good_save(const Journal& journal, const string& filename) {
    ofstream ofs(filename);
    ofs << journal.str();
}
