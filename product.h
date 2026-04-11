#pragma once
#include <string>
#include <string_view>

class Item {
public:
    Item(std::string_view id, std::string_view name, double price);
    virtual ~Item() = default;

    std::string getId() const;
    std::string getName() const;
    double getPrice() const;
    void setPrice(double price);

    virtual void display() const;

private:
    std::string m_id;
    std::string m_name;
    double m_price;
};

class Product : public Item {
public:
    Product(std::string_view id, std::string_view name, double price,
            int quantity, std::string_view category);

    int getQuantity() const;
    void setQuantity(int quantity);
    std::string getCategory() const;

    void display() const override;

private:
    int m_quantity;
    std::string m_category;
};
