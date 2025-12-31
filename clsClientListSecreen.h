#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClient.h"
#include <iomanip>
 
using namespace std;

class clsClientListSecreen :protected clsScreen
{
	static void PrintClientRecordLine(clsBankClient Client)
	{

		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << setw(20) << left << Client.FullName();
		cout << setw(12) << left << Client.Phone;
		cout << setw(20) << left << Client.Email;
		cout << setw(10) << left << Client.PinCode;
		cout << setw(12) << left << Client.AccountBalance;
	}

public:

	static void ShowClientList()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pListClient))
		{
			return;
		}

		vector<clsBankClient> vClient = clsBankClient::GetClientsList();
		string Title = "\t Client List Screen";
		string SubTitle = "\t   (" + to_string(vClient.size()) + ") Client (s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t________________________________________________________________";
		cout << "__________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(20) << "Client Number";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "PinCod";
		cout << "| " << left << setw(12) << "Accund Balance";
		cout << setw(8) << left << "" << "\n\t________________________________________________________________";
		cout << "__________________________________\n" << endl;

		if (vClient.size() == 0)
		{
			cout << "\t\t\t\t\t Nu Client Availabe in the system!";

		}
		else
		{
			for (clsBankClient Client : vClient)
			{
				PrintClientRecordLine(Client);
			    cout << endl;
			}

			cout << setw(8) << left << "" << "\n\t_________________________________________________________";
			cout << "______________________________________________\n";
		}

	}


};

