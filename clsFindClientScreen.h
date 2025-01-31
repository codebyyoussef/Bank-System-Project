#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
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

public:
	static void showFindClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		_drawScreenHeader("\tFind Client Screen");

		string accountNumber;
		cout << "Please enter an account number: ";
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::readString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);

		if (!client.isEmpty())
		{
			cout << "\nClient found :)\n";
		}
		else
		{
			cout << "\nClient was not found!\n";
		}
		_printClientInfo(client);
	}
};

