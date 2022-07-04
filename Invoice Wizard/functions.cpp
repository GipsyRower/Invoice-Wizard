#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "invoice.h"
#include "settings.h"

using std::cout;
using std::cin;
using std::string;
using std::ifstream;

namespace fs = std::filesystem;

void printInvoiceList()
{
    int currentInvoices = 0;

    for (const auto& file : fs::directory_iterator(fs::current_path())) {
        if (file.path().extension() == ".txt") {
            currentInvoices++;
            cout << file.path().stem().string() << '\n';
        }
    }

    if (currentInvoices > 0) {
        cout << "Total amount of invoices - " << currentInvoices << "\n";
    }

    if (currentInvoices == 0) {
        cout << "No invoices found\n";
    }

    system("pause");
    return loadInvoices();
}

void createInvoice(int totalInvoices)
{
    string contractorName;
    contractorName = "";

    totalInvoices++;

    string invoiceNumber = std::to_string(totalInvoices);

    string product;
    product = "";

    int unitPrice;
    unitPrice = 0;

    int amount;
    amount = 0;

    cout << "Eneter contractor name\n";
    cin >> contractorName;

    cout << "Enter product/service name\n";
    cin >> product;

    cout << "Enter unit price\n";
    cin >> unitPrice;

    cout << "Enter amount\n";
    cin >> amount;
      
    cout << "Total invoices: " << invoiceNumber << "\n";

    string outfileName = contractorName + " invoice " + invoiceNumber + ".txt";

    cout << outfileName << "\n";

    std::ofstream outfile(outfileName, std::ios::out);

    outfile << "Invoice Number - " << invoiceNumber << "\n";
    outfile << "Contractors Name - " << contractorName << "\n";
    outfile << "Product/service name - " << product << "\n";
    outfile << "Unit Price - " << unitPrice << "\n";
    outfile << "Amount - " << amount << "\n";
    outfile << "Price - " << unitPrice * amount << "\n";

    outfile.close();

    system("pause");
    return addInvoices();
}

void deleteInvoice()
{
    string invoices[255] = {};

    int currentInvoices = 1;
    int userChoice = 0;

    int i = 0;

    for (const auto& file : fs::directory_iterator(fs::current_path())) {
        if (file.path().extension() == ".txt") {
            invoices[i] = file.path().string();
            cout << file.path().stem().string() << " - " << currentInvoices << '\n';
            currentInvoices++;
            i++;
        }
    }

    if (currentInvoices == 1) {
        cout << "No invoices to delete\n";
    }

    cout << "Type number of invoice you want to delete\n";
    cin >> userChoice;

    if (userChoice > currentInvoices) {
        cout << "This invoice dosn't exist\n";
    }
    else if (userChoice <= 0) {
        cout << "Please type number biger than 0\n";
    }

    currentInvoices = userChoice;

    if (currentInvoices == 1) {
        currentInvoices = 0;
    }

    std::filesystem::remove(invoices[currentInvoices]);
    
    cout << "Deleting was successful!\n";

    return loadInvoices();
}