#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
using namespace std;

class clsCurrency
{
private:
	enum enMode { emptyMode = 0, updateMode = 1 };

	enMode _mode;
	string _country;
	string _currencyCode;
	string _currencyName;
	float _exchangeRate;

	static clsCurrency _convertLineToCurrencyObject(string line, string seperator = "#//#")
	{
		vector<string> vCurrencyData = clsString::splitString(line, seperator);
		return clsCurrency(updateMode, vCurrencyData.at(0), vCurrencyData.at(1), vCurrencyData.at(2), stof(vCurrencyData.at(3)));
	}

	static vector<clsCurrency> _loadCurrenciesDataFromFile()
	{
		vector<clsCurrency> vCurrencies;

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				vCurrencies.push_back(currency);
			}
			file.close();
		}
		return vCurrencies;
	}

	static string _convertCurrencyObjectToLine(clsCurrency currency, string seperator = "#//#")
	{
		string currencyRecord = "";

		currencyRecord += currency.country() + seperator;
		currencyRecord += currency.currencyCode() + seperator;
		currencyRecord += currency.currencyName() + seperator;
		currencyRecord += to_string(currency.exchangeRate()) + seperator;

		return currencyRecord;
	}

	static void _saveClientsDataToFile(vector<clsCurrency> vCurrencies)
	{
		fstream file;
		file.open("Currencies.txt", ios::out); // overwrite

		if (file.is_open())
		{
			string dataLine;
			for (clsCurrency currency : vCurrencies)
			{
				dataLine = _convertCurrencyObjectToLine(currency);
				file << dataLine << "\n";
			}
			file.close();
		}
	}

	void _update()
	{
		vector<clsCurrency> vCurrencies = _loadCurrenciesDataFromFile();

		for (clsCurrency &currency : vCurrencies)
		{
			if (currency.currencyCode() == currencyCode())
			{
				currency = *this;
				break;
			}
		}

		_saveClientsDataToFile(vCurrencies);
	}

	static clsCurrency _getEmptyCurrencyObject()
	{
		return clsCurrency(enMode::emptyMode, "", "", "", 0);
	}

public:
	clsCurrency(enMode mode, string country, string currencyCode, string currencyName, float exchangeRate)
	{
		_mode = mode;
		_country = country;
		_currencyCode = currencyCode;
		_currencyName = currencyName;
		_exchangeRate = exchangeRate;
	}

	bool isEmpty()
	{
		return _mode == enMode::emptyMode;
	}

	string country()
	{
		return _country;
	}

	string currencyCode()
	{
		return _currencyCode;
	}
	
	string currencyName()
	{
		return _currencyName;
	}

	void updateExchangeRate(float newExchangeRate)
	{
		_exchangeRate = newExchangeRate;
		_update();
	}

	float exchangeRate()
	{
		return _exchangeRate;
	}

	static clsCurrency findByCode(string currencyCode)
	{
		currencyCode = clsString::convertToUppercase(currencyCode);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				if (currency.currencyCode() == currencyCode)
				{
					file.close();
					return currency;
				}
			}
			file.close();
		}
		
		return _getEmptyCurrencyObject();
	}

	static clsCurrency findByCountry(string country)
	{
		country = clsString::convertToUppercase(country);

		fstream file;
		file.open("Currencies.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _convertLineToCurrencyObject(line);
				if (clsString::convertToUppercase(currency.country()) == country)
				{
					file.close();
					return currency;
				}
			}
			file.close();
		}

		return _getEmptyCurrencyObject();
	}

	static bool isCurrencyExist(string currencyCode)
	{
		clsCurrency currency = clsCurrency::findByCode(currencyCode);
		return !currency.isEmpty();
	}
	
	static vector<clsCurrency> getCurrencyList()
	{
		return _loadCurrenciesDataFromFile();
	}

	float convertToUSD(float amount)
	{
		return (float)(amount / exchangeRate());
	}

	float convertToOtherCurrency(float amount, clsCurrency currency2)
	{
		float amountInUSD = convertToUSD(amount);

		if (currency2.currencyCode() == "USD")
		{
			return amountInUSD;
		}

		return (float)(amountInUSD * currency2.exchangeRate());
	}
};

