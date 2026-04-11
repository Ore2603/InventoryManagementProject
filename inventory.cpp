#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "inventory.h"

int Inventory::findIndex(std::string_view id) const {
    for (int i = 0; i < static_cast<int>(m_items.size()); ++i)
        if (m_items[i].getId() == id) return i;
    return -1;
}

void Inventory::addItem(const Product& product) {
    if (findIndex(product.getId()) != -1)
        throw std::invalid_argument(
            std::format("Item with ID '{}' already exists.", product.getId()));
    m_items.push_back(product);
    std::cout << std::format("Item '{}' added successfully.\n", product.getName());
}

void Inventory::removeItem(std::string_view id) {
    int index = findIndex(id);
    if (index == -1)
        throw std::invalid_argument(std::format("Item ID '{}' not found.", id));
    std::cout << std::format("Item '{}' removed.\n", m_items[index].getName());
    m_items.erase(m_items.begin() + index);
}

void Inventory::updatePrice(std::string_view id, double newPrice) {
    int index = findIndex(id);
    if (index == -1)
        throw std::invalid_argument(std::format("Item ID '{}' not found.", id));
    m_items[index].setPrice(newPrice);
    std::cout << std::format("Price updated for '{}'.\n", m_items[index].getName());
}

void Inventory::updateQuantity(std::string_view id, int newQuantity) {
    int index = findIndex(id);
    if (index == -1)
        throw std::invalid_argument(std::format("Item ID '{}' not found.", id));
    m_items[index].setQuantity(newQuantity);
    std::cout << std::format("Quantity updated for '{}'.\n", m_items[index].getName());
}

void Inventory::searchItem(std::string_view query) const {
    bool found = false;
    for (const Product& p : m_items) {
        if (p.getId() == query || p.getName().find(query) != std::string::npos) {
            p.display();
            found = true;
        }
    }
    if (!found)
        std::cout << std::format("No items found matching '{}'.\n", query);
}

void Inventory::displayAll() const {
    if (m_items.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    std::cout << std::format("{:-<70}\n", "");
    std::cout << std::format("{:<10} {:<20} {:<12} {:<10} {:<15}\n",
        "ID", "Name", "Price", "Qty", "Category");
    std::cout << std::format("{:-<70}\n", "");
    for (const Product& p : m_items)
        std::cout << std::format("{:<10} {:<20} ${:<11.2f} {:<10} {:<15}\n",
            p.getId(), p.getName(), p.getPrice(), p.getQuantity(), p.getCategory());
    std::cout << std::format("{:-<70}\n", "");
}

void Inventory::checkLowStock(int threshold) const {
    bool any = false;
    for (const Product& p : m_items) {
        if (p.getQuantity() <= threshold) {
            if (!any) std::cout << "⚠ Low stock alert:\n";
            std::cout << std::format("  {} (ID: {}) — only {} left\n",
                p.getName(), p.getId(), p.getQuantity());
            any = true;
        }
    }
    if (!any) std::cout << "All items are sufficiently stocked.\n";
}

void Inventory::saveToFile(std::string_view filename) const {
    std::ofstream file{std::string(filename)};
    if (!file)
        throw std::runtime_error("Failed to open file for writing.");
    for (const Product& p : m_items)
        file << std::format("{},{},{:.2f},{},{}\n",
            p.getId(), p.getName(), p.getPrice(),
            p.getQuantity(), p.getCategory());
    std::cout << std::format("Inventory saved to '{}'.\n", filename);
}

void Inventory::loadFromFile(std::string_view filename) {
    std::ifstream file{std::string(filename)};
    if (!file) {
        std::cout << "No save file found. Starting with empty inventory.\n";
        return;
    }
    m_items.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss{line};
        std::string id, name, category, priceStr, qtyStr;
        if (std::getline(ss, id, ',') && std::getline(ss, name, ',') &&
            std::getline(ss, priceStr, ',') && std::getline(ss, qtyStr, ',') &&
            std::getline(ss, category)) {
            try {
                m_items.emplace_back(id, name, std::stod(priceStr),
                    std::stoi(qtyStr), category);
            } catch (...) {
                std::cout << "Skipping invalid record.\n";
            }
        }
    }
    std::cout << std::format("Loaded {} items from '{}'.\n", m_items.size(), filename);
}
