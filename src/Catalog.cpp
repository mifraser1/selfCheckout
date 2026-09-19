#include "ProductRecord.h"
#include "Catalog.h"
#include <unordered_map>
#include <stdexcept>

const std::unordered_map<int, ProductRecord> catalog = {
    // Hardcoded product catalog for testing: {index, name, price, weight, tax, quantity, pricing type, age restriction}
    std::pair<const int, ProductRecord>{1, ProductRecord{1, "Gum", 1.50, 0.0, 0.07, 100, PricingType::PerUnit, false}},
    std::pair<const int, ProductRecord>{2, ProductRecord{2, "Apples", 2.99, 1.0, 0.07, 50, PricingType::PerWeight, false}},
    std::pair<const int, ProductRecord>{3, ProductRecord{3, "Salad", 5.99, 0.0, 0.14, 20, PricingType::PerUnit, false}},
    std::pair<const int, ProductRecord>{4, ProductRecord{4, "Beer", 12.99, 0.0, 0.07, 12, PricingType::PerUnit, true}}
};

const ProductRecord& getProductById(int itemID) {
    auto it = catalog.find(itemID);
    if (it != catalog.end()) {
        return it->second;
    }
    throw std::out_of_range("Product ID not found: " + std::to_string(itemID));
}