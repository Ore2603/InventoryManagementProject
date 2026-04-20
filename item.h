#ifndef ITEM_H
#define ITEM_H

#include <QString>

// Abstract base class representing a generic inventory item
class Item {
protected:
    QString name;     // Name of the product
    int quantity;     // Quantity in stock
    double price;     // Price per unit

public:
    // Constructor initializes attributes
    Item(QString n, int q, double p)
        : name(n), quantity(q), price(p) {}

    // Virtual destructor for proper cleanup in inheritance
    virtual ~Item() {}

    // Getter methods (encapsulation)
    QString getName() { return name; }
    int getQuantity() { return quantity; }
    double getPrice() { return price; }

    // Increase quantity
    void addQuantity(int q) { quantity += q; }

    // Decrease quantity safely
    void removeQuantity(int q)
    {
        if (q <= quantity)
            quantity -= q;
    }

    // Pure virtual function (forces derived classes to implement it)
    virtual double getTotalValue() = 0;
};

#endif