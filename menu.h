#pragma once
#include "inventory.h"

class Menu {
public:
    void displayMenu();

private:
    Inventory m_inventory;
    void handleAdd();
    void handleRemove();
    void handleUpdate();
    void handleSearch();
};
