#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"


class clsUpdateCurrencyScreen : protected clsScreen
{
private:

	static float _ReadRate()
	{
		float NewRate = 0;
		cout << "\n\nEnter New Rate: ";
		NewRate = clsInputValidate::ReadNumber<float>();

		return NewRate;
	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "____________________________________";
		cout << "\nCountry      : " << Currency.Counter();
		cout << "\nCode         : " << Currency.CurrencyCode();
		cout << "\nName         : " << Currency.CurrencyName();
		cout << "\nRate(1$) =   : " << Currency.Rate();
		cout << "\n____________________________________\n";
	}

public:

	static void _ShowUpdateScreen()
	{
		_DrawScreenHeader("Update Currency Screen");
		string CurrencyCode;
		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();
		
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found , chooes another noe: ";
			CurrencyCode = clsInputValidate::ReadString(); 
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		char Answer = ' ';
		cout << "\nAre you sure you want to update the rate of this Currency y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			cout << "\nUpdate Currency Rate:";
			cout << "\n_______________________";


			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Update Successfully :-)\n";
			_PrintCurrency(Currency);
		}

	}
};

