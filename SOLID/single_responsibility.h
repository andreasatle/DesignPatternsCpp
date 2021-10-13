#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "solid.h"

using namespace std;

/// Class SingleResponsibilityPrinciple is the super-class for the journal example.

/// The class contains one example of a class Journal that violate the Single
/// Responsibility Principle. It is better to create a new class PersistenceManager
/// that handles the storage of the data. This could then be generalized to store
/// more things than journals. If we would change the storage type and e.g. use a
/// database, then we should only have to modify this class.
class SingleResponsibilityPrinciple : public Solid {};

/// Class Journal contains a journal with entries.

/// This class exemplifies the Single Responsibility Principle in the SOLID
/// Design Principles. The only objective of this class should be to keep
/// the journal entries and to be able to add entries into the journal.
///
/// The method save is violating the Single Responsibility Principle.
/// A better way to manage persistence is to use a separate class
/// e.g. PersistenceManager that handles the storage of any data.

class Journal : public SingleResponsibilityPrinciple {
public:
    /// Constructor creates a new Journal with a title.
    /// @param _title The title of the journal.
    Journal(const string& _title);

    /// Add one entry to the journal.
    /// @param entry The entry to add to the journal.
    void add_entry(const string& entry);

    /// Convert a journal to a string.
    string str() const;

    /// Save the journal to a file.

    /// This routine violates the Single Responsibility Principle.
    /// @param filename The filename to save to.
    void bad_save(const string& filename);
private:
    string title;
    vector<string> entries;
};

/// Class PersistenceManager contains routines that stores data to e.g. disk.

/// If we change the format of the storage, we should only have to change
/// this class.
class PersistenceManager : public SingleResponsibilityPrinciple {
public:
    /// Save a journal to a file.
    ///
    /// This routine obeys the Single Responsibility Principle.
    /// @param journal is an instance of Journal.
    /// @param filename is the name of the file to write to.
    void good_save(const Journal& journal, const string& filename);
};

