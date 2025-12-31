#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"


using namespace std;

class clsScreen
{
protected:

	

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		
		cout << "\t\t\t\t\t__________________________________________";
		cout << "\n\n\t\t\t\t\t  " << Title;
		if (SubTitle != "")
		{
			cout << "\n\t\t\t\t\t" << SubTitle;
        }

		cout << "\n\t\t\t\t\t__________________________________________\n\n";
		cout << "\t\t\t\t\tUser: " << CurrentUser.UserName;
		cout << "\n\t\t\t\t\tData: " << clsDate::DateToString(clsDate()) << endl << endl;
	}

	static bool CheckAccessRights(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermission(Permissions))
		{
			cout << "\t\t\t\t\t__________________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.\n";
			cout << "\t\t\t\t\t__________________________________________"; 
				return false;
		}
		else
		{
			return true;
		}
	}

};

