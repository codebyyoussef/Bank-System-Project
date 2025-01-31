#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
using namespace std;

class CurrencyListScreen : protected clsScreen
{
private:
	static void _printCurrencyRecordLine(clsCurrency currency)
	{
		cout << "\t| " << setw(30) << left << currency.country();
		cout << "| " << setw(5) << left << currency.currencyCode();
		cout << "| " << setw(40) << left << currency.currencyName();
		cout << "| " << setw(10) << left << currency.exchangeRate();
	}
public:
	static void showCurrencyListScreen()
	{
		vector<clsCurrency> vCurrencyList = clsCurrency::getCurrencyList();
		string title = "\tCurrency List Screen";
		string subTitle = "\t (" + to_string(vCurrencyList.size()) + ") Currencies.";

		_drawScreenHeader(title, subTitle);

		cout << "\t_____________________________________________________________________________________________\n\n";
		cout << "\t| " << setw(30) << left << "Country";
		cout << "| " << setw(5) << left << "Code";
		cout << "| " << setw(40) << left << "Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";
		cout << "\n\t_____________________________________________________________________________________________\n\n";
		if (vCurrencyList.size() == 0)
		{
			cout << "\tNo currency is available in the system!\n";
		}
		else
		{
			for (const clsCurrency& currency : vCurrencyList)
			{
				_printCurrencyRecordLine(currency);
				cout << "\n";
			}
		}
		cout << "\n\t_____________________________________________________________________________________________\n\n";
	}
};

