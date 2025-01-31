#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateExchangeRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private: 
    enum enCurrencyExchangeMenuOptions
    {
        currencyList = 1,
        findCurrency = 2,
        updateExchangeRate = 3, 
        currencyCalculator = 4, 
        mainMenu = 5
    };

    static void _goBackToCurrencyExchangeMainScreen()
    {
        cout << "\nPress any key to go back to Main Menu...";
        system("pause>0");
        showCurrencyExchangeMainScreen();
    }

    static void _showCurrencyListScreen()
    {
        CurrencyListScreen::showCurrencyListScreen();
    }

    static void _showFindCurrencyScreen()
    {
        FindCurrencyScreen::showFindCurrencyScreen();
    }

    static void _showUpdateExchangeRateScreen()
    {
        clsUpdateExchangeRateScreen::showUpdateExchangeRateScreen();
    }

    static void _showCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
    }

    static short _readCurrencyExchangeMenuOption()
    {
        short choice;
        cout << setw(75) << "Choose what you want to do? [1 to 5]: ";
        choice = clsInputValidate::readNumberBetween<short>(1, 5, "\t\t\t\t     Enter a number between 1 and 5: ");
        return choice;
    }

    static void _performCurrencyExchangeMenuOption(enCurrencyExchangeMenuOptions currencyExchangeMenuOption)
    {
        switch (currencyExchangeMenuOption)
        {
            case enCurrencyExchangeMenuOptions::currencyList:
                system("cls");
                _showCurrencyListScreen();
                _goBackToCurrencyExchangeMainScreen();
                break;
            case enCurrencyExchangeMenuOptions::findCurrency:
                system("cls");
                _showFindCurrencyScreen();
                _goBackToCurrencyExchangeMainScreen();
                break;
            case enCurrencyExchangeMenuOptions::updateExchangeRate:
                system("cls");
                _showUpdateExchangeRateScreen();
                _goBackToCurrencyExchangeMainScreen();
                break;
            case enCurrencyExchangeMenuOptions::currencyCalculator:
                _showCurrencyCalculatorScreen();
                _goBackToCurrencyExchangeMainScreen();
                break;
            case enCurrencyExchangeMenuOptions::mainMenu:
            {

            }
        }
    }
public:
	static void showCurrencyExchangeMainScreen()
	{
        system("cls");
		_drawScreenHeader("    Currency Exchange Main Screen");

        cout << setw(80) << right << "==========================================\n";
        cout << setw(80) << "          Currency Exchange Menu           \n";
        cout << setw(80) << "==========================================\n";
        cout << setw(80) << "  [1] Currency List.                      \n";
        cout << setw(80) << "  [2] Find Currency.                      \n";
        cout << setw(80) << "  [3] Update Exchange Rate.               \n";
        cout << setw(80) << "  [4] Currency Calculator.                \n";
        cout << setw(80) << "  [5] Main Menu.                          \n";
        cout << setw(80) << "==========================================\n";
        _performCurrencyExchangeMenuOption((enCurrencyExchangeMenuOptions)_readCurrencyExchangeMenuOption());
	}
};
