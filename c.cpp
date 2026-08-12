#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

void printCurrencies(const vector<string>& order, const unordered_map<string,double>& rates) {
    cout << "Available currencies:\n";
    for (size_t i = 0; i < order.size(); ++i)
        cout << (i+1) << ") " << order[i] << " (1 USD = " << rates.at(order[i]) << ")\n";
}


int chooseIndex(const string& prompt, size_t max) {
    while (true) {
        cout << prompt;
        int idx;
        if (!(cin >> idx)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }
        if (idx >= 1 && (size_t)idx <= max) return idx - 1;
        cout << "Out of range. Try again.\n";
    }
}

void currencyconverter(unordered_map<string,double> rates, vector<string> order) 
{
    while (true) {
        
        // currency converter menu:
                    // you can choose to implement this function.
        // display options:
        cout << "\nCurrency Converter\n";
        cout << "1) Convert between currencies\n";
        cout << "2) Add currency (relative to USD)\n";
        cout << "3) Change existing rate (relative to USD)\n";
        cout << "4) Quit\n";
        cout << "Choose an option: ";

        int opt;
        if (!(cin >> opt)) { // statement 1
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (opt == 4) break; //statement 2

        if (opt == 1) {
            printCurrencies(order, rates);
            int iFrom = chooseIndex("Choose source currency number: ", order.size());
            int iTo = chooseIndex("Choose target currency number: ", order.size());
            cout << "Enter amount: ";
            double amt;
            if (!(cin >> amt)) { // statement 3
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount.\n";
                continue;
            }
            // Convert: amount_in_USD = amt / rate_of_source, then * rate_of_target
            double srcRate = rates[order[iFrom]];
            double tgtRate = rates[order[iTo]];
            double converted = (amt / srcRate) * tgtRate;
            cout << fixed << setprecision(2)
                 << amt << " " << order[iFrom] << " = " << converted << " " << order[iTo] << "\n";
        } else if (opt == 2) { // statement 4
            cout << "Enter new currency code (e.g. GBP): ";
            string code;
            cin >> code;
            if (rates.count(code)) { // statement 5
                cout << "Currency already exists.\n";
                continue;
            }
            cout << "Enter rate meaning '1 USD = ? " << code << "': ";
            double r;
            if (!(cin >> r) || r <= 0) { // statement 6
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid rate.\n";
                continue; // continuation
            }
            rates[code] = r;
            order.push_back(code);
            cout << "Added " << code << " with rate 1 USD = " << r << "\n";
        } else if (opt == 3) { // statement 7
            printCurrencies(order, rates);
            int idx = chooseIndex("Choose currency number to change: ", order.size());
            cout << "Enter new rate (1 USD = ? " << order[idx] << "): ";
            double r;
            if (!(cin >> r) || r <= 0) { // statement 8
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid rate.\n";
                continue;
            }
            rates[order[idx]] = r;
            cout << "Rate updated.\n";
        } else { // statement 91
            cout << "Unknown option.\n";
        }
    }
}

int main()
{
    unordered_map<string,double> rates = {
        {"USD", 1.0},
        {"PHP", 59.3},   // example: 1 USD = 59.3 PHP
        {"Dirham", 3.67},   // example: 1 USD = 3.67 Dirham
        {"EUR", 1.15}    // example: 1 USD = 1.15 EUR
    };
    vector<string> order = {"USD","PHP","Dirham","EUR"};
    currencyconverter(rates, order);
    return 0;
}