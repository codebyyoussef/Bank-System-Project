
#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class FindCurrencyScreen : protected clsScreen
{
private:
	static void _printCurrencyCard(clsCurrency currency)
	{
		cout << "\nCurrency Card:";
		cout << "\n________________________________";
		cout << "\nCountry          : " << currency.country();
		cout << "\nCurrency Code    : " << currency.currencyCode();
		cout << "\nCurrency Name    : " << currency.currencyName();
		cout << "\nExchage Rate(1$) : " << currency.exchangeRate();
		cout << "\n________________________________\n";
	}

	static void _showResults(clsCurrency currency)
	{
		if (currency.isEmpty())
		{
			cout << "\nCurrency was not found :(\n";
		}
		else
		{
			cout << "\nCurrency found :)\n";
			_printCurrencyCard(currency);
		}
	}

public:
	static void showFindCurrencyScreen()
	{
		_drawScreenHeader("\tFind Currency Screen");
		
		short choice;
		cout << "Find By: [1] Code or [2] Country ? ";
		choice = clsInputValidate::readNumberBetween<short>(1, 2, "\nEnter a number between 1 and 2: ");

		if (choice == 1)
		{
			string currencyCode;
			cout << "\nPlease enter currency code: ";
			currencyCode = clsInputValidate::readString();

			clsCurrency currency = clsCurrency::findByCode(currencyCode);
			_showResults(currency);
		}
		else
		{
			string country;
			cout << "\nPlease enter country name: ";
			country = clsInputValidate::readString();

			clsCurrency currency = clsCurrency::findByCountry(country);
			_showResults(currency);
		}

	}
};

