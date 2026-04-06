#include "../include/product.hpp"

// --------- Product class implementation ---------
Product::Product(const std::string &name, double price)
    : name_(name), price_(price), quantity_(1) {}


Product::Product(const std::string &name, double price, int quantity)
    : name_(name), price_(price), quantity_(quantity) {}


const std::string& Product::getName() const {
    return name_;
}

double Product::getPrice() const {
    return price_;
}

int Product::getQuantity() const {
    return quantity_;
}

void Product::setQuantity(int quantity) {
    quantity_ = quantity;
}

bool Product::operator<(const Product &other) const {
    return price_ < other.price_;
}
