#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize table with 4 columns
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(
        {"Item Name", "Price", "Quantity", "Total Price"}
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Adds a new product or updates quantity if it already exists
void MainWindow::on_addButton_clicked()
{
    QString name = ui->lineEditName->text();
    int quantity = ui->lineEditQuantity->text().toInt();
    double price = ui->lineEditPrice->text().toDouble();

    // Input validation
    if (name.isEmpty() || quantity <= 0 || price <= 0)
    {
        QMessageBox::warning(this, "Error", "Enter valid values");
        return;
    }

    // Check if product already exists and update quantity
    for (auto item : inventory)
    {
        if (item->getName().toLower() == name.toLower())
        {
            item->addQuantity(quantity);
            updateTable();
            return;
        }
    }

    // Add new product
    inventory.push_back(new Product(name, quantity, price));

    updateTable();
}

// Deletes a selected product entirely
void MainWindow::on_deleteButton_clicked()
{
    int row = ui->tableWidget->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this, "Error", "Select a row");
        return;
    }

    delete inventory[row];
    inventory.erase(inventory.begin() + row);

    updateTable();
}

// Searches for a product and highlights it
void MainWindow::on_searchButton_clicked()
{
    QString name = ui->lineEditSearch->text();

    for (int i = 0; i < inventory.size(); i++)
    {
        if (inventory[i]->getName().toLower() == name.toLower())
        {
            ui->tableWidget->selectRow(i);
            return;
        }
    }

    QMessageBox::information(this, "Not Found", "Product not found");
}

// Removes a specified quantity instead of deleting the product
void MainWindow::on_removeQtyButton_clicked()
{
    int row = ui->tableWidget->currentRow();
    int q = ui->lineEditRemoveQty->text().toInt();

    if (row < 0 || q <= 0)
    {
        QMessageBox::warning(this, "Error", "Invalid selection or quantity");
        return;
    }

    inventory[row]->removeQuantity(q);

    // Remove item completely if quantity reaches zero
    if (inventory[row]->getQuantity() == 0)
    {
        delete inventory[row];
        inventory.erase(inventory.begin() + row);
    }

    updateTable();
}

// Updates the table widget to reflect current inventory
void MainWindow::updateTable()
{
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < inventory.size(); i++)
    {
        ui->tableWidget->insertRow(i);

        ui->tableWidget->setItem(i, 0,
                                 new QTableWidgetItem(inventory[i]->getName()));

        ui->tableWidget->setItem(i, 1,
                                 new QTableWidgetItem("$" + QString::number(inventory[i]->getPrice(), 'f', 2)));

        ui->tableWidget->setItem(i, 2,
                                 new QTableWidgetItem(QString::number(inventory[i]->getQuantity())));

        // Uses polymorphism through virtual function
        ui->tableWidget->setItem(i, 3,
                                 new QTableWidgetItem("$" + QString::number(inventory[i]->getTotalValue(), 'f', 2)));
    }
}