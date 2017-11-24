#include "stdafx.h"
#include "DutchAuction.h"

/// <summary>
/// 
/// </summary>
/// <param name="bidInitialPrice">Bid initial price</param>
DutchAuction::DutchAuction(double bidInitialPrice):
	m_initialPrice(bidInitialPrice)
{
}


void DutchAuction::InternalPlaceBid(IBid::IBidPtr bidIn)
{
	// for dutch always bid is the current price
	bidIn->SetValue(m_initialPrice);

	m_winningBid = bidIn;

	m_bids->push_back(m_winningBid);

	//close the bid after placing the bid
	Close();
}

void DutchAuction::UpdatePrice(const double &newAmount)
{
	// update shall be allowed only if auction is open
	if (m_isClosed)
	{
		throw exception("Update is not allowed on closed auction's");
	}

	//Price can be only lowered
	if (newAmount >= m_initialPrice)
		throw exception("Bid ammount only allowed to decrease and not allowed to increment");

	m_initialPrice = newAmount;
}