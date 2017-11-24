#pragma once
#include "Interfaces.h"

using namespace std;

class Auction : public virtual IAuction
{
public:

	virtual void PlaceBid(const IUser::IUserPtr &user, const double &value) override;
	
	virtual void Close() override;

	virtual const list<IBid::IBidPtr> GetAllBids() override
	{
		return *m_bids;
	}

	virtual const IBid::IBidPtr GetWinningBid() override
	{
		return m_winningBid;
	}

	Auction();
	virtual ~Auction();

protected:
	list<IBid::IBidPtr> *m_bids;
	bool m_isClosed = false;
	IBid::IBidPtr m_winningBid = nullptr;
	virtual void InternalPlaceBid(IBid::IBidPtr bid) = 0;
};


