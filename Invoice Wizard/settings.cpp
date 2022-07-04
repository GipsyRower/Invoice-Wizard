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

void addInvoices()
{
    int totalInvoices = 0;
    int num = 0;

    ifstream fsetting;

    fsetting.open("setting.iwconfig");

    fsetting >> num;
    while (!fsetting.eof()) {
        totalInvoices = num;
        fsetting >> num;
    }

    fsetting.close();

    totalInvoices++;

    std::ofstream outfile("setting.iwconfig");

    outfile << totalInvoices;

    outfile.close();

    return loadInvoices();
}

void options(int currentInvoices)
{
    int userChoice;
    userChoice = 0;

    cout << "1 - View invoice list\n";
    cout << "2 - Create invoice\n";
    cout << "3 - Delete invoice list\n";
    cin >> userChoice;

    if (userChoice <= 0) {
        cout << "Please enter number biger than 0\n";
        return options(currentInvoices);
    }
    else if (userChoice > 3) {
        cout << "Please enter number lower than 4\n";
        return options(currentInvoices);
    }
    else {
        switch (userChoice)
        {
        case 1:
            return printInvoiceList();
            break;

        case 2:
            return createInvoice(currentInvoices);
            break;

        case 3:
            return deleteInvoice();
            break;

        default:
            return options(currentInvoices);
            break;
        }
    }
}

void createSettings()
{
    int InvociesAmount;
    InvociesAmount = 0;

    std::ofstream outfile("setting.iwconfig");

    outfile << "0\n";

    outfile.close();

    return options(InvociesAmount);
}

void loadSettings(int currentInvoices)
{
    int InvociesAmount;
    InvociesAmount = 0;

    if (InvociesAmount <= currentInvoices)
    {
        InvociesAmount = currentInvoices;
    }

    int userChoice;
    userChoice = 0;

    int num;
    num = 0;

    ifstream fsetting;
    fsetting.open("setting.iwconfig");
    if (!fsetting) {
        return createSettings();
    }
    fsetting >> num;
    while (!fsetting.eof()) {
        InvociesAmount = num;
        fsetting >> num;
    }
    fsetting.close();
    return options(InvociesAmount);
}

void loadInvoices()
{
    int InvociesAmount;
    InvociesAmount = 0;

    for (const auto& file : fs::directory_iterator(fs::current_path())) {
        if (file.path().extension() == ".txt") {
            (InvociesAmount)++;
        }
    }
    return loadSettings(InvociesAmount);
}