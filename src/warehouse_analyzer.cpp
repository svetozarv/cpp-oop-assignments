#include "warehouse_analyzer.hpp"
#include <string>
#include <vector>
#include <algorithm>

double WarehouseAnalyzer::calculateTotalValue(const Warehouse &warehouse) {
    std::vector<Product> products = warehouse.getProducts();
    std::vector<double> values;

    std::transform(products.begin(), products.end(), std::back_inserter(values), [](const Product& product) {
        return product.getPrice() * product.getQuantity();
    });
    return std::accumulate(values.begin(), values.end(), 0.0);
}

Product WarehouseAnalyzer::getTheMostExpensiveOne(const Warehouse &warehouse) {
    std::vector<Product> products = warehouse.getProducts();
    return *std::max_element(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.getPrice() < b.getPrice();
    });
}

std::vector<Product> WarehouseAnalyzer::getTheMostExpensiveHalf(const Warehouse &warehouse) {
    auto mean = calculateTotalValue(warehouse) / warehouse.getProducts().size();
    std::vector<Product> products = warehouse.getProducts();
    std::vector<Product> result;
    std::copy_if(products.begin(), products.end(), std::back_inserter(result), [mean](const Product& product) {
        return product.getPrice() > mean;
    });
    return result;
}

void WarehouseAnalyzer::increasePricesOfSelected(const Warehouse &warehouse, int treshold, double percentage) {
    
}
