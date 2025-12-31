#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClient.h"
#include "clsInputValidate.h"
#include "clsDepsitScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalances.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionMenueOprtions
	{eDeposit=1, eWithdraw=2, eShowTotalBalances=3, eTransfer = 4, eTransferLog = 5, eShowMainMenue=6 };

	static short ReadTransactionMenueOption()
	{
		cout << setw(37) << left << "" << "Chooes what do you want to do [1 to 6]? ";
		short Choice = clsInputValidate::ReadNumbetBetween<int>(1, 6, "Enter Number Between 1 to 6");
		return Choice;
	}

	static void _ShowDepsitScreen()
	{
		clsDepsitScreen::ShowDepsitScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalances()
	{
		clsTotalBalances::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTranferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Meune...";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _PerformTransactionsMeuneOption(enTransactionMenueOprtions TransactionMenueOprtions)
	{
		switch (TransactionMenueOprtions)
		{
		case enTransactionMenueOprtions::eDeposit:
		
			system("cls");
			_ShowDepsitScreen();
			_GoBackToTransactionMenue();
			break;

		case enTransactionMenueOprtions::eWithdraw:
		
			system("cls");
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;

		case enTransactionMenueOprtions::eShowTotalBalances:
		
			system("cls");
			_ShowTotalBalances();
			_GoBackToTransactionMenue;
			break;
		

		case enTransactionMenueOprtions::eTransfer:

			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;

		case enTransactionMenueOprtions::eTransferLog:
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;

		case enTransactionMenueOprtions::eShowMainMenue:
		
			break;
		}
	}

public:

	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pTranactoins))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "=========================================================================\n";
		cout << setw(37) << left << "" << "\t\t Transactions Menue\n";
		cout << setw(37) << left << "" << "=========================================================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "=========================================================================\n";

		_PerformTransactionsMeuneOption(enTransactionMenueOprtions(ReadTransactionMenueOption()));
	}
};

