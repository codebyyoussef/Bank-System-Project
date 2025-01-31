#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateExchangeRateScreen : protected clsScreen
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

	static float _readNewExchangeRate()
	{
		float newExchangeRate;
		cout << "Enter new exchange rate: ";
		newExchangeRate = clsInputValidate::readNumber<float>();
		return newExchangeRate;
	}

public:
	static void showUpdateExchangeRateScreen()
	{
		_drawScreenHeader("      Update Echange Rate Screen");

		string currencyCode;
		cout << "Please enter currency code: ";
		currencyCode = clsInputValidate::readString();

		while (!clsCurrency::isCurrencyExist(currencyCode))
		{
			cout << "\nCurrency code is not found, choose anther one: ";
			currencyCode = clsInputValidate::readString();
		}

		clsCurrency currency = clsCurrency::findByCode(currencyCode);
		_printCurrencyCard(currency);

		char confirmUpdate = 'n';
		cout << "\nAre you sure you want to update the rate of this currency? y/n: ";
		cin >> confirmUpdate;

		if (confirmUpdate == 'y' || confirmUpdate == 'Y')
		{
			cout << "\nUpdate currency exchange rate:\n";
			cout << "______________________________\n\n";
			currency.updateExchangeRate(_readNewExchangeRate());
			cout << "\nCurrency exchange rate updated successfully :)\n";
			_printCurrencyCard(currency);
		}
	}
};

