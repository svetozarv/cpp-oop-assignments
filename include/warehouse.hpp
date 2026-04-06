#pragma once
#include <vector>
#include "product.hpp"

class Warehouse {
    std::vector<Product> products_;

  public:
    Warehouse();
    Warehouse(const std::vector<Product>& products);
    void addProduct(const Product& product);
    const std::vector<Product>& getProducts() const;
    std::vector<Product> &getProducts();
};
