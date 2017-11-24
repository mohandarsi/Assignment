#pragma once
#include "Interfaces.h"

class Bid : public IBid
{
private:
	Bid(const IUser::IUserPtr &user, const double &value);
	IUser::IUserPtr m_user;
	double m_value;

public:
	void SetValue(const double &value)
	{
		m_value = value;
	}

	double GetValue() const
	{
		return m_value ;
	}

	const IUser::IUserPtr GetUser()
	{
		return m_user;
	}

	/// <summary>
	/// Factory method to create bid
	/// </summary>
	/// <param name="user">user of the bid</param>
	/// <param name="value">bid value</param>
	/// <returns></returns>
	static IBid* Create(const IUser::IUserPtr &user, const double &value)
	{
		if (value < 0)
			throw exception("Negative value is not valid.Invalid Bid Value");
		return new Bid(user, value);
	}
};


