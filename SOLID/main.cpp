#include "single_responsibility.h"
#include "open_closed.h"
#include "open_closed.hpp"
#include "liskov_substitution.h"
#include "interface_segregation.h"
#include "dependency_inversion.h"

using namespace std;

void single_responsibility() {
    cout << endl << "== Single Responsibility Principle ==" << endl;

    Journal journal{"Dear Diary"};
    journal.add_entry("I ate a bug.");
    journal.add_entry("I cried today.");
    journal.add_entry("It's a beautiful day.");

    // Write journal to stout.
    cout << journal.str() << endl;

    // Bad way of storing the journal.
    journal.bad_save("journal.txt");

    // Good way of storing the journal.
    PersistenceManager pm;
    pm.good_save(journal, "pm-journal.txt");
    cout << endl;
}

void open_closed() {
    cout << endl << "== Open Closed Principle ==" << endl;
    // Create the data
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};
    Product watermelon{"Watermelon", Color::green, Size::large};

    vector<Product*> items{&apple, &tree, &house, &watermelon};
    for (auto& item : items) {
        cout << item->name << endl;
    }

    // Bad filter, that violate the Open Closed Principle.
    ProductFilter pf;
    auto bad_green_things = pf.by_color(items, Color::green);
    for (auto& item : bad_green_things) {
        cout << item->name << " is green" << endl;
    }

    auto bad_large_things = pf.by_size(items, Size::large);
    for (auto& item : bad_large_things) {
        cout << item->name << " is large" << endl;
    }

    auto bad_large_green_things = pf.by_size_and_color(items, Size::large, Color::green);
    for (auto& item : bad_large_green_things) {
        cout << item->name << " is large and green" << endl;
    }

    // Good filter, that builds the filter using a Specification.
    Filter<Product> filter;

    ColorSpecification green(Color::green);
    auto good_green_things = filter.find(items, green);

    for (auto& item : good_green_things) {
        cout << item->name << " is green" << endl;
    }

    SizeSpecification large(Size::large);
    auto good_large_things = filter.find(items, large);

    for (auto& item : good_large_things) {
        cout << item->name << " is large" << endl;
    }

    // Half-good way of creating a conjunction of two specifications.
    AndSpecification large_and_green(large, green);
    auto good_large_green_things = filter.find(items, large_and_green);

    for (auto& item : good_large_green_things) {
        cout << item->name << " is large and green" << endl;
    }

    // Better way of creating a conjunction, where the type can be hidden.
    // We still need to instantiate the conjunction, with an overloaded &&-operator.
    auto large_and_green2 = large && green;
    auto good_large_green_things2 = filter.find(items, large_and_green2);

    for (auto& item : good_large_green_things2) {
        cout << item->name << " is large and green 2" << endl;
    }
    cout << endl;
}

void liskov_substitution() {
    cout << endl << "== Liskov Substitution Principle ==" << endl;

    // Use constructor and the stringer.
    Rectangle rectangle(10, 5);
    cout << rectangle.str() << endl;

    // Modify with setter routines.
    rectangle.setWidth(8);
    rectangle.setHeight(7);
    cout << rectangle.str() << endl;

    // Process rectangle with rectangle logic.
    process(rectangle);

    // Use square constructor and rectangle stringer.
    Square square(12);
    cout << square.str() << endl;

    // Process square with rectangle logic.
    process(square);
    cout << endl;
}

void interface_segregation() {
    cout << endl << "== Interface Segregation Principle ==" << endl;
    Document doc;
    MultiFunctionPrinter mfp;
    ScannerBad scannerBad;
    Printer printer;
    Scanner scanner;
    Machine machine(printer, scanner);
    mfp.print(doc);
    mfp.scan(doc);
    mfp.fax(doc);
    scannerBad.print(doc);
    scannerBad.scan(doc);
    scannerBad.fax(doc);
    machine.print(doc);
    machine.scan(doc);
    cout << endl;
}

void dependency_inversion() {
    cout << endl << "== Dependency Inversion Principle ==" << endl;
    Person parent{"Andreas"};
    Person son{"Anton"};
    Person daughter{"Annelie"};
    Relationships rel;
    rel.add_parent_and_child(parent, son);
    rel.add_parent_and_child(parent, daughter);
    rel.add_siblings(son, daughter);
    cout << rel.str() << endl;
    ResearchBad _1(rel);
    ResearchGood _2(rel);
    cout << endl;
}

int main() {
    single_responsibility();
    open_closed();
    liskov_substitution();
    interface_segregation();
    dependency_inversion();
    return 0;
}