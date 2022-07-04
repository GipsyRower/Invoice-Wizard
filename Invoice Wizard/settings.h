#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;

void createSettings();
void loadSettings(int currentInvoices);
void options(int currentInvoices);
void loadInvoices();
void addInvoices();

#endif // !SETTINGS_H
