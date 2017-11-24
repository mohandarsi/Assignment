#pragma once
#include "Interfaces.h"


/// <summary>
/// Interface to Auction system
/// </summary>
class AuctionSystem : public IAuctionSystem
{
public:
	/// <summary>
	/// shall able to create auction
	/// </summary>
	/// <param name="type">type of the auction</param>
	/// <returns></returns>
	IAuction::IAuctionPtr Create(AuctionType type);

	/// <summary>
	/// shall able to close the auction
	/// </summary>
	/// <param name="auction">auction which needs to be close</param>
	void Close(IAuction::IAuctionPtr auction);

	/// <summary>
	/// Registering the user 
	/// </summary>
	/// <param name="user">user infromation</param>
	void RegisterUser(IUser::IUserPtr user);

	/// <summary>
	/// Shall able to Query auctions in which participant has participated
	/// </summary>
	/// <param name="user"></param>
	/// <returns></returns>
	list<IAuction::IAuctionPtr> GetAuctionsofUser(IUser::IUserPtr user) const;


	AuctionSystem();
	~AuctionSystem();

private:
	/// <summary>
	/// mainintanins list of users
	/// </summary>
	list<IUser::IUserPtr> *m_userList = new list<IUser::IUserPtr>();

	/// <summary>
	/// maintains list of auctions
	/// </summary>
	list<IAuction::IAuctionPtr> *m_auctionList = new list<IAuction::IAuctionPtr>();
};

