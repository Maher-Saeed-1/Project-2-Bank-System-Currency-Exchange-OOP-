#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"


class clsCurrencyCalculator : protected clsScreen
{
private:

	static float _ReadAmount()
	{
		float Amound = 0;
		cout << "\nEnter Amount to Exchange: ";
		Amound = clsInputValidate::ReadNumber<float>();

		return Amound;
	}

	static clsCurrency _GetCurrency(string Message)
	{
		string CurrencyCode;
		cout << Message << endl;

		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, chooes anthoer noe: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static void _PrintCurrency(clsCurrency Currency, string Title)
	{
		cout << "\n" << Title << "\n";
		cout << "____________________________________";
		cout << "\nCountry      : " << Currency.Counter();
		cout << "\nCode         : " << Currency.CurrencyCode();
		cout << "\nName         : " << Currency.CurrencyName();
		cout << "\nRate(1$) =   : " << Currency.Rate();
		cout << "\n____________________________________\n";
	}

	static void _PrintCalculationResult(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_PrintCurrency(Currency1, "Convert From:");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);
		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}

		cout << "\nConvert from USD to: \n";
		_PrintCurrency(Currency2, "To");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode();
	}

public:

	static void ShowCalculatorScreen()
	{
		char Contiune = 'Y';

		while (Contiune == 'y' || Contiune == 'Y')
		{
			system("cls");
			_DrawScreenHeader("\tUpdate Currency Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
		    clsCurrency CurrencyTo = _GetCurrency("\nPlease ENter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalculationResult(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform anthoer claculation ? y/n? ";
			cin >> Contiune;
		}
	}
};

