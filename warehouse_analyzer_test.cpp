#include <gtest/gtest.h>
#include "./include/warehouse_analyzer.hpp"


TEST (warehouse_analyzer, calculateTotalValue) {
    Warehouse warehouse;
    warehouse.addProduct(Product("Product1", 10.0, 5));
    warehouse.addProduct(Product("Product2", 20.0, 3));
    warehouse.addProduct(Product("Product3", 15.0, 4));

    double totalValue = WarehouseAnalyzer::calculateTotalValue(warehouse);
    EXPECT_DOUBLE_EQ(totalValue, 10.0 * 5 + 20.0 * 3 + 15.0 * 4);
}

TEST (warehouse_analyzer, getTheMostExpensiveOne) {
    Warehouse warehouse;
    warehouse.addProduct(Product("Product1", 10.0, 5));
    warehouse.addProduct(Product("Product2", 20.0, 3));
    warehouse.addProduct(Product("Product3", 15.0, 4));

    Product mostExpensive = WarehouseAnalyzer::getTheMostExpensiveOne(warehouse);
    EXPECT_EQ(mostExpensive.getName(), "Product2");
    EXPECT_DOUBLE_EQ(mostExpensive.getPrice(), 20.0);
    EXPECT_EQ(mostExpensive.getQuantity(), 3);
}

TEST (warehouse_analyzer, getTheMostExpensiveHalf) {
    Warehouse warehouse;
    warehouse.addProduct(Product("Product1", 10.0, 5));
    warehouse.addProduct(Product("Product2", 20.0, 3));
    warehouse.addProduct(Product("Product3", 15.0, 4));

    std::vector<Product> expensiveHalf = WarehouseAnalyzer::getTheMostExpensiveHalf(warehouse);
    EXPECT_EQ(expensiveHalf.size(), 1);
    EXPECT_EQ(expensiveHalf[0].getName(), "Product2");
}

TEST (warehouse_analyzer, increasePricesOfSelected) {
    Warehouse warehouse;
    warehouse.addProduct(Product("Product1", 10.0, 5));
    warehouse.addProduct(Product("Product2", 20.0, 3));
    warehouse.addProduct(Product("Product3", 15.0, 4));

    WarehouseAnalyzer::increasePricesOfProductsBelowMedian(warehouse, 10.0);
    for (const Product& product : warehouse.getProducts()) {
        if (product.getName() == "Product1") {
            EXPECT_DOUBLE_EQ(product.getPrice(), 11.0); //  increased by 10%
        } else if (product.getName() == "Product2") {
            EXPECT_DOUBLE_EQ(product.getPrice(), 20.0); // remains unchanged
        } else if (product.getName() == "Product3") {
            EXPECT_DOUBLE_EQ(product.getPrice(), 15.0); //  remains unchanged bcos < not <=
        }
    }
}
