#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsMenuScreen.h"
#include "clsManageUsersMenuScreen.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include "clsUsersLoginRecordsScreen .h"
#include "clsCurrencyExchangeMainScreen.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenuOptions
    {
        showClientsList = 1,
        addClient = 2,
        deleteClient = 3,
        updateClient = 4,
        findClient = 5,
        transactions = 6,
        manageUsers = 7,
        usersLoginRecords = 8,
        currencyExchange = 9,
        logout = 10
    };

    static short _readMainMenuOption()
    {
        short choice;
        cout << setw(75) << "Choose what you want to do? [1 to 10]: ";
        choice = clsInputValidate::readNumberBetween<short>(1, 10, "\t\t\t\t     Enter a number between 1 and 10: ");
        return choice;
    }

    static void _goBackToMainMenuScreen()
    {
        cout << "\nPress any key to go back to Main Menu...";
        system("pause>0");
        showMainMenuScreen();
    }

    static void _showClientListScreen()
    {
        clsClientListScreen::showClientListScreen();
    }

    static void _showAddNewClientsScreen()
    {
        clsAddNewClientScreen::showAddNewClientScreen();
    }

    static void _showDeleteClientScreen()
    {
        clsDeleteClientScreen::showDeleteClientScreen();
    }

    static void _showUpdateClientScreen()
    {
        clsUpdateClientScreen::showUpdateClientScreen();
    }

    static void _showFindClientScreen()
    {
        clsFindClientScreen::showFindClientScreen();
    }

    static void _showTransactionsMenuScreen()
    {
        clsTransactionsMenuScreen::showTransactionsMenuScreen();
    }

    static void _showManageUsersMenuScreen()
    {
        clsManageUsersMenuScreen::showManageUsersMenuScreen();
    }

    static void _showUsersLoginRecordsScreen()
    {
        clsUsersLoginRecordsScreen::showUsersLoginRecordsScreen();
    }

    static void _showCurrencyExchangeMainScreen()
    {
        clsCurrencyExchangeMainScreen::showCurrencyExchangeMainScreen();
    }

    static void _logout()
    {
        currentUser = clsUser::find("", "");
        // Then it will go to main function
    }

    static void _performMainMenuOption(enMainMenuOptions mainMenuOption)
    {
        switch (mainMenuOption)
        {
        case enMainMenuOptions::showClientsList:
            system("cls");
            _showClientListScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::addClient:
            system("cls");
            _showAddNewClientsScreen();
            _goBackToMainMenuScreen();
        case enMainMenuOptions::deleteClient:
            system("cls");
            _showDeleteClientScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::updateClient:
            system("cls");
            _showUpdateClientScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::findClient:
            system("cls");
            _showFindClientScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::transactions:
            system("cls");
            _showTransactionsMenuScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::manageUsers:
            _showManageUsersMenuScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::usersLoginRecords:
            system("cls");
            _showUsersLoginRecordsScreen();
            _goBackToMainMenuScreen();
            break;
        case enMainMenuOptions::currencyExchange:
            _showCurrencyExchangeMainScreen();
            _goBackToMainMenuScreen();
        case enMainMenuOptions::logout:
            system("cls");
            _logout();
        }
    }

public:
	static void showMainMenuScreen()
	{
		system("cls");
		_drawScreenHeader("\t     Main Screen");

        cout << setw(80) << right << "==========================================\n";
        cout << setw(80) << "                 Main Menu                \n";
        cout << setw(80) << "==========================================\n";
        cout << setw(80) << "  [1] Show Client List.                   \n";
        cout << setw(80) << "  [2] Add New Client.                     \n";
        cout << setw(80) << "  [3] Delete Client.                      \n";
        cout << setw(80) << "  [4] Update Client.                      \n";
        cout << setw(80) << "  [5] Find Client.                        \n";
        cout << setw(80) << "  [6] Transactions.                       \n";
        cout << setw(80) << "  [7] Manage Users.                       \n";
        cout << setw(80) << "  [8] Users Login Records.                \n";
        cout << setw(80) << "  [9] Currency Exchange.                  \n";
        cout << setw(80) << "  [10] Logout.                            \n";
        cout << setw(80) << "==========================================\n";
        _performMainMenuOption((enMainMenuOptions)_readMainMenuOption());
	}
};

