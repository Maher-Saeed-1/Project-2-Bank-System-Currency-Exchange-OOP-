#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"

class clsCurrenciesLsitScreen : protected clsScreen
{
private:
	static void _PrintCurrenciesLien(clsCurrency CurrenciesLsitScreen)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << CurrenciesLsitScreen.Counter();
		cout << "| " << setw(8) << left << CurrenciesLsitScreen.CurrencyCode();
		cout << "| " << setw(45) << left << CurrenciesLsitScreen.CurrencyName();
		cout << "| " << setw(10) << left << CurrenciesLsitScreen.Rate();
		
	}
	


public:

	static void ShowListCurenciesScreen()
	{
		vector <clsCurrency> vListScreen = clsCurrency::GeturrenciesList();
		string Titel = "\tCurrencies List Screen";
		string SubTitle = "\t(" + to_string(vListScreen.size()) + ") Currency.";

		_DrawScreenHeader(Titel, SubTitle);

		cout << setw(8) << left << "" << "___________________________________________________________________";
		cout << "___________________________________________\n";

		cout << setw(8) << left << "" << "| " << setw(30) << left << "Counter";
		cout << "| " << setw(8) << left << "Code";
		cout << "| " << setw(45) << left << "Name";
		cout << "| " << setw(10) << left << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t______________________________________________________________";
		cout << "___________________________________________\n";
		
		if (vListScreen.size() == 0)
		{
			cout << "\t\t\t\t\t Nu Currencies List!";
		}
		else
		{
			for (clsCurrency C : vListScreen)
			{
				_PrintCurrenciesLien(C);
				cout << endl;
			}
			cout <<  setw(8) << left << "" << "______________________________________________________________";
			cout << "________________________________________________\n";
		}
		
		
	}
};

