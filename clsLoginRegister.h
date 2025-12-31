#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>


class clsLoginRegister : protected clsScreen
{
private:

	static void PrintLoginRegister(clsUser::stLoginRegisterRecord LoginRegisterRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.DateTime;
		cout << "| " << setw(20) << left << LoginRegisterRecord.UserName;
		cout<<  "| " << setw(20) << left << LoginRegisterRecord.Password;
		cout << "| " << setw(10) << left << LoginRegisterRecord.Permissions;
		
	}

public:

	static void ShowLoginRegsterListScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}

		vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginRegisterList();

		string Title = "\t Login Register List Screen";
		string SubTitle = "\t   (" + to_string(vLoginRegisterRecord.size()) + ") Record (s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t________________________________________________________________";
		cout << "__________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Passowrd";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t________________________________________________________________";
		cout << "__________________________________\n" << endl;

		if (vLoginRegisterRecord.size() == 0)
		{
			cout << "\t\t\t\t\t Nu Record Availabe in the system!";

		}
		else
		{
			for (clsUser::stLoginRegisterRecord Login : vLoginRegisterRecord)
			{
				PrintLoginRegister(Login);
				cout << endl;
			}

			cout << setw(8) << left << "" << "\n\t_________________________________________________________";
			cout << "______________________________________________\n";
		}
	}

};

