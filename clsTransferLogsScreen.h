#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsTransferLogsScreen : protected clsScreen
{
private:
	static void _printTranserfLogDetails(clsBankClient::stTransferLog transferLog)
	{
		cout << "\t| " << setw(20) << left << transferLog.dateTime;
		cout << "| " << setw(20) << left << transferLog.srcAccountNumber;
		cout << "| " << setw(20) << left << transferLog.destAccountNumber;
		cout << "| " << setw(20) << left << transferLog.transferAmount;
		cout << "| " << setw(20) << left << transferLog.srcNewBalance;
		cout << "| " << setw(20) << left << transferLog.destNewBalance;
		cout << "| " << setw(15) << left << transferLog.userName;
	}

public:
	static void showTransferLogsScreen()
	{
		vector<clsBankClient::stTransferLog> vTransferLogs = clsBankClient::readTransferLogsFromFile();

		string title = "\tTransfer Logs Screen";
		string subTitle = "\t   (" + to_string(vTransferLogs.size()) + ") Record(s).";
		_drawScreenHeader(title, subTitle);

		cout << "\t________________________________________________________________________________________________________________________________________________\n\n";
		cout << "\t| " << setw(20) << left << "Date/Time";
		cout << "| " << setw(20) << left << "Src Account Number";
		cout << "| " << setw(20) << left << "Dest Account Number";
		cout << "| " << setw(20) << left << "Amount Transferred";
		cout << "| " << setw(20) << left << "Src New Balance";
		cout << "| " << setw(20) << left << "Dest New Balance";
		cout << "| " << setw(15) << left << "Username";
		cout << "\n\t________________________________________________________________________________________________________________________________________________\n\n";

		if (vTransferLogs.size() == 0)
		{
			cout << "\tNo Transfer log available in the system!\n";
		}
		else
		{
			for (const clsBankClient::stTransferLog& transferLog : vTransferLogs)
			{
				_printTranserfLogDetails(transferLog);
				cout << "\n";
			}
		}
		cout << "\t________________________________________________________________________________________________________________________________________________\n\n";
	}
};

