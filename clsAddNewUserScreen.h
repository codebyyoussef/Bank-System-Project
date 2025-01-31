#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
    static short _readPermissionsToSet()
    {
        short userPermissions = 0;
        char answer = 'n';

        cout << "\nDo you want give full access? y/n: ";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            return clsUser::enPermissions::pAll;
        }

        cout << "\nDo you want to give access to:\n\n";

        cout << "Show client list? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pShowClientList;
        }

        cout << "\nAdd new client? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete client? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate client? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pUpdateClient;
        }

        cout << "\nFind client? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pTransactions;
        }

        cout << "\nManage users? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nShow users login Records? y/n: ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            userPermissions += clsUser::enPermissions::pShowUsersLoginRecords;
        }

        return userPermissions;
    }

	static void _readUserInfo(clsUser& user)
	{
		cout << "\nEnter firstname: ";
		user.firstName = clsInputValidate::readString();

		cout << "\nEnter lastname: ";
		user.lastName = clsInputValidate::readString();

		cout << "\nEnter email: ";
		user.email = clsInputValidate::readString();

		cout << "\nEnter phone: ";
		user.phone = clsInputValidate::readString();

		cout << "\nEnter password: ";
		user.password = clsInputValidate::readString();

		cout << "\nEnter permissions: ";
		user.permissions = _readPermissionsToSet();
	}

    static void _printUserInfo(clsUser user)
    {
        cout << "\nUser Card:";
        cout << "\n-------------------------------------";
        cout << "\nFirstname  : " << user.firstName;
        cout << "\nLastname   : " << user.lastName;
        cout << "\nFullname   : " << user.fullName();
        cout << "\nEmail      : " << user.email;
        cout << "\nPhone      : " << user.phone;
        cout << "\nUsername   : " << user.userName;
        cout << "\nPassword   : " << user.password;
        cout << "\nPermissions : " << user.permissions;
        cout << "\n-------------------------------------\n";
    }


public:
	static void showAddNewUserScreen()
	{
		_drawScreenHeader("\tAdd New User Screen");

		string userName;
		cout << "Please enter a username: ";
		userName = clsInputValidate::readString();

		while (clsUser::isUserExist(userName))
		{
			cout << "\nUsername is already used, choose another one: ";
			userName = clsInputValidate::readString();
		}

		clsUser newUser = clsUser::getANewClientObject(userName);

        _readUserInfo(newUser);

        clsUser::enSaveResults saveResult = newUser.save();

        switch (saveResult)
        {
            case clsUser::svSucceeded:
                cout << "\nUser added successfully :)\n";
                _printUserInfo(newUser);
                break;
            case clsUser::svfailedEmptyObject:
                cout << "\nError user was not saved because it's empty\n";
                break;
            case clsUser::svFailedUserExists:
                cout << "\nError user was not saved because username is already used!\n";
        }

	}
};

