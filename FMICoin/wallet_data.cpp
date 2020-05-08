#include "wallet_data.h"

WalletData::WalletData() : data(nullptr), size(0), capacity(128)
{
	data = new(std::nothrow) Wallet*[capacity];
	if (!data) {
		throw("Not enough memory!");
	}
	std::ifstream walletData;

	walletData.open("wallets.dat", std::ios::in | std::ios::binary);
	if (!walletData) {
		throw("Could not open wallets.dat!");
	}
	if (walletData.tellg() == 0) {
		walletData.close();
	}
	else {
		while (!walletData.eof())
		{
			char owner[256];
			unsigned int id;
			unsigned int money;
			walletData >> id >> owner >> money;
			data[size++] = new(std::nothrow)Wallet(id, owner, money);
			if (!data[size-1]) {
				throw("Not enough memory!");
			}
			if (size == capacity) {
				resize();
			}
		}
		walletData.close();
	}
}

WalletData::~WalletData()
{
	destroy();
}

Wallet* WalletData::findByID(const unsigned int ID)const
{
	if (ID == system_id) {
		return nullptr;
	}
	for (size_t i = 0; i < size; ++i) {
		//std::cout << data[i]->getID() << " " << ID << std::endl;
		if (data[i]->getID() == ID) {
			return data[i];
		}
	}
	return nullptr;
}

void WalletData::add_wallet(Wallet * newWallet)
{
	data[size++] = new(std::nothrow)Wallet;
	if (!data[size - 1]) {
		throw("Not enough memory!");
	}
	data[size-1] = newWallet;
	if (size == capacity) {
		resize();
	}
}

const unsigned int WalletData::add_wallet(const char * name, double fiatMoney)
{
	data[size++] = new(std::nothrow) Wallet(fiatMoney, name);
	if (!data[size - 1]) {
		throw("Not enough memory!");
	}
	if (size == capacity) {
		resize();
	}
	return data[size - 1]->getID();
}

void WalletData::save_data()
{
	std::ofstream wallets;
	wallets.open("wallets.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!wallets) {
		throw("Could not open wallets.dat!");
	}
	else {
		for (size_t i = 0; i < size; ++i) {
			wallets << data[i]->getID() << " " << data[i]->getOwner() << " " << data[i]->getMoney() << std::endl;
		}
		wallets.close();
	}
}

void WalletData::update_data()
{
	std::ofstream wallets;
	wallets.open("wallets.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!wallets) {
		throw("Could not open wallets.dat!");
	}
	else {
		for (size_t i = 0; i < size; ++i) {
			wallets << data[i]->getID() << " " << data[i]->getOwner() << " " << data[i]->getMoney() << std::endl;
		}
		wallets.close();
	}
}

void WalletData::print() const
{
	for (size_t i = 0; i < size; ++i) {
		std::cout << data[i] << std::endl;
	}
}

void WalletData::resize()
{
	capacity *= 2;
	Wallet** newData = new(std::nothrow)Wallet*[capacity];
	if (!newData) {
		throw("Not enough memory!");
	}
	for (size_t i = 0; i < size; ++i) {
		newData[i] = new(std::nothrow)Wallet(data[i]->getID(), data[i]->getOwner(), data[i]->getMoney());
		if (!newData) {
			throw("Not enough memory!");
		}
		newData[i]->setCoins(data[i]->getCoins());
	}
	destroy();
	data = newData;
}

void WalletData::destroy()
{
	for (size_t i = 0; i < size; ++i) {
		delete data[i];
	}
	delete[] data;
	data = nullptr;
}
