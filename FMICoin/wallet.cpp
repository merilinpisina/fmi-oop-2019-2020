#include "wallet.h"

Wallet::Wallet() : data(), fmiCoins(0) {}

// We use this constructor only when we first start the program - it loads data from wallets.dat
Wallet::Wallet(unsigned int id, const char * name, double fiatMoney) : data(id, name, fiatMoney), fmiCoins(fiatMoney / 375) 
{
	print();
}

Wallet::Wallet(double fiatMoney, const char *name) : data(name, fiatMoney), fmiCoins(fiatMoney / 375)
{
	saveRecord();
}

void Wallet::setMoney(const double fiatMoney)
{
	if (fiatMoney < 0) {
		throw("Value for fiatMoney should be a positive number!");
	}
	this->data.fiatMoney = fiatMoney;
}

void Wallet::setCoins(const double fmiCoins)
{
	this->fmiCoins = fmiCoins;
}

unsigned int Wallet::getID()const
{
	return this->data.id;
}

double Wallet::getCoins()const
{
	return fmiCoins;
}

double Wallet::getMoney()const
{
	return this->data.fiatMoney;
}

const char * Wallet::getOwner()const
{
	return data.owner;
}

void Wallet::saveRecord()const
{
	std::ofstream wallets;
	// File should be config.dat
	wallets.open("wallets.dat", std::ios::out | std::ios::binary | std::ios::app);
	if (!wallets) {
		throw("Could not open wallets.dat!");
	}
	else {
		wallets << getID() << " " << getOwner() << " " << getMoney() << std::endl;
		wallets.close();
	}
}

void Wallet::print() const
{
	std::cout << data.id << " " << data.owner << " " << data.fiatMoney << std::endl;
}

void Wallet::info() const
{
	std::cout << "Owner: " << data.owner << ", fiatMoney: " << data.fiatMoney << ", fmiCoins: " << fmiCoins << std::endl;
}
