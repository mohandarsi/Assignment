#pragma once
#include "Auction.h"
class DutchAuction : public virtual Auction, public virtual IDutchAuction
{
public:
	DutchAuction(double bidInitialPrice);
	DEFAULT_DESTRUCTOR(DutchAuction)

	virtual void UpdatePrice(const double &newAmount);
private:
	double m_initialPrice = 0;
protected:
	virtual void InternalPlaceBid(IBid::IBidPtr bid);
};





