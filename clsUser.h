#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <fstream>


class clsUser : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString()+ Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	static clsUser _ConvertLineUserOpject(string Line, string Seperator = "/##/")
	{
		vector <string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4],clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}

	
	static string _ConverUserObjectToline(clsUser User, string Seperator = "/##/")
	{
		string UserRecord = "";

		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User._UserName + Seperator;
		UserRecord += clsUtil::EncryptText(User._Password) + Seperator;
		UserRecord += to_string( User._Permissions);

		return UserRecord;
	}

	struct stLoginRegisterRecord;
	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seprator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seprator);

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText((LoginRegisterDataLine[2]));
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	static vector<clsUser> _LoadUserDataFromFile()
	{
		vector <clsUser> vUsers;


		fstream MyFile;
		

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineUserOpject(Line);

				vUsers.push_back(User);
			}
			MyFile.close();
	    }

		return vUsers;
	}

	static void _SaveUserDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
		 
			for (clsUser C : vUsers)
			{
				if (C._MarkedForDelete == false)
				{
					string DataLine = _ConverUserObjectToline(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> vUser;
		vUser = _LoadUserDataFromFile();

		for (clsUser& C : vUser)
		{
			if (C.UserName == UserName)
			{
				C = *this;
				break;
			}
		}

		_SaveUserDataToFile(vUser);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConverUserObjectToline(*this));
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	enum enPermissions {eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4 ,pUpdateClient = 8
	, pFindClient = 16, pTranactoins = 32, pManageUsers = 64, pLoginRegister = 128};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};


	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineUserOpject(Line);

				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

		 MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineUserOpject(Line);

				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceded = 1, svFaildUserExists = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults:: svSucceded;
			break;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceded;
			}
			break;
		}
		}
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> vUser;
		vUser = _LoadUserDataFromFile();

		for (clsUser& C : vUser)
		{
			if (C.UserName == _UserName)
			{
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveUserDataToFile(vUser);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode,"", "", "", "", UserName, "", 0);
	}

	static vector<clsUser> GetUsersList()
	{
		return _LoadUserDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::eAll)
		{
			return true;
		}
		if ((Permissions & this->Permissions) == Permissions)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void RegisterLogIn()
	{
		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister - Notepad.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vUser;

		fstream MyFile;
		MyFile.open("LoginRegister - Notepad.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line = "";

			while (getline(MyFile, Line))
			{
				stLoginRegisterRecord Login = _ConvertLoginRegisterLineToRecord(Line);
				vUser.push_back(Login);
			}

			MyFile.close();

		}
		return vUser;
	}
};

