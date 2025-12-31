#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>


class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Countery;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConverLinetoCurrencyOpject(string Line, string Seperator = "#//#")
	{
		vector<string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stod(vCurrencyData[3]));
	}

	static string _ConverCurrencyOpjectToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		string stCurrencyRecord = "";

		stCurrencyRecord += Currency.Counter() + Seperator;
		stCurrencyRecord += Currency.CurrencyCode() + Seperator;
		stCurrencyRecord += Currency.CurrencyName() + Seperator;
		stCurrencyRecord += to_string(Currency.Rate());

		return stCurrencyRecord;
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector <clsCurrency> vCurrency;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";
			
			while (getline(MyFile, Line))
			{
				clsCurrency Currnecy = _ConverLinetoCurrencyOpject(Line);

				vCurrency.push_back(Currnecy);
			}
			MyFile.close();
		}

		return vCurrency;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsCurrency C : vCurrency)
			{
				DataLine = _ConverCurrencyOpjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> _vCurrency;

		_vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : _vCurrency)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(_vCurrency);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Countery, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Countery = Countery;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector<clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencyDataFromFile();
	}

	
    bool IsEmpty()
	{
		return _Mode = enMode::EmptyMode;
	}

	string Counter()
	{
		return _Countery;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCounter(string Counter)
	{
		Counter = clsString::UpperAllString(Counter);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConverLinetoCurrencyOpject(Line);

				if (clsString::UpperAllString(Currency.Counter()) == Counter)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConverLinetoCurrencyOpject(Line);

				if (clsString::UpperAllString(Currency.CurrencyCode()) == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency	C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}

	static bool IsCurrencyExistName(clsCurrency C1)
	{
		return (!C1.IsEmpty());
	}

	static  vector <clsCurrency> GeturrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	enum enSaveResults { svSucceeded = 1, svFaildEmptyOpject = 0 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::UpdateMode:
		{
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::EmptyMode:
		{
			return enSaveResults::svFaildEmptyOpject;
			break;
		}

		}
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currenct2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currenct2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currenct2.Rate());
	}

};

