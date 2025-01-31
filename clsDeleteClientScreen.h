#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;


class clsDeleteClientScreen : protected clsScreen
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
	static void showDeleteClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		_drawScreenHeader("\tDelete Client Screen");
		string accountNumber;
		cout << "\nPlease enter an account number: ";
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::readString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);
		_printClientInfo(client);

		char deleteClient = 'n';
		cout << "Are you sure you want to delete this client? y/n? ";
		cin >> deleteClient;
		if (deleteClient == 'y' || deleteClient == 'Y')
		{
			if (client.Delete())
			{
				cout << "\nAccount deleted successfully :)\n";
				_printClientInfo(client);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}

	}

};

