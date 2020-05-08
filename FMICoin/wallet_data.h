#ifndef WALLET_DATA
#define WALLET_DATA

#include "wallet.h"

class WalletData {
public:
	// Loads all data from wallets.dat
	WalletData();
	WalletData(const WalletData &) = delete;
	WalletData &operator=(const WalletData &) = delete;
	~WalletData();

	Wallet* findByID(const unsigned int ID)const;

	virtual void add_wallet(Wallet * newWallet);
	const unsigned int add_wallet(const char * name, double fiatMoney);

	void save_data();
	void update_data();

	void print()const;

protected:
	unsigned int size, capacity;
	Wallet** data;

	void resize();
	void destroy();
	//void readAndLoad(char *fileName);
};

#endif