#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtility.h"
using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void _printClientRecordBalanceLine(clsBankClient client)
	{
		cout << "\t\t\t| " << setw(15) << left << client.accountNumber();
		cout << "| " << setw(25) << left << client.fullName();
		cout << "| " << setw(10) << left << client.accountBalance;
	}

public:
	static void showTotalBalancesScreen()
	{
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string title = "\tClient Balances Screen";
		string subTitle = "\t(" + to_string(vClients.size()) + ") Client(s).";
		_drawScreenHeader(title, subTitle);

		cout << "\t\t\t________________________________________________________________\n\n";
		cout << "\t\t\t| " << setw(15) << left << "Account Number";
		cout << "| " << setw(25) << left << "Client Name";
		cout << "| " << setw(10) << left << "Balance";
		cout << "\n\t\t\t________________________________________________________________\n\n";

		double totalBalances = clsBankClient::getTotalBalances();

		if (vClients.size() == 0)
		{
			cout << "\t\t\tNo clients available in the system!\n";
		}
		else
		{
			for (const clsBankClient &client : vClients)
			{
				_printClientRecordBalanceLine(client);
				cout << "\n";
			}
		}
		cout << "\t\t\t________________________________________________________________\n";

		cout << "\t\t\tTotal Balances = " << totalBalances;
		cout << " (" << clsUtility::convertNumberToText(totalBalances) << ")\n";
	}
};

