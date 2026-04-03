#pragma once
#include <string>
#include <vector>


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
};

class Warehouse {
    std::vector<Product> products_;

  public:
    Warehouse();
    Warehouse(const std::vector<Product>& products);
    void addProduct(const Product& product);
    const std::vector<Product>& getProducts() const;
};

class WarehouseAnalyzer {
  public:
    static double calculateTotalValue(const Warehouse& warehouse);
    static Product getTheMostExpensiveOne(const Warehouse& warehouse);
    static std::vector<Product> getTheMostExpensiveHalf(const Warehouse& warehouse);
    void increasePricesOfSelected(const Warehouse& warehouse, int treshold, double percentage);
};
