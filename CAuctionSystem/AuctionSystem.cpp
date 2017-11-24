#include "stdafx.h"
#include<algorithm>
#include "AuctionSystem.h"
#include "EnglishAuction.h"
#include "DutchAuction.h"
#include "BlindAuction.h"

AuctionSystem::AuctionSystem()
{
}
AuctionSystem::~AuctionSystem()
{
	if (m_userList != nullptr)
	{
		m_userList->clear();
		delete m_userList;
	}
	if (m_auctionList != nullptr)
	{
		m_auctionList->clear();
		delete m_auctionList;
	}
	m_userList = nullptr;
	m_auctionList = nullptr;
}

void AuctionSystem::Close(IAuction::IAuctionPtr auction)
{
	auction->Close();
	//remove the auction form list
	if (m_auctionList != nullptr)
	   m_auctionList->remove(auction);
}

void AuctionSystem::RegisterUser(IUser::IUserPtr user)
{
	auto result =
		std::find(m_userList->begin(), m_userList->end(), user);

	// Only registered users can participate in bid
	if (result == std::end(*m_userList))
	{
		m_userList->push_back(user);
	}
	else
	{
		//user is already registered
	}
}
list<IAuction::IAuctionPtr> AuctionSystem::GetAuctionsofUser(IUser::IUserPtr user) const
{
	list<IAuction::IAuctionPtr> findLists;
	for (auto it = m_auctionList->begin(); it != m_auctionList->end(); ++it)
	{
		auto iter = (*it)->GetAllBids();
		for (auto it1 = iter.begin(); it1 != iter.end(); ++it1)
		{
			if ((*it1)->GetUser() == user)
				findLists.push_back(*it);
		}
	}

	return findLists;
}

/// <summary>
/// factory method to create auction based on the type
/// </summary>
/// <param name="type"></param>
/// <returns></returns>
IAuction::IAuctionPtr AuctionSystem::Create(AuctionType type)
{
	Auction* auction;
	switch (type)
	{
	case AuctionType::English:
		auction = new EnglishAuction();
		break;
	case AuctionType::Dutch:
		auction = new DutchAuction(INT_MAX);
		break;
	case AuctionType::Blind:
		auction = new BlindAuction(*m_userList);
		break;
	default:
		throw std::logic_error("Auction is invalid or not implemented");
	}
	IAuction::IAuctionPtr ptr(auction);
	m_auctionList->push_back(ptr);
	return ptr;
}