#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _readClientInfo(clsBankClient& client)
	{
		cout << "\nEnter firstname: ";
		client.firstName = clsInputValidate::readString();

		cout << "\nEnter lastname: ";
		client.lastName = clsInputValidate::readString();

		cout << "\nEnter email: ";
		client.email = clsInputValidate::readString();

		cout << "\nEnter phone: ";
		client.phone = clsInputValidate::readString();

		cout << "\nEnter pin code: ";
		client.pinCode = clsInputValidate::readString();

		cout << "\nEnter account Balance: ";
		client.accountBalance = clsInputValidate::readNumber<double>();
	}

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
	static void showUpdateClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermissions::pUpdateClient))
		{
			return;
		}

		_drawScreenHeader("\tUpdate Client Screen");

		string accountNumber;
		cout << "Please enter client account number: ";
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount Number is not fount, choose another one: ";
			accountNumber = clsInputValidate::readString();
		}

		clsBankClient client = clsBankClient::find(accountNumber);
		_printClientInfo(client);

		cout << "\nAre you sure you want to update this client y/n? ";
		char updateClient = 'n';
		cin >> updateClient;

		if (updateClient == 'y' || updateClient == 'Y')
		{
			cout << "\n\nUpdate client info:\n";
			cout << "__________________\n";

			_readClientInfo(client);

			clsBankClient::enSaveResults saveResult;
			saveResult = client.save();

			switch (saveResult)
			{
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Updated successfully :)\n";
				_printClientInfo(client);
				break;
			case clsBankClient::enSaveResults::svfailedEmptyObject:
				cout << "\nError account was not saved because it's empty\n";
			}
		}	
	}
};

