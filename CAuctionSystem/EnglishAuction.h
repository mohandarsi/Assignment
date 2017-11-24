#pragma once
#include "Auction.h"

class EnglishAuction :public Auction
{
public:
	EnglishAuction();
	DEFAULT_DESTRUCTOR(EnglishAuction)
protected:
	virtual void InternalPlaceBid(IBid::IBidPtr bid);
};

