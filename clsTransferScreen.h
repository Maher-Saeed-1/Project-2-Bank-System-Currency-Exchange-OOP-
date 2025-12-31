#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClient.h"
#include "clsUser.h"
#include "Global.h"


class clsTransferScreen : protected clsScreen
{
private:

	static void _PrintTranfer(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n\n_______________________________";
		cout << "\n\nFull Name   :" << Client.FullName();
		cout << "\nAcc Number    :" << Client.AccountNumber();
		cout << "\nBalance       :" << Client.AccountBalance;
		cout << "\n\n_______________________________\n\n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer Too: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAvter Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static float _ReadAmount(clsBankClient SourceClient)
	{
		float Amount;

		cout << "\nEnter Tranfer Amount? ";
		Amount = clsInputValidate::ReadNumber<float>();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the available Balance, Enter amother Amount ?";
			Amount = clsInputValidate::ReadNumber<float>();
		}

		return Amount;
	}
	
public:

	static void ShowTranferScreen()
	{
		_DrawScreenHeader("Transfer Screen");

		
		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintTranfer(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintTranfer(DestinationClient);

		float Amount = _ReadAmount(SourceClient);

		char Answer = ' ';
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName ))
			{
				cout << "\nTranfer done successfully\n";
				
			}
			else
			{
				cout << "\nTransfer Faild\n";
			}
		}
		

		_PrintTranfer(SourceClient);
		_PrintTranfer(DestinationClient);
	}
};

