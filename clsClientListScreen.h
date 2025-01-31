#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void _printClientRecordLine(clsBankClient client)
	{
		cout << "\t| " << setw(15) << left << client.accountNumber();
		cout << "| " << setw(25) << left << client.fullName();
		cout << "| " << setw(12) << left << client.phone;
		cout << "| " << setw(25) << left << client.email;
		cout << "| " << setw(10) << left << client.pinCode;
		cout << "| " << setw(10) << left << client.accountBalance;
	}

public:
    static void showClientListScreen()
	{
		if (!_checkAccessRights(clsUser::enPermissions::pShowClientList))
		{
			return;// this will exit the function and it will not continue
		}

		vector<clsBankClient> vClients = clsBankClient::getClientsList();
		string title = "\t Client List Screen";
		string subTitle = "\t (" + to_string(vClients.size()) + ") Client(s)";

		/*cout << setw(50) << "Client List (" << vClients.size() << ") Client(s).\n";*/
		_drawScreenHeader(title, subTitle);
		cout << "\t____________________________________________________________________________________________________________\n\n";
		cout << "\t| " << setw(15) << left << "Account Number";
		cout << "| " << setw(25) << left << "Client Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(25) << left << "Email";
		cout << "| " << setw(10) << left << "Pin Code";
		cout << "| " << setw(10) << left << "Balance";
		cout << "\n\t____________________________________________________________________________________________________________\n\n";

		if (vClients.size() == 0)
		{
			cout << "\tNo clients available in the system!\n";
		}
		else
		{
			for (const clsBankClient& client : vClients)
			{
				_printClientRecordLine(client);
				cout << "\n";
			}
		}
		cout << "\t____________________________________________________________________________________________________________\n\n";
	}
};

