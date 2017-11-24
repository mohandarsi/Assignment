#pragma once
#include "Interfaces.h"

using namespace std;
class User : public IUser
{
private:
	string m_userName;
	string m_userId;
public:
	User(string userName,string userId);
	string GetUserName() { return m_userName; }
	string GetUserId() { return m_userId; }
	/// <summary>
	/// Factory method to create bid
	/// </summary>
	/// <param name="user">user of the bid</param>
	/// <param name="value">bid value</param>
	/// <returns></returns>
	static IUser* Create(const string &user, const string &value)
	{
		return new User(user, value);
	}
};

