#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include <fstream>
#include "clsDate.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
	

	static bool _Login()
	{
		bool LoginFaild = false;

		string _UserName;
		string _Password;
		int FaildLoginCount = 0;

		do
		{
			if (LoginFaild)
			{
				FaildLoginCount++;
				cout << "\nInvaid Username/Password!";
				cout << "\nYou have " << (3-FaildLoginCount) << " Trials to login.\n\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\nYour are Locked after 3 faild trails";
				return false;
			}

			cout << "Enter Username? ";
			cin >> _UserName;
			cout << "Enter Password? ";
			cin >> _Password;

			CurrentUser = clsUser::Find(_UserName, _Password);

			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);

		   CurrentUser.RegisterLogIn();
		
			clsMainScreen::ShowMainMenue();
			return true;
	}


public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   Login Screen");
		return _Login();
	}
};

