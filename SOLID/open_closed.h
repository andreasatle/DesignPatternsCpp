#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "solid.h"

using namespace std;

/// Class OpenClosedPrinciple is the super-class of the class ProductFilter.
class OpenClosedPrinciple : public Solid {};

/// Enum Class Color contains different colors.
enum class Color {red, green, blue};

/// Enum Class Size contains different sizes.
enum class Size {small, medium, large};

/// Product is a struct with a name, color and size.
struct Product {
    string name;
    Color color;
    Size size;
};

/// class ProductFilter filter Products with different criterias.

/// This structure violates the Open Closed Principle, since the class
/// has to be modified everytime we want to filter with a new criteria.
/// The number of filters can grow very fast.
class ProductFilter : public OpenClosedPrinciple {
public:
    /// Filter by color.
    /// @param items is a vector of products.
    /// @param color is the color to sort by.
    vector<Product*> by_color(vector<Product*> items, Color color);

    /// Filter by size.
    /// @param items is a vector of products.
    /// @param size is the size to sort by.
    vector<Product*> by_size(vector<Product*> items, Size size);

    /// Filter by size and color.
    /// @param items is a vector of products.
    /// @param size is the size to sort by.
    /// @param color is the color to sort by.
    vector<Product*> by_size_and_color(vector<Product*> items, Size size, Color color);
};

