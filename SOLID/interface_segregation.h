#pragma once

#include <iostream>
#include "solid.h"


/// Class InterfaceSegregationPrinciple is the super-class of the document example.
class InterfaceSegregationPrinciple : public Solid {};

/// Document to be handled.
struct Document {};

/// Class IMachineBad has routines for all possible actions.
class IMachineBad : public InterfaceSegregationPrinciple {
public:
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
};

void ok(const string str) {
    cout << str << ": This is ok!" << endl;
}

void not_ok(const string str) {
    cout << str << ": This is not ok!" << endl;
}

class MultiFunctionPrinter : public IMachineBad {
private:
    const string info = "MultiFunctionPrinter";
public:
    void print(Document& doc) override {
        ok(info);
    }
    void scan(Document& doc) override {
        ok(info);
    }
    void fax(Document& doc) override {
        ok(info);
    }
};

class ScannerBad : public IMachineBad {
private:
    const string info = "ScannerBad";
public:
    void print(Document& doc) override {
        // A scanner can't print.
        not_ok(info);
    }
    void scan(Document& doc) override {
        ok(info);
    }
    void fax(Document& doc) override {
        // A scanner can't fax.
        not_ok(info);
    }
};

class IPrinter : public InterfaceSegregationPrinciple {
public:
    virtual void print(Document& doc) = 0;
};

class Printer : public IPrinter {
private:
    const string info = "Printer";
public:
    void print(Document& doc) override {
        ok(info);
    }
};
class IScanner : public InterfaceSegregationPrinciple {
public:
    virtual void scan(Document& doc) = 0;
};

class Scanner : public IScanner {
private:
    const string info = "Scanner";
public:
    void scan(Document& doc) override {
        ok(info);
    }
};

class IFaxer : public InterfaceSegregationPrinciple {
public:
    virtual void fax(Document& doc) = 0;
};

class Faxer : public IFaxer {
private:
    const string info = "Faxer";
public:
    void fax(Document& doc) override {
        ok(info);
    }
};

class IMachineGood : public IPrinter, public IScanner {};

class Machine : public IMachineGood {
private:
    IPrinter& printer;
    IScanner& scanner;
public:
    Machine(IPrinter& _printer, IScanner& _scanner) : printer{_printer}, scanner{_scanner} {}
    void print(Document& doc) override {
        printer.print(doc);
    }
    void scan(Document& doc) override {
        scanner.scan(doc);
    }
};