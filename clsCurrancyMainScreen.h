#pragma once
#include <iostream>
#include "clsScreen.h"
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsCurrenciesLsitScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculator.h"


class clsCurrancyMainScreen : protected clsScreen
{
private:
	enum enCurrency {eListCurrency = 1, eFindCurrency = 2, eUpdateCurrency=3, eCurrencyCalculater = 4, eExit = 5};

	static short _ReadCurrency()
	{
		short CurrencyData =0;
		cout << "\nChoose what do you want to do? [1 to 5]? ";
		CurrencyData = clsInputValidate::ReadNumbetBetween<int>(1, 5);

		return CurrencyData;
	}

	static void _ShowListCurrencyScreen()
	{
		clsCurrenciesLsitScreen::ShowListCurenciesScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyScreen()
	{
		clsUpdateCurrencyScreen::_ShowUpdateScreen();
	}

	static void _ShowCurrencyCalculator()
	{
		clsCurrencyCalculator::ShowCalculatorScreen();
	}

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
		
		system("pause>0");
		ShowCurrancyMainMenue();
	}

	static void _PerforMainMeunOption(enCurrency Currency)
	{
		switch (Currency)
		{
		case enCurrency::eListCurrency:
			system("cls");
			_ShowListCurrencyScreen();
			_GoBackToMainMenue();
			break;

		case enCurrency::eFindCurrency:
			system("cls");
			
			_ShowFindCurrencyScreen();
			_GoBackToMainMenue();
			break;

		case enCurrency::eUpdateCurrency:
			system("cls");
		
			_ShowUpdateCurrencyScreen();
			_GoBackToMainMenue();
			break;

		case enCurrency::eCurrencyCalculater:
			system("cls");
			
			_ShowCurrencyCalculator();
			_GoBackToMainMenue();
			break;

		case enCurrency::eExit:
			system("cls");
			break;


		}
	}

public:
	 
	static void ShowCurrancyMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "=========================================\n"; 
		cout << setw(37) << left << "" << "\t\tCurrency Exchange Manue\n";
		cout << setw(37) << left << "" << "=========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currency.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue\n";
		cout << setw(37) << left << "" << "=========================================\n";
		_PerforMainMeunOption(enCurrency(_ReadCurrency()));
	}
};

