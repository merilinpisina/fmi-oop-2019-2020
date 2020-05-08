#ifndef DATA_H
#define DATA_H

#include "wallet_data.h"
#include "transaction_data.h"
#include "order_data.h"

class Data{
public:
	Data();
	Data(const Data&) = delete;
	Data& operator=(const Data&) = delete;
	~Data();

	void load_transactions();

	void add_wallet(Wallet * newWallet);
	void add_wallet(const char * name, double fiatMoney);
	void add_transaction(Transaction* newTransaction);
	void add_transaction(unsigned int senderId, unsigned int receiverId, double fmiCoins);
	//void add_order(Order * newOrder);
	void add_order(const char * type, const unsigned int id, const double coins);

	void wallet_info(const unsigned int ID) const;

	void print()const;

private:
	WalletData wallets;
	TransactionData transactions;
	OrderData orders;
};


#endif