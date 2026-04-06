#pragma once
#include <string>

class Product {
    std::string name_;
    double price_;
    int quantity_;

  public:
    Product(const std::string& name, double price);
    Product(const std::string& name, double price, int quantity);
    const std::string& getName() const;
    double getPrice() const;
    int getQuantity() const;
    void setQuantity(int quantity);
    bool operator<(const Product& other) const;
};
