#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClient.h"
#include "clsUser.h"
#include <string>
#include "clsInputValidate.h"
#include <iomanip>


class clsAddNewUserScreen : protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter First Name:";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name:";
		User.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email:";
		User.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();
		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();
	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

	static int _ReadPermissionsToSet()
	{
		int Permissions = 0;
		char Answer = ' ';

		cout << "\nDo you want to give full access? y/n?";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo yow want to give access to : \n";

		cout << "\nShow Clinet List? y/n: ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pListClient;
		}

		cout << "\nAdd new Client y/n: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete ClinetY/N: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client y/n: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client y/n: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions Client y/n: ";
		cin >> Answer; 
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pTranactoins;
		}

		cout << "\nManage User Client y/n: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nLogin Register Record y/n: ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'y')
		{
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  AddNew User Screen");

		string UserName = "";

		cout << "Please Enter User Name:";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Name Is Already Used, Choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceded:
		{
			cout << "\nUser Addeded Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError User was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResults::svFaildUserExists:
		{
			cout << "\nError User was not saved because UserName is used!\n";
			break;

		}
		}
	}
	 
};

