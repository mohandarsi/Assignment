#include "stdafx.h"
#include "Auction.h"
#include "Bid.h"
#include<exception>

Auction::Auction():m_bids(new list<IBid::IBidPtr>())
{
}

Auction::~Auction()
{
	if (m_bids != nullptr)
	{
		m_bids->clear();
		delete m_bids;
	}
	m_bids = nullptr;
}

void Auction::PlaceBid(const IUser::IUserPtr &user, const double &value)
{
	if (m_isClosed)
	{
		throw exception("Bid is not allowed on closed auction's");
	}
	IBid::IBidPtr ptr(Bid::Create(user, value));
	InternalPlaceBid(ptr);
}

void Auction::Close()
{
	m_isClosed = true;
	//clear all bids as auction is closed
	if (m_bids != nullptr)
	{
		m_bids->clear();
	}
}
