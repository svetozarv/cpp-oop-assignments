#include "../include/warehouse_analyzer.hpp"

// --------- Warehouse class implementation ---------
Warehouse::Warehouse()
    : products_(std::vector<Product>()) {}


Warehouse::Warehouse(const std::vector<Product> &products)
    : products_(products) {}


void Warehouse::addProduct(const Product &product) {
    products_.push_back(product);
}

const std::vector<Product> &Warehouse::getProducts() const {
    return products_;
}

std::vector<Product> &Warehouse::getProducts() {
    return products_;
}
