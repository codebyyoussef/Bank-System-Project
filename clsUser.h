#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtility.h"
using namespace std;

class clsUser : public clsPerson
{
private:
	enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };

	enMode _mode;
	string _userName;
	string _password;
	short _permissions;
	bool _isMarkForDelete = false;

	struct stUserLoginRecord;
	static stUserLoginRecord _convertUserLoginLineToRecord(string userLoginRecordLine)
	{
		stUserLoginRecord userLoginRecord;
		vector<string> userLoginRecordParts = clsString::splitString(userLoginRecordLine, "#//#");

		userLoginRecord.dateTime = userLoginRecordParts[0];
		userLoginRecord.userName = userLoginRecordParts[1];
		userLoginRecord.password = clsUtility::decryptText(userLoginRecordParts[2], 2);
		userLoginRecord.permissions = stoi(userLoginRecordParts[3]);

		return userLoginRecord;
	}

	string _formatLoginRecordLine(string seperator = "#//#")
	{
		string loginRecord;

		loginRecord += clsDate::getSystemDateTimeString() + seperator;
		loginRecord += userName + seperator;
		loginRecord += clsUtility::encryptText(password, 2) + seperator;
		loginRecord += to_string(permissions);

		return loginRecord;
	}

	static clsUser _convertLineToUserObject(string line, string seperator = "#//#")
	{
		vector<string> vUsersData = clsString::splitString(line, seperator);
		return clsUser(enMode::updateMode, vUsersData.at(0), vUsersData.at(1), vUsersData.at(2), vUsersData.at(3), vUsersData.at(4),
               clsUtility::decryptText(vUsersData[5], 2), stof(vUsersData.at(6)));
	}

	static string _convertUserObjectToLine(clsUser user, string seperator = "#//#")
	{
		string UserRecord = ""; // it represents the concatenated string version of all the User details (or record)

		UserRecord += user.firstName + seperator;
		UserRecord += user.lastName + seperator;
		UserRecord += user.email + seperator;
		UserRecord += user.phone + seperator;
		UserRecord += user.userName + seperator;
		UserRecord += clsUtility::encryptText(user.password, 2) + seperator;
		UserRecord += to_string(user.permissions);

		return UserRecord;
	}

	static vector<clsUser> _loadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream file;
		file.open("Users.txt", ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				if (line == "")
				{
					continue;
				}
				clsUser user = _convertLineToUserObject(line);
				vUsers.push_back(user);
			}
			file.close();
		}
		return vUsers;
	}

	static void _saveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream file;
		string dataLine;

		file.open("Users.txt", ios::out); // overwrite

		if (file.is_open())
		{
			for (clsUser user : vUsers)
			{
				if (user.isMarkForDelete() == false)
				{
					// write only records that are not marked for delete
					dataLine = _convertUserObjectToLine(user);
					file << dataLine << "\n";
				}
			}
			file.close();
		}
	}

	void _update()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.userName == _userName)
			{
				User = *this;
				break;
			}
		}

		_saveUsersDataToFile(vUsers);
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream file;
		file.open("Users.txt", ios::app);

		if (file.is_open())
		{
			file << dataLine << "\n";
			file.close();
		}
	}

	void _addNew()
	{
		_addDataLineToFile(_convertUserObjectToLine(*this));
	}

	static clsUser _getEmptyUserObject()
	{
		return clsUser(emptyMode, "", "", "", "", "", "", 0);
	}


public:
	enum enPermissions
	{
		pAll = -1,
		pShowClientList = 1,
		pAddNewClient = 2,
		pDeleteClient = 4,
		pUpdateClient = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64,
		pShowUsersLoginRecords = 128
	};

	struct stUserLoginRecord
	{
		string dateTime;
		string userName;
		string password;
		short permissions;
	};

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, string userName, string passwd, short permissions)
		: clsPerson(firstName, lastName, email, phone)
	{
		_mode = mode;
		_userName = userName;
		_password = passwd;
		_permissions = permissions;
	}

	bool isEmpty()
	{
		return _mode == enMode::emptyMode;
	}

	bool isMarkForDelete()
	{
		return _isMarkForDelete;
	}

	void setUserName(string userName)
	{
		_userName = userName;
	}
	string getUserName()
	{
		return _userName;
	}
	__declspec(property(get = getUserName, put = setUserName)) string userName;
	
	void setPassword(string password)
	{
		_password = password;
	}
	string getPassword()
	{
		return _password;
	}
	__declspec(property(get = getPassword, put = setPassword)) string password;
	
	void setPermissions(short permissions)
	{
		_permissions = permissions;
	}
	short getPermissions()
	{
		return _permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions)) short permissions;

	static clsUser find(string userName)
	{
		fstream file;
		file.open("Users.txt", ios::in); // read mode

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsUser user = _convertLineToUserObject(line);
				if (user.userName == userName)
				{
					file.close();
					return user;
				}
			}
			file.close();
		}

		return  _getEmptyUserObject();
	}

	static clsUser find(string userName, string password)
	{
		fstream file;
		file.open("Users.txt", ios::in); // read mode

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsUser user = _convertLineToUserObject(line);
				if (user.userName == userName && user.password == password)
				{
					file.close();
					return user;
				}
			}
			file.close();
		}

		return  _getEmptyUserObject();
	}

	static bool isUserExist(string userName)
	{
		clsUser user = clsUser::find(userName);
		return !user.isEmpty();
	}

	enum enSaveResults { svfailedEmptyObject = 0, svSucceeded = 1, svFailedUserExists = 3 };

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
				if (clsUser::isUserExist(_userName))
				{
					return enSaveResults::svFailedUserExists;
				}
				else
				{
					_addNew(); // this will add new record to file or database
					_mode = enMode::updateMode;
					return enSaveResults::svSucceeded;
				}
		}
	}

	static clsUser getANewClientObject(string userName)
	{
		return clsUser(enMode::addNewMode, "", "", "", "", userName, "", 0);
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& user : vUsers)
		{
			if (_userName == "Admin")
				return false;

			if (user.userName == _userName)
			{
				user._isMarkForDelete = true;
				break;
			}
		}

		_saveUsersDataToFile(vUsers);
		*this = _getEmptyUserObject();
		return true;
	}

	static vector<clsUser> getUserList()
	{
		return _loadUsersDataFromFile();
	}

	bool checkAcessPermission(enPermissions permission)
	{
		if (this->permissions == enPermissions::pAll)
		{
			return true;
		}
		else if ((permission & this->permissions) == permission)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void recordLogin()
	{
		string loginRecordLine = _formatLoginRecordLine();
		fstream file;

		file.open("LoginRegister.txt", ios::app);
		if (file.is_open())
		{
			file << loginRecordLine << "\n";
			file.close();
		}
	}

	static vector<stUserLoginRecord> readUsersLoginRecordsFromFile()
	{
		vector<stUserLoginRecord> vUsersLoginRecords;
		fstream file;

		file.open("LoginRegister.txt", ios::in);
		if (file.is_open())
		{
			string userLoginRecordLine;
			stUserLoginRecord userLoginRecord;
			while (getline(file, userLoginRecordLine))
			{
				userLoginRecord = _convertUserLoginLineToRecord(userLoginRecordLine);
				vUsersLoginRecords.push_back(userLoginRecord);
			}
			file.close();
		}
		return vUsersLoginRecords;
	}
};


