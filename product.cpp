#include <iostream>
#include <stdexcept>
#include "product.h"

// Item
Item::Item(std::string_view id, std::string_view name, double price)
    : m_id{id}, m_name{name}, m_price{0.0} {
    setPrice(price);
}

std::string Item::getId() const { return m_id; }
std::string Item::getName() const { return m_name; }
double Item::getPrice() const { return m_price; }

void Item::setPrice(double price) {
    if (price < 0.0)
        throw std::invalid_argument("Price cannot be negative.");
    m_price = price;
}

void Item::display() const {
    std::cout << "ID: " << m_id
              << " | Name: " << m_name
              << " | Price: $" << m_price << "\n";
}

// Product
Product::Product(std::string_view id, std::string_view name, double price,
                 int quantity, std::string_view category)
    : Item{id, name, price}, m_quantity{0}, m_category{category} {
    setQuantity(quantity);
}

int Product::getQuantity() const { return m_quantity; }

void Product::setQuantity(int quantity) {
    if (quantity < 0)
        throw std::invalid_argument("Quantity cannot be negative.");
    m_quantity = quantity;
}

std::string Product::getCategory() const { return m_category; }

void Product::display() const {
    std::cout << "ID: " << getId()
              << " | Name: " << getName()
              << " | Price: $" << getPrice()
              << " | Qty: " << m_quantity
              << " | Category: " << m_category << "\n";
}
