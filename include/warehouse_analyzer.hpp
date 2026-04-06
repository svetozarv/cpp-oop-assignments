#pragma once
#include <string>
#include <vector>
#include "product.hpp"
// #include "warehouse.hpp"

class Warehouse;    // Forward declaration

class WarehouseAnalyzer {
    static std::vector<double> getProductPrices(const Warehouse& warehouse);
    static std::vector<double> getProductValues(const Warehouse& warehouse);
  public:
    static double calculateTotalValue(const Warehouse& warehouse);
    static Product getTheMostExpensiveOne(const Warehouse& warehouse);
    static std::vector<Product> getTheMostExpensiveHalf(const Warehouse& warehouse);
    static void increasePricesOfProductsBelowMedian(Warehouse& warehouse, double percentage);
};
