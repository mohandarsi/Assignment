// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AuctionSystem.h"
#include "User.h"
#include<assert.h>
#include<chrono>
int main()
{

	//auction system
	unique_ptr<IAuctionSystem> auctionSystem(new AuctionSystem());
	
	//creating english auction
	auto englishAuction = auctionSystem->Create(AuctionType::English);
	IUser::IUserPtr user1(User::Create("User1", "user1"));
	IUser::IUserPtr  user2(User::Create("User2", "user2"));


	//placing bid on english
	englishAuction->PlaceBid(user1, 100);
	englishAuction->PlaceBid(user2, 200);

	//Querying winning bid
	assert(englishAuction->GetWinningBid()->GetValue() == 200);
	
	//Query all bids on the auction
	list<IBid::IBidPtr> englishbidLists = englishAuction->GetAllBids();
	assert(englishbidLists.size() == 2); //shall be 2 bids

										 
	//creating dutch auction
	auto dutchAuction = auctionSystem->Create(AuctionType::Dutch);
	auto dauction = dynamic_cast<IDutchAuction*>(dutchAuction.get());
	dauction->UpdatePrice(1000);

	//placing bid on dutch
	dutchAuction->PlaceBid(user2, 100);
	//Querying winning bid
	assert(dutchAuction->GetWinningBid()->GetValue() == 1000);


	//registering users
	auctionSystem->RegisterUser(user1);
	auctionSystem->RegisterUser(user2);

	//Blind Auction
	auto blindAuction = auctionSystem->Create(AuctionType::Blind);
	
	//placing bid on Blind
	blindAuction->PlaceBid(user1, 100);

	//Querying for auction users
   auto auctionlist =auctionSystem->GetAuctionsofUser(user1);
   assert(auctionlist.size() == 2); //user1 auctioned for  dutch and english

   //closing auctions
   auctionSystem->Close(englishAuction);

   auctionlist = auctionSystem->GetAuctionsofUser(user1);
   assert(auctionlist.size() == 1); //as english auction closed

    return 0;
}

