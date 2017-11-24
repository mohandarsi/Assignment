#pragma once

#include<memory>
#include<list>

using namespace std;

# define PURE	=0 //for pure virtual functions
# define interface	struct //c,c++ does n't have keyword for interface
#define DEFAULT_DESTRUCTOR(type) virtual ~##type##() = default;

/// <summary>
/// Allowed auction types are English , Dutch and Blind
/// </summary>
enum AuctionType
{
	English, Dutch, Blind
};


interface IUser
{
	typedef shared_ptr<IUser> IUserPtr;

	virtual string GetUserName() PURE;
	virtual string GetUserId() PURE;

	DEFAULT_DESTRUCTOR(IUser)
};

interface IBid
{
	typedef shared_ptr<IBid> IBidPtr;

	typedef std::pair<list<IBidPtr>::const_iterator, list<IBidPtr>::const_iterator>
		IBidEnumerator;

	virtual const IUser::IUserPtr GetUser() PURE;
	virtual double GetValue() const PURE;
	virtual void SetValue(const double &value) PURE;

	DEFAULT_DESTRUCTOR(IBid)
};

/// <summary>
/// Interface to Auction 
/// </summary>
interface IAuction
{
	typedef shared_ptr<IAuction> IAuctionPtr;

	virtual void PlaceBid(const IUser::IUserPtr &user, const double &value) PURE;

	virtual void Close() PURE;

	virtual const list<IBid::IBidPtr> GetAllBids() PURE;

	virtual const IBid::IBidPtr GetWinningBid() PURE;

	DEFAULT_DESTRUCTOR(IAuction)
};

interface IDutchAuction : public virtual IAuction
{
	virtual void UpdatePrice(const double &newAmount) PURE;

	DEFAULT_DESTRUCTOR(IDutchAuction)
};

/// <summary>
/// Interface to Auction system
/// </summary>
interface IAuctionSystem
{
	/// <summary>
	/// shall able to create auction
	/// </summary>
	/// <param name="type">type of the auction</param>
	/// <returns></returns>
	virtual IAuction::IAuctionPtr Create(AuctionType type) PURE;

	/// <summary>
	/// shall able to close the auction
	/// </summary>
	/// <param name="auction">auction which needs to be close</param>
	virtual void Close(IAuction::IAuctionPtr auction) PURE;

	/// <summary>
	/// Registering the user 
	/// </summary>
	/// <param name="user">user infromation</param>
	virtual void RegisterUser(IUser::IUserPtr user) PURE;

	/// <summary>
	/// Shall able to Query auctions in which participant has participated
	/// </summary>
	/// <param name="user"></param>
	/// <returns></returns>
	virtual list<IAuction::IAuctionPtr> GetAuctionsofUser(IUser::IUserPtr user) const PURE ;

	DEFAULT_DESTRUCTOR(IAuctionSystem)
};
