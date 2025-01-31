#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositScreen : protected clsScreen
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

    static double _readDepositAmount()
    {
        double amount;
        cout << "Please enter deposit amount: ";
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
    static void showDepositScreen()
    {
        _drawScreenHeader("\tDeposit Screen");

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

        double amount = _readDepositAmount();

        char depositConfirmation = 'n';
        cout << "\nAre you sure you want to perform this transaction? y/n: ";
        cin >> depositConfirmation;

        if (depositConfirmation == 'y' || depositConfirmation == 'Y')
        {
            client.deposit(amount);
            cout << "\nAmount deposited seccussfully\n";
            cout << "\nThe new balance is " << client.accountBalance << "\n";
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};

