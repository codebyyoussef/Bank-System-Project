#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:
    static void _printClientInfo(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n-------------------------------------";
        cout << "\nFirstname      : " << client.firstName;
        cout << "\nLastname       : " << client.lastName;
        cout << "\nFullname       : " << client.fullName();
        cout << "\nEmail          : " << client.email;
        cout << "\nPhone          : " << client.phone;
        cout << "\nAccount Number : " << client.accountNumber();
        cout << "\nPassword       : " << client.pinCode;
        cout << "\nBalance        : " << client.accountBalance;
        cout << "\n-------------------------------------\n";
    }

    static double _readWithdrawAmount()
    {
        double amount;
        amount = clsInputValidate::readNumber<double>();
        while (amount <= 0)
        {
            cout << "Amount should be > 0\n";
            cout << "Enter a valid amount: ";
            amount = clsInputValidate::readNumber<double>();
        }
        return amount;
    }

public:
	static void showWithdrawScreen()
	{
		_drawScreenHeader("\tWithdraw Screen");

        string accountNumber;
        cout << "Please enter an account number: ";
        accountNumber = clsInputValidate::readString();

        while (!clsBankClient::isClientExist(accountNumber))
        {
            cout << "\nClient with [" << accountNumber << "] does not exist.\n";
            cout << "Choose anoter one: ";
            accountNumber = clsInputValidate::readString();
        }

        clsBankClient client = clsBankClient::find(accountNumber);
        _printClientInfo(client);

        double amount = _readWithdrawAmount();
        /*UI áÍãÇíÉ ÇáÅÏÎÇá ãä
        amount = InputValidate::readFloatNumberBetween(0, Client.AccountBalance)*/

        char withdrawConfirmation = 'n';
        cout << "\nAre you sure you want to perform this transaction? y/n: ";
        cin >> withdrawConfirmation;

        if (withdrawConfirmation == 'y' || withdrawConfirmation == 'Y')
        {
            if (client.withdraw(amount))
            {
                cout << "\nAmount withdrew successfully.\n";
                cout << "\nNew balance is: " << client.accountBalance << "\n";
            }
            else
            {
                cout << "\nCannot withdraw, insufficient balance!\n";
                cout << "Amount to withdraw is: " << amount << "\n";
                cout << "Your balance is: " << client.accountBalance << "\n";
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
	}
};

