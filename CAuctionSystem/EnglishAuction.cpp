#include "stdafx.h"
#include "EnglishAuction.h"


EnglishAuction::EnglishAuction()
{
}

void EnglishAuction::InternalPlaceBid(IBid::IBidPtr bidIn)
{

	//Bid is accepted inly if the new bid ammount is greater than current bid

	if (m_winningBid != nullptr && m_winningBid->GetValue() >= bidIn->GetValue())
	{
		throw exception("Placed Bid amount is less than current Winning bid ammount");
	}
	m_winningBid = bidIn;

	m_bids->push_back(m_winningBid);

}
