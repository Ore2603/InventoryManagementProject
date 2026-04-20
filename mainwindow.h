#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "product.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Template function demonstrating generic programming
template <typename T>
T calculateTotal(T a, T b)
{
    return a * b;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot functions triggered by GUI buttons
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void on_removeQtyButton_clicked();

private:
    Ui::MainWindow *ui;

    // Composition: MainWindow contains a collection of Items
    std::vector<Item*> inventory;

    // Helper function to update table display
    void updateTable();
};

#endif