#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"
#include <string>
#include <limits>

using namespace std;
 


class clsInputValidate
{

public:

	template <typename T> static bool IsNumberBetween(T Number, T From, T To) {
		if (Number >= From && Number <= To)
			return true;
		else
			return false; }

	template <typename T> static T ReadNumber(string ErrorMassage = "Invalid Number, Enter again\n") {
		T Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMassage;
		}

		return Number;
	}

	template <typename T> static T ReadNumbetBetween(T From, T To, string ErrorMassage = "Number is not within range, Enter again\n")
	{
		T Number = ReadNumber<T>();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMassage;
			Number = ReadNumber<T>();
		}

		return Number;
	}

   static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) 
   {
		if (clsDate::IsDate1AfterDate2(Date, From) || (clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To)) || (clsDate::IsDate1EqualDate2(Date, To)))
		{
			return true;
		}

		if (clsDate::IsDate1AfterDate2(Date, To) || (clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From)) || (clsDate::IsDate1EqualDate2(Date, From)))
		{
			return true;
		}

		return false;
	}

   static bool IsValideDate(clsDate Date)
   { 
	   return clsDate::IsValidDate(Date);
   }

   static string ReadString()
   {
	   string Name;
	   getline(cin, Name);

	   return Name;
   }
	
};