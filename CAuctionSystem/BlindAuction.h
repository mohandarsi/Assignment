#pragma once
#include "Auction.h"
#include "User.h"
class BlindAuction :public Auction
{
public:
	BlindAuction(const list<IUser::IUserPtr>& usersList);
	DEFAULT_DESTRUCTOR(BlindAuction)
protected:
	virtual void InternalPlaceBid(IBid::IBidPtr bid);
private:
	const list<User::IUserPtr>& m_registeredUsers;
};

