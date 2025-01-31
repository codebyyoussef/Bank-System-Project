#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "Global.h"
#include "clsInputValidate.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _printClientInfo(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n-------------------------------------";
		cout << "\nFull Name      : " << client.fullName();
		cout << "\nAccount Number : " << client.accountNumber();
		cout << "\nBalance        : " << client.accountBalance;
		cout << "\n-------------------------------------\n";
	}

	static string _readClientAccountNumber(string msg)
	{
		string accountNumber;
		cout << msg;
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::readString();
		}

		return accountNumber;
	}

	static double _readAmountToTransfer(clsBankClient senderClient)
	{
		double amount;

		cout << "\nEnter transfer amount: ";
		amount = clsInputValidate::readNumber<double>();

		while (amount > senderClient.accountBalance)
		{
			cout << "\nAmount exceeds the available balance, enter another amount: ";
			amount = clsInputValidate::readNumber<double>();
		}

		return amount;
	}

public:
	static void showTransferScreen()
	{
		_drawScreenHeader("\t   Transfer Screen");

		clsBankClient srcClient = clsBankClient::find(_readClientAccountNumber("Please enter account number to transfer from: "));
		_printClientInfo(srcClient);

		clsBankClient destClient = clsBankClient::find(_readClientAccountNumber("\nPlease enter account number to transfer to: "));

		while (destClient.accountNumber() == srcClient.accountNumber())
		{
			cout << "\nYou can't transfer money to yourself!\n";
			destClient = clsBankClient::find(_readClientAccountNumber("\nPlease enter account number to transfer to: "));
		}
		_printClientInfo(destClient);

		double amountToTransfer = _readAmountToTransfer(srcClient);

		char confirmOperation = 'n';
		cout << "\nAre you sure you want to perform this operation? y/n: ";
		cin >> confirmOperation;

		if (confirmOperation == 'y' || confirmOperation == 'Y')
		{
			if (srcClient.transfer(amountToTransfer, destClient, currentUser.userName))
			{
				cout << "\nTransfer done successfully :)\n";
				_printClientInfo(srcClient);
				_printClientInfo(destClient);
			}
			else
			{
				cout << "\nTransfer operation failed!\n";
			}
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
	}
};

