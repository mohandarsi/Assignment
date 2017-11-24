#include "stdafx.h"
#include "BlindAuction.h"
#include<algorithm>

BlindAuction::BlindAuction(const list<IUser::IUserPtr>& usersList):
	m_registeredUsers(usersList)
{
}


/// <summary>
/// Only registered users can participate in bid
/// </summary>
/// <param name="bidIn"></param>
void BlindAuction::InternalPlaceBid(IBid::IBidPtr bidIn)
{

	auto found = std::find_if(m_registeredUsers.begin(), m_registeredUsers.end(), [bidIn](IUser::IUserPtr user) {
		return user == bidIn->GetUser();
	});
	// Only registered users can participate in bid
	if (found == std::end(m_registeredUsers))
	{
		throw  exception("User is not registered");
	}

	auto result1 =
		std::find_if(m_bids->begin(), m_bids->end(), 
			[bidIn](IBid::IBidPtr bidPtr) { return bidPtr->GetUser() == bidIn->GetUser(); });

	//User can make only one bid
	if (result1 != m_bids->end())
	{
		throw exception("Bid is not allowed multiple times on same user");
	}
		
	m_bids->push_back(bidIn);

	// winning bid logic
	if (m_winningBid == nullptr || m_winningBid->GetValue() < bidIn->GetValue())
	{
		m_winningBid = bidIn;
	}

	//close the bid if all participants/users made bid
	if (m_bids->size() == m_registeredUsers.size())
	{
		Close();
	}

}
