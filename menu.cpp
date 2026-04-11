#include <iostream>
#include <limits>
#include "menu.h"

void Menu::displayMenu() {
    m_inventory.loadFromFile();

    int choice = 0;

    while (choice != 0) {
        std::cout << "\n=== Inventory Management System ===\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Update Item\n";
        std::cout << "4. Search Item\n";
        std::cout << "5. Display All Items\n";
        std::cout << "6. Check Low Stock\n";
        std::cout << "7. Save Inventory\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) handleAdd();
        else if (choice == 2) handleRemove();
        else if (choice == 3) handleUpdate();
        else if (choice == 4) handleSearch();
        else if (choice == 5) m_inventory.displayAll();
        else if (choice == 6) m_inventory.checkLowStock();
        else if (choice == 7) m_inventory.saveToFile();
        else if (choice == 0) {
            m_inventory.saveToFile();
            std::cout << "Goodbye!\n";
        }
        else std::cout << "Invalid option, try again.\n";
    }
}

void Menu::handleAdd() {
    std::string id, name, category;
    double price = 0.0;
    int qty = 0;

    std::cout << "Enter ID: ";
    std::getline(std::cin, id);
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter category: ";
    std::getline(std::cin, category);
    std::cout << "Enter price: ";
    std::cin >> price;
    std::cout << "Enter quantity: ";
    std::cin >> qty;
    std::cin.ignore();

    try {
        m_inventory.addItem(Product{id, name, price, qty, category});
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Menu::handleRemove() {
    std::string id;
    std::cout << "Enter ID to remove: ";
    std::getline(std::cin, id);
    m_inventory.removeItem(id);
}

void Menu::handleUpdate() {
    std::string id;
    std::cout << "Enter ID to update: ";
    std::getline(std::cin, id);

    std::cout << "1. Update price\n2. Update quantity\nChoice: ";
    int option = 0;
    std::cin >> option;
    std::cin.ignore();

    try {
        if (option == 1) {
            double price = 0.0;
            std::cout << "New price: ";
            std::cin >> price;
            std::cin.ignore();
            m_inventory.updatePrice(id, price);
        } else if (option == 2) {
            int qty = 0;
            std::cout << "New quantity: ";
            std::cin >> qty;
            std::cin.ignore();
            m_inventory.updateQuantity(id, qty);
        } else {
            std::cout << "Invalid option.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Menu::handleSearch() {
    std::string query;
    std::cout << "Enter name or ID to search: ";
    std::getline(std::cin, query);
    m_inventory.searchItem(query);
}
