#include "../include/warehouse_analyzer.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

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
    std::vector<Product> products = warehouse.getProducts();
    auto items_it = std::find_if(products.begin(), products.end(), [treshold](const Product& product) {
        return product.getQuantity() < treshold;
    });
    std::transform(items_it, products.end(), items_it, [percentage](Product& product) {
        double new_price = product.getPrice() * (1 + percentage / 100);
        return Product(product.getName(), new_price, product.getQuantity());
    });
}
