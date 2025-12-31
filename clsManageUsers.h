#pragma once

#include <iostream>
#include <iomanip>
#include "clsClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScteen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


class clsManageUsers : protected clsScreen
{
private:

	enum enManageUsersMenueOptions {
		eListUser = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMeune= 6};

	static int _ReadManageUsersMenueOption()
	{
		int AccountNumber = 0;
		cout << "Choise what do you want to do? [1 to 6]: ";
		AccountNumber = clsInputValidate::ReadNumbetBetween<int>(1, 6, "Enter Number Between [1 to 6]: ");

		return AccountNumber;
    }

	static void _GoBackToManageUserMenueOption()
	{
		cout << "\n\nPress any key to go back to Manage users Menue ...";
		system("pause>0");
		ShowManageUsersMenue();
	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUsersScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUsersScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUsersScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUsersScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerFormManageUsersMenueOption(enManageUsersMenueOptions ManagUsersMenueScreen)
	{
		switch (ManagUsersMenueScreen)
		{

		case enManageUsersMenueOptions::eListUser:

			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUserMenueOption();
			break;


		case enManageUsersMenueOptions::eAddNewUser:

			system("cls");
			_ShowAddNewUsersScreen();
			_GoBackToManageUserMenueOption();
			break;

		case enManageUsersMenueOptions::eDeleteUser:

			system("cls");
			_ShowDeleteUsersScreen();
			_GoBackToManageUserMenueOption();
			break;

		case enManageUsersMenueOptions::eUpdateUser:

			system("cls");
			_ShowUpdateUsersScreen();
			_GoBackToManageUserMenueOption();
			break;

		case enManageUsersMenueOptions::eFindUser:

			system("cls");
			_ShowFindUsersScreen();
			_GoBackToManageUserMenueOption();
			break;

		case enManageUsersMenueOptions::eMainMeune:


			break;

		};
	}

public:

	static void ShowManageUsersMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Manage Users Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerFormManageUsersMenueOption(enManageUsersMenueOptions(_ReadManageUsersMenueOption()));
	}
};

