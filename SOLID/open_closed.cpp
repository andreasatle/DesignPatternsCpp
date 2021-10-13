#include "open_closed.h"

vector<Product*> ProductFilter::by_color(vector<Product*> items, Color color) {
    vector<Product*> result;
    for (auto& item : items) {
        if (item->color == color) {
            result.push_back(item);
        }
    }
    return result;
}

vector<Product*> ProductFilter::by_size(vector<Product*> items, Size size) {
    vector<Product*> result;
    for (auto& item : items) {
        if (item->size == size) {
            result.push_back(item);
        }
    }
    return result;
}

vector<Product*> ProductFilter::by_size_and_color(vector<Product*> items, Size size, Color color) {
    vector<Product*> result;
    for (auto& item : items) {
        if (item->size == size && item->color == color) {
            result.push_back(item);
        }
    }
    return result;
}

