#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClient.h"
#include <fstream>

class clsTransferLogScreen : protected clsScreen
{
private:

	static void PrintLoginRegister(clsBankClient::stTransferLog TransferLogRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLogRecord.DateTime;
		cout << "| " << setw(10) << left << TransferLogRecord.SourceAccountNumber;
		cout << "| " << setw(10) << left << TransferLogRecord.DestinationAccountNumber;
		cout << "| " << setw(10) << left << TransferLogRecord.Amount;
		cout << "| " << setw(10) << left << TransferLogRecord.srcBalanceAfter;
		cout << "| " << setw(10) << left << TransferLogRecord.destBalanceAfter;
		cout << "| " << setw(10) << left << TransferLogRecord.UserName;

	}

public:

	static void ShowTransferLogScreen()
	{

		vector<clsBankClient::stTransferLog> vTransferLogRecord = clsBankClient::GetTransfersLogLista();

		string Title = "\t Transfer Log List Screen";
		string SubTitle = "\t   (" + to_string(vTransferLogRecord.size()) + ") Record (s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t________________________________________________________________";
		cout << "__________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct ";
		cout << "| " << left << setw(10) << "d.Acct ";
		cout << "| " << left << setw(10) << "Amount ";
		cout << "| " << left << setw(10) << "s.Balances ";
		cout << "| " << left << setw(10) << "d.Balances ";
		cout << "| " << left << setw(10) << "User ";
		cout << setw(8) << left << "" << "\n\t________________________________________________________________";
		cout << "__________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0)
		{
			cout << "\t\t\t\t\t Nu Record Availabe in the system!";

		}
		else
		{
			for (clsBankClient::stTransferLog TransferLog :vTransferLogRecord)
			{
				PrintLoginRegister(TransferLog);
				cout << endl;
			}

			cout << setw(8) << left << "" << "\n\t_________________________________________________________";
			cout << "______________________________________________\n";
		}
	

	}
};

