#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "solid.h"
#include "open_closed.h"

/// Template Class Specification contains the filter criteria.
template <typename T> class Specification : public OpenClosedPrinciple {
public:
    /// verify that criteria is met.
    /// @param item is the item to be verified.
    /// @returns true if criteria is met.
    virtual bool is_satisfied(T* item) = 0;
};

/// Template Class Filter contains the filter-routine.

/// This filter fulfills the Open Closed Principle, since we create a new
/// Specification class for each new criteria to be filtered for.
template <typename T> class Filter : public OpenClosedPrinciple {
public:
    /// Method find filters by the given Specification.
    /// @param item is a vector of pointers.
    /// @param spec is an instance of Specification.
    vector<T*> find(vector<T*> items, Specification<T>& spec) {
        vector<T*> result;
        for (auto& item : items) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

/// Template Class AndSpecification filters by conjunction of two criterias.
template <typename T> class AndSpecification : public Specification<T> {
public:
    /// Constructor for conjunction filter.
    AndSpecification(Specification<T>& _first, Specification<T>& _second) : first{_first}, second{_second} {}

    /// Implements the Specification interface with conjunction.
    bool is_satisfied(Product* item) {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }

private:
    Specification<T>& first;
    Specification<T>& second;
};

/// The Class ColorSpecification implements a filter by color for Products.
class ColorSpecification : public Specification<Product> {
public:
    /// Constructor for the Class ColorSpecification.
    /// @param _color is the color to be filtered for.
    ColorSpecification(Color _color) : color{_color} {}

    /// Implements the Specification interface for color-filter.
    bool is_satisfied(Product* item) {
        return item->color == color;
    }
private:
    Color color;
};

/// The Class SizeSpecification implements a filter by size for Products.
class SizeSpecification : public Specification<Product> {
public:
    /// Constructor for the Class SizeSpecification.
    /// @param _size is the size to be filtered for.
    SizeSpecification(Size _size) : size{_size} {}

    /// Implements the Specification interface for size-filter.
    bool is_satisfied(Product* item) {
        return item->size == size;
    }
private:
    Size size;
};

/// Overloading the &&-operator that creates an instance of AndSpecification.
/// @param first is the first Specification argument.
/// @param second is the second Specification argument.
template <typename T> AndSpecification<T> operator&&(Specification<T>& first, Specification<T>& second) {
    return AndSpecification<T>(first, second);
}
