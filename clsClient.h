#pragma once

#include <iostream>
#include "clsString.h"
#include <string>
#include <vector>
#include"clsPerson.h"
#include <fstream>
#include "clsDate.h"
#include "Global.h"
#include <fstream>


class clsBankClient : public clsPerson
{
private:

	
	enum emMode{EmptyMode = 0, UpdateMode = 1, AddNew = 2};
	emMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDeletd = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seprator = "#//#")
	{
		vector <string> vClientDate;
		vClientDate = clsString::Split(Line, Seprator);

		return clsBankClient(emMode::UpdateMode, vClientDate[0], vClientDate[1], vClientDate[2], vClientDate[3], vClientDate[4],
			vClientDate[5], stod(vClientDate[6]));
	}

	static string _ConvertLientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Separator;
		stClientRecord += Client.LastName + Separator;
		stClientRecord += Client.Email + Separator;
		stClientRecord += Client.Phone + Separator;
		stClientRecord += Client.AccountNumber() + Separator;
		stClientRecord += Client.PinCode + Separator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	static vector <clsBankClient> _LoadClientDataFromFile()
	{
		vector <clsBankClient> _vClient;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Lien;

			while (getline(MyFile, Lien))
			{
				clsBankClient Client = _ConvertLineToClientObject(Lien);

				_vClient.push_back(Client);
			}

			MyFile.close();
		}

		return _vClient;
	}

	static void _SaveClientDataToFile(vector <clsBankClient> vClient)
	{
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out);

	   string DataLien;

	   if (Myfile.is_open())
	   {
		   for (clsBankClient C : vClient)
		   {
			   if (C.MarkedForDeleted() == false)
			   {
				   DataLien = _ConvertLientObjectToLine(C);
				   Myfile << DataLien << endl;
			   }
		   }
		   Myfile.close();
	   }
	}

	void _UpdateClient()
	{
		vector <clsBankClient> _vBankClient;
		_vBankClient = _LoadClientDataFromFile();

		for (clsBankClient& C : _vBankClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientDataToFile(_vBankClient);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertLientObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(emMode::EmptyMode,"", " "," "," ", " ","",0);
	}

	 struct stTransferLog;
	
	static stTransferLog _ConvertLineToTransferOpject(string Lien, string seprator = "#//#")
	{
		vector <string> vTransferLog = clsString::Split(Lien, seprator);
		stTransferLog TransferLog;

		TransferLog.DateTime = vTransferLog[0];
		TransferLog.SourceAccountNumber = vTransferLog[1];
		TransferLog.DestinationAccountNumber = vTransferLog[2];
		TransferLog.Amount = stoi(vTransferLog[3]);
		TransferLog.srcBalanceAfter = stoi(vTransferLog[4]);
		TransferLog.destBalanceAfter = stoi(vTransferLog[5]);
		TransferLog.UserName = vTransferLog[6];

		return TransferLog;
	}


	string _PerpareTransferLogRecord(float Amount, clsBankClient DestinationCleint, string UserName, string Seprater = "#//#")
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seprater;
		TransferLogRecord += AccountNumber() + Seprater;
		TransferLogRecord += DestinationCleint.AccountNumber() + Seprater;
		TransferLogRecord += to_string(Amount) + Seprater;
		TransferLogRecord += to_string(AccountBalance) + Seprater;
		TransferLogRecord += to_string(DestinationCleint.AccountBalance) + Seprater;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}



	void _RegisterTransferLog(float Amount, clsBankClient DestinationCleint , string UserName)
	{
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::out | ios::app);

		string stDataLine;
		stDataLine = _PerpareTransferLogRecord(Amount, DestinationCleint, UserName);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;
			MyFile.close();
		}

	}


public:

	clsBankClient(emMode Mode, string FirstName, string LastName, string Email, string Phone
		, string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	static struct stTransferLog
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		double srcBalanceAfter;
		double destBalanceAfter;
		string UserName;
	};

	bool IsEmpty()
	{
		return (_Mode == emMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDeletd;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void setPinCod(string PinCod)
	{
		_PinCode = PinCod;
	}

	string GetPinCod()
	{
		return _PinCode;
	}

	_declspec(property(get = GetPinCod, put = setPinCod))string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	_declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;


	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Lien;
			while (getline(MyFile, Lien))
			{
				clsBankClient Client = _ConvertLineToClientObject(Lien);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCod)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Lien;
			while (getline(MyFile, Lien))
			{
				clsBankClient Client = _ConvertLineToClientObject(Lien);

				if (Client.AccountNumber() == AccountNumber && Client.GetPinCod() == PinCod)
				{
					MyFile.close();
					return Client;
				}

			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static enum enSaveResults {svSucceeded = 1, svFaildEmptyObject = 0, svFaildAccountNumberExists = 3};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case emMode::UpdateMode:
		{
			_UpdateClient();

			return enSaveResults::svSucceeded;

			break;
		}

		case emMode::EmptyMode:
		{
			return enSaveResults::svFaildEmptyObject;

			break;
		}

		case emMode::AddNew:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = emMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}

		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDeletd = true;
				break;
			}
		}
		_SaveClientDataToFile(_vClients);

		*this = _GetEmptyClientObject();
		return true;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(emMode::AddNew," ", " ", " ", " ", AccountNumber, "", 0);
	}
	

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vTotalBalances = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vTotalBalances)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

	void Depsit(double Amound)
	{
		_AccountBalance += Amound;
		Save();
	}

	bool Withdraw(double Amound)
	{
		if (Amound > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amound;
			Save(); 
			return true;
		}
		
	}
	
	bool Transfer(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		
		Withdraw(Amount);
		DestinationClient.Depsit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);

		return true;

	}

	static vector<stTransferLog> GetTransfersLogLista()
	{
		vector<stTransferLog> vTransferLog;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			stTransferLog TransferLog;

			while(getline(MyFile, Line))
			{
				TransferLog = _ConvertLineToTransferOpject(Line);
				vTransferLog.push_back(TransferLog);
			}

			
			MyFile.close();
		}
		return vTransferLog;
	}

};

