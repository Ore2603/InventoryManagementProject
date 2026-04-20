#ifndef PRODUCT_H
#define PRODUCT_H

#include "item.h"

// Derived class representing a specific product
class Product : public Item {
public:
    // Constructor calls base class constructor
    Product(QString n, int q, double p)
        : Item(n, q, p) {}

    // Override of virtual function to calculate total value
    double getTotalValue() override
    {
        return quantity * price;
    }
};

#endif