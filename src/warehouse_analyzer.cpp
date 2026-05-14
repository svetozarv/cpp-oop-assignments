#include "../include/warehouse_analyzer.hpp"
#include "../include/warehouse.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ranges>

// Ignore quantities, just prices
std::vector<double> WarehouseAnalyzer::getProductPrices(const Warehouse &warehouse) {
    auto prices = warehouse.getProducts()
    | std::views::transform([](const Product& product) { return product.getPrice(); });
    return std::vector<double>(prices.begin(), prices.end());
}

std::vector<double> WarehouseAnalyzer::getProductValues(const Warehouse &warehouse) {
    auto values = warehouse.getProducts()
    | std::views::transform([](const Product& product) { return product.getPrice() * product.getQuantity(); });
    return std::vector<double>(values.begin(), values.end());
}

double WarehouseAnalyzer::calculateTotalValue(const Warehouse &warehouse) {
    std::vector<double> values = getProductValues(warehouse);
    return std::accumulate(values.begin(), values.end(), 0.0);
}

Product WarehouseAnalyzer::getTheMostExpensiveOne(const Warehouse &warehouse) {
    std::vector<Product> products = warehouse.getProducts();
    return *std::max_element(products.begin(), products.end());
}

// Get all the products which prices(not values) are above the mean price
std::vector<Product> WarehouseAnalyzer::getTheMostExpensiveHalf(const Warehouse &warehouse) {
    auto prices = getProductPrices(warehouse);
    double mean = std::accumulate(prices.begin(), prices.end(), 0.0) / prices.size();

    std::vector<Product> result{};
    std::copy_if(warehouse.getProducts().begin(), warehouse.getProducts().end(), std::back_inserter(result), [mean](const Product& product) {
        return product.getPrice() > mean;
    });
    return result;
}

// Increase the prices of all products which prices are below the median price by a given percentage
void WarehouseAnalyzer::increasePricesOfProductsBelowMedian(Warehouse &warehouse, double percentage) {
    std::vector<Product> &products = warehouse.getProducts();
    auto median = products.begin() + products.size() / 2;
    std::nth_element(products.begin(), median, products.end());
    std::transform(products.begin(), median, products.begin(), [percentage](const Product& product) {
        double new_price = product.getPrice() * (1 + percentage / 100);
        return Product(product.getName(), new_price, product.getQuantity());
    });
}
