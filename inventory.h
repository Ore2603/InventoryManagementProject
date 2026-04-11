#pragma once
#include <string>
#include <string_view>
#include <vector>
#include "product.h"

class Inventory {
public:
    void addItem(const Product& product);
    void removeItem(std::string_view id);
    void updatePrice(std::string_view id, double newPrice);
    void updateQuantity(std::string_view id, int newQuantity);
    void searchItem(std::string_view query) const;
    void displayAll() const;
    void checkLowStock() const;
    void saveToFile() const;
    void loadFromFile();

private:
    std::vector<Product> m_items;
    int findIndex(std::string_view id) const;
};
