#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogsScreen.h"
using namespace std;

class clsTransactionsMenuScreen : protected clsScreen
{
private:
    enum enTransactionsMenuOptions
    {
        deposit = 1,
        withdraw = 2,
        totalBalances = 3,
        transfer = 4,
        showTransferLogs = 5,
        mainMenu = 6
    };

    static short _readTransactionsMenuOption()
    {
        short choice;
        cout << setw(75) << "Choose what you want to do? [1 to 6]: ";
        choice = clsInputValidate::readNumberBetween<short>(1, 6, "\t\t\t\t     Enter a number between 1 and 6: ");
        return choice;
    }

    static void _goBackToTransactionsMenuScreen()
    {
        cout << "\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        showTransactionsMenuScreen();
    }
    
    static void _showDepositScreen()
    {
        clsDepositScreen::showDepositScreen();
    }
    
    static void _showWithdrawScreen()
    {
        clsWithdrawScreen::showWithdrawScreen();
    }
    
    static void _showClientsBalancesScreen()
    {
        clsTotalBalancesScreen::showTotalBalancesScreen();
    }

    static void _showTransferScreen()
    {
        clsTransferScreen::showTransferScreen();
    }

    static void _showTransferLogsScreen()
    {
        clsTransferLogsScreen::showTransferLogsScreen();
    }

    static void _performTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
    {
        switch (TransactionsMenuOption)
        {
            case enTransactionsMenuOptions::deposit:
                system("cls");
                _showDepositScreen();
                _goBackToTransactionsMenuScreen();
                break;
            case enTransactionsMenuOptions::withdraw:
                system("cls");
                _showWithdrawScreen();
                _goBackToTransactionsMenuScreen();
                break;
            case enTransactionsMenuOptions::totalBalances:
                system("cls");
                _showClientsBalancesScreen();
                _goBackToTransactionsMenuScreen();
                break;
            case enTransactionsMenuOptions::transfer:
                system("cls");
                _showTransferScreen();
                _goBackToTransactionsMenuScreen();
            case enTransactionsMenuOptions::showTransferLogs:
                system("cls");
                _showTransferLogsScreen();
                _goBackToTransactionsMenuScreen();
            case enTransactionsMenuOptions::mainMenu:
            {
                //do nothing here the main screen will handle it :-)
            }  
        }
    }

public:
	static void showTransactionsMenuScreen()
	{
        if (!_checkAccessRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }

        system("cls");
		_drawScreenHeader("\tTransactions Screen");

        cout << setw(80) << right << "==========================================\n";
        cout << setw(80) << "             Transactions Screen          \n";
        cout << setw(80) << "==========================================\n";
        cout << setw(80) << "  [1] Deposit.                            \n";
        cout << setw(80) << "  [2] Withdraw.                           \n";
        cout << setw(80) << "  [3] Total Balances.                     \n";
        cout << setw(80) << "  [4] Transfer.                           \n";
        cout << setw(80) << "  [5] Transfer Logs.                      \n";
        cout << setw(80) << "  [6] Main Menu.                          \n";
        cout << setw(80) << "==========================================\n";
        _performTransactionsMenuOption((enTransactionsMenuOptions)_readTransactionsMenuOption());
	}
};

