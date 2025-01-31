#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "Global.h"
#include "clsString.h"
#include "clsUtility.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode {emptyMode = 0, updateMode = 1, addNewMode = 2};
	enMode _mode;

	string _accountNumber;
	string _pinCode;
	double _accountBalance;
	bool _markForDelete = false;

	struct stTransferLog;
	static clsBankClient::stTransferLog _convertTransferLogLineToRecord(string transferLogLine)
	{
		clsBankClient::stTransferLog transferLog;
		vector<string> vTransferLogDetails = clsString::splitString(transferLogLine, "#//#");

		transferLog.dateTime = vTransferLogDetails[0];
		transferLog.srcAccountNumber = vTransferLogDetails[1];
		transferLog.destAccountNumber = vTransferLogDetails[2];
		transferLog.transferAmount = stod(vTransferLogDetails[3]);
		transferLog.srcNewBalance = stod(vTransferLogDetails[4]);
		transferLog.destNewBalance = stod(vTransferLogDetails[5]);
		transferLog.userName = currentUser.userName;

		return transferLog;
	}

	static clsBankClient _convertLineToClientObject(string line, string seperator = "#//#")
	{
		vector<string> vClientsData = clsString::splitString(line, seperator);
		return clsBankClient(updateMode, vClientsData.at(0), vClientsData.at(1), vClientsData.at(2), vClientsData.at(3), vClientsData.at(4),
			clsUtility::decryptText(vClientsData.at(5), 2), stof(vClientsData.at(6)));
	}

	static string _convertClientObjectToLine(clsBankClient client, string seperator = "#//#")
	{
		string clientRecord = ""; // it represents the concatenated string version of all the client details (or record)

		clientRecord += client.firstName + seperator;
		clientRecord += client.lastName + seperator;
		clientRecord += client.email + seperator;
		clientRecord += client.phone + seperator;
		clientRecord += client.accountNumber() + seperator;
		clientRecord += clsUtility::encryptText(client.pinCode, 2) + seperator;
		clientRecord += to_string(client.accountBalance);

		return clientRecord;
	}

	static clsBankClient _getEmptyClientObject()
	{
		return clsBankClient(emptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _loadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream file;
		file.open("Clients.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				if (line == "")
				{
					continue;
				}
				clsBankClient client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}
			file.close();
		}
		return vClients;
	}
	
	static void _saveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream file;
		string dataLine;

		file.open("Clients.txt", ios::out); // overwrite

		if (file.is_open())
		{
			for (clsBankClient client : vClients)
			{
				if (client.markForDelete == false)
				{
					// write only records that are not marked for delete
					dataLine = _convertClientObjectToLine(client);
					file << dataLine << "\n";
				}
			}
			file.close();
		}
	}

	void _update()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& client : vClients)
		{
			if (client.accountNumber() == accountNumber())
			{
				client = *this;
				break;
			}
		}

		_saveClientsDataToFile(vClients);
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream file;
		file.open("Clients.txt", ios::app);

		if (file.is_open())
		{
			file << dataLine << "\n";
			file.close();
		}
	}

	void _addNew()
	{
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	string _formatTransferRecordLine(double transferAmount, clsBankClient destClient, string userName, string seperator = "#//#")
	{
		string transferRecordLine;

		transferRecordLine += clsDate::getSystemDateTimeString() + seperator;
		transferRecordLine += accountNumber() + seperator;
		transferRecordLine += destClient.accountNumber() + seperator;
		transferRecordLine += to_string(transferAmount) + seperator;
		transferRecordLine += to_string(accountBalance) + seperator;
		transferRecordLine += to_string(destClient.accountBalance) + seperator;
		transferRecordLine += userName;

		return transferRecordLine;

	}

	void _recordTransferLog(double transferAmount, clsBankClient destClient, string userName)
	{
		string transferRecord = _formatTransferRecordLine(transferAmount, destClient, userName);
		fstream file;

		file.open("TransferLogs.txt", ios::app);
		if (file.is_open())
		{
			file << transferRecord << "\n";
			file.close();
		}
	}

public:
	struct stTransferLog
	{
		string dateTime;
		string srcAccountNumber;
		string destAccountNumber;
		double transferAmount;
		double srcNewBalance;
		double destNewBalance;
		string userName;
	};

	clsBankClient(enMode mode, string firstName, string lastName, string email, string phone, string accountNumber, string pinCode, double accountBalance)
		: clsPerson(firstName, lastName, email, phone)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = accountBalance;
	}

	bool isEmpty()
	{
		return _mode == emptyMode;
	}

	string accountNumber()
	{
		return _accountNumber;
	}

	void setPinCode(string pinCode)
	{
		_pinCode = pinCode;
	}

	string getPinCode()
	{
		return _pinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string pinCode;
	
	void setAccountBalance(double accountBalance)
	{
		_accountBalance = accountBalance;
	}

	double getAccountBalance()
	{
		return _accountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) double accountBalance;

	void setMarkForDelete(bool value)
	{
		_markForDelete = value;
	}

	bool getMarkForDelete()
	{
		return _markForDelete;
	}

	__declspec(property(get = getMarkForDelete, put = setMarkForDelete)) bool markForDelete;

	/* No UI related code inside object.
	void print() 
	{
		cout << "\nClient Card:";
		cout << "\n-------------------------------------";
		cout << "\nFirstname      : " << firstName;
		cout << "\nLastname       : " << lastName;
		cout << "\nFullname       : " << fullName();
		cout << "\nEmail          : " << email;
		cout << "\nPhone          : " << phone;
		cout << "\nAccount Number : " << _accountNumber;
		cout << "\nPassword       : " << _pinCode;
		cout << "\nBalance        : " << _accountBalance;
		cout << "\n-------------------------------------\n";
	}*/

	static clsBankClient find(string accountNumber)
	{
		fstream file;
		file.open("Clients.txt", ios::in); // read mode

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				if (client.accountNumber() == accountNumber)
				{
					file.close();
					return client;
				}
			}
			file.close();
		}

		return  _getEmptyClientObject();
	}
	
	static clsBankClient find(string accountNumber, string pinCode)
	{
		fstream file;
		file.open("Clients.txt", ios::in); // read mode

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				if (client.accountNumber() == accountNumber && client.pinCode == pinCode)
				{
					file.close();
					return client;
				}
			}
			file.close();
		}

		return  _getEmptyClientObject();
	}

	static bool isClientExist(string accountNumber)
	{
		clsBankClient client = clsBankClient::find(accountNumber);
		return !client.isEmpty();
	}

	enum enSaveResults {svfailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 3};

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::emptyMode:
			return enSaveResults::svfailedEmptyObject;
		case enMode::updateMode:
			_update();
			return enSaveResults::svSucceeded;
		case enMode::addNewMode:

			if (clsBankClient::isClientExist(accountNumber()))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_addNew(); // this will add new record to file or database
				_mode = enMode::updateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient getANewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& client : vClients)
		{
			if (client.accountNumber() == _accountNumber)
			{
				client.markForDelete = true;
				break;
			}
		}

		_saveClientsDataToFile(vClients);
		*this = _getEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> getClientsList()
	{
		return _loadClientsDataFromFile();
	}

	static double getTotalBalances()
	{
		double totalBalances = 0;
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient client : vClients)
		{
			totalBalances += client.accountBalance;
		}

		return totalBalances;
	}
	
	void deposit(double amount)
	{
		_accountBalance += amount;
		save();
	}

	bool withdraw(double amount)
	{
		if (amount > _accountBalance)
		{
			return false;
		}
		else
		{
			_accountBalance -= amount;
			save();
			return true;
		}
	}

	bool transfer(double amountToTransfer, clsBankClient &destClient, string userName)
	{
		if (!withdraw(amountToTransfer))
		{
			return false;
		}
		else
		{
			destClient.deposit(amountToTransfer);
			_recordTransferLog(amountToTransfer, destClient, userName);
			return true;
		}	
	}

	static vector<clsBankClient::stTransferLog> readTransferLogsFromFile()
	{
		vector<clsBankClient::stTransferLog> vTransferLogs;
		fstream file;

		file.open("TransferLogs.txt", ios::in);
		if (file.is_open())
		{
			string transferLogLine;
			while (getline(file, transferLogLine))
			{
				clsBankClient::stTransferLog transferLog = _convertTransferLogLineToRecord(transferLogLine);
				vTransferLogs.push_back(transferLog);
			}
			file.close();
		}

		return vTransferLogs;
	}

};  

