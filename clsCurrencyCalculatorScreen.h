#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static void _printCurrencyCard(clsCurrency currency, string title)
	{
		cout << "\n" << title;
		cout << "\n___________________________________";
		cout << "\nCountry          : " << currency.country();
		cout << "\nCurrency Code    : " << currency.currencyCode();
		cout << "\nCurrency Name    : " << currency.currencyName();
		cout << "\nExchage Rate(1$) : " << currency.exchangeRate();
		cout << "\n___________________________________\n\n";
	}

	static clsCurrency _getCurrency(string msg)
	{
		string currencyCode;
		cout << msg;
		currencyCode = clsInputValidate::readString();

		while (!clsCurrency::isCurrencyExist(currencyCode))
		{
			cout << "\nCurrency was not found, choose anther one: ";
			currencyCode = clsInputValidate::readString();
		}

		clsCurrency currency = clsCurrency::findByCode(currencyCode);
		return currency;
	}

	static void _printConversionResults(float amount, clsCurrency currencyFrom, clsCurrency currencyTo)
	{
		_printCurrencyCard(currencyFrom, "Converting From " + currencyFrom.currencyCode() + " to USD:");

		float amountInUSD = currencyFrom.convertToUSD(amount);
		cout << amount << " " << currencyFrom.currencyCode() << " = " << amountInUSD << " USD\n";

		if (currencyTo.currencyCode() == "USD")
		{
			return;
		}

		_printCurrencyCard(currencyTo, "Converting From " + currencyFrom.currencyCode() + " to " + currencyTo.currencyCode() + ":");

		float convertedAmount = currencyFrom.convertToOtherCurrency(amount, currencyTo);
		cout << amount << " " << currencyFrom.currencyCode() << " = " << convertedAmount << " " << currencyTo.currencyCode() << "\n";
	}

public:
	static void showCurrencyCalculatorScreen()
	{
		char Continue = 'y';
		while (Continue == 'y' || Continue == 'Y')
		{
			system("cls");
			_drawScreenHeader("\t Currency Calculator");

			clsCurrency currencyFrom = _getCurrency("Please enter currency 01 code: ");
			clsCurrency currencyTo = _getCurrency("\nPlease enter currency 02 code: "); 
			cout << "\nAmount: ";
			float amount = clsInputValidate::readNumber<float>();

			_printConversionResults(amount, currencyFrom, currencyTo);

			cout << "\nDo you want to perform another calculation? y/n: ";
			cin >> Continue;
		}
	}
};

