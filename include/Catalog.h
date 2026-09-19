#ifndef CATALOG_H
#define CATALOG_H

#include "ProductRecord.h"
#include <unordered_map>

// unorderedmap of product records, keyed by itemID
const std::unordered_map<int, ProductRecord> catalog;

const ProductRecord& getProductById(int itemID);

#endif // CATALOG_H
