#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsUtility.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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
	static void showAddNewClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		_drawScreenHeader("\tAdd New Client Screen");
		string accountNumber;
		cout << "Please enter an account number: ";
		accountNumber = clsInputValidate::readString();

		while (clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount Number already exists, choose another one: ";
			accountNumber = clsInputValidate::readString();
		}

		clsBankClient newClient = clsBankClient::getANewClientObject(accountNumber);

		_readClientInfo(newClient);

		clsBankClient::enSaveResults saveResult = newClient.save();

		switch (saveResult)
		{
			case clsBankClient::svSucceeded:
				cout << "\nClient added successfully :)\n";
				_printClientInfo(newClient);
				break;
			case clsBankClient::svfailedEmptyObject:
				cout << "\nError account was not saved because it's empty\n";
				break;
			case clsBankClient::svFailedAccountNumberExists:
				cout << "\nThe account number is already used!\n";
		}
	}
};

