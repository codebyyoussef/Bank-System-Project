#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;


class clsManageUsersMenuScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOptions {listUsers = 1, addNewUser = 2, deleteUser = 3, updateUser = 4, findUser = 5, mainMenu = 6};

    static short _readManageUsersMenuOption()
    {
        short choice;
        cout << setw(75) << "Choose what you want to do? [1 to 6]: ";
        choice = clsInputValidate::readNumberBetween<short>(1, 6, "\t\t\t\t     Enter a number between 1 and 6: ");
        return choice;
    }

    static void _goBackToManageUsersMenuScreen()
    {
        cout << "\nPress any key to go back to Manage Users Menu...";
        system("pause>0");
        showManageUsersMenuScreen();
    }

    static void _showUserListScreen()
    {
        clsUserListScreen::showUserListScreen();
    }
    
    static void _showAddNewUserScreen()
    {
        clsAddNewUserScreen::showAddNewUserScreen();
    }
    
    static void _showDeleteUserScreen()
    {
        clsDeleteUserScreen::showDeleteUserScreen();
    }
    
    static void _showUpdateUserScreen()
    {
        clsUpdateUserScreen::showUpdateUserScreen();
    }
    
    static void _showFindUserScreen()
    {
        clsFindUserScreen::showFindUserScreen();
    }

    static void _performManageUsersMenuOption(enManageUsersMenuOptions manageUsersMenuOption)
    {
        switch (manageUsersMenuOption)
        {
            case enManageUsersMenuOptions::listUsers:
                system("cls");
                _showUserListScreen();
                _goBackToManageUsersMenuScreen();
                break;
            case enManageUsersMenuOptions::addNewUser:
                system("cls");
                _showAddNewUserScreen();
                _goBackToManageUsersMenuScreen();
                break;
            case enManageUsersMenuOptions::deleteUser:
                system("cls");
                _showDeleteUserScreen();
                _goBackToManageUsersMenuScreen();
                break;
            case enManageUsersMenuOptions::updateUser:
                system("cls");
                _showUpdateUserScreen();
                _goBackToManageUsersMenuScreen();
                break;
            case enManageUsersMenuOptions::findUser:
                system("cls");
                _showFindUserScreen();
                _goBackToManageUsersMenuScreen();
                break;
            case enManageUsersMenuOptions::mainMenu:
            {

            }
        }
    }

public:
	static void showManageUsersMenuScreen()
	{
        system("cls");

        if (!_checkAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }

		_drawScreenHeader("\tManage Users Screen");

        cout << setw(80) << right << "==========================================\n";
        cout << setw(80) << "              Manage Users Menu           \n";
        cout << setw(80) << "==========================================\n";
        cout << setw(80) << "  [1] List Users.                         \n";
        cout << setw(80) << "  [2] Add New User.                       \n";
        cout << setw(80) << "  [3] Delete User.                        \n";
        cout << setw(80) << "  [4] Update User.                        \n";
        cout << setw(80) << "  [5] Find User.                          \n";
        cout << setw(80) << "  [6] Main Menu.                          \n";
        cout << setw(80) << "==========================================\n";
        _performManageUsersMenuOption((enManageUsersMenuOptions)_readManageUsersMenuOption());
	}
};

