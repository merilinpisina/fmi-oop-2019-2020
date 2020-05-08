#ifndef WALLETS
#define WALLETS

#include <string.h>
#include "id.h"

class Wallet
{
public:
	Wallet();
	Wallet(unsigned int id, const char*name, double fiatMoney);
	explicit Wallet(double fiatMoney, const char* name);
	Wallet(const Wallet &) = delete;
	Wallet &operator=(const Wallet &) = delete;
	~Wallet() = default;

	void setMoney(const double fiatMoney);
	void setCoins(const double fmiCoins);

	//const?
	unsigned int getID()const;
	double getCoins()const;
	double getMoney()const;
	const char* getOwner()const;

	void saveRecord()const;

	void print() const;

	void info()const;

private:
	struct wallet
	{
		unsigned int id;
		char owner[256];
		double fiatMoney;

		wallet() {
			id = system_id;
			strcpy_s(owner, "");
			fiatMoney = 0;
		}

		wallet(const char *name, double money)
		{
			id = data::getAndIncrease();
			strcpy_s(owner, name);
			fiatMoney = money;
		}

		wallet(unsigned int id, const char *name, double money)
		{
			this->id = id;
			strcpy_s(owner, name);
			fiatMoney = money;
		}

	} data;
	double fmiCoins;
	int numberOfOrders;
};

#endif