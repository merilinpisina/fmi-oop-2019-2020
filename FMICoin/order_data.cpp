#include "order_data.h"

OrderData::OrderData() : 
	sellData(nullptr), sizeSell(0), capacitySell(128), 
	buyData(nullptr), sizeBuy(0), capacityBuy(128)
{
	sellData = new(std::nothrow) Order*[capacitySell];
	if (!sellData) {
		throw("Not enough memory!");
	}
	buyData = new(std::nothrow) Order*[capacityBuy];
	if (!buyData) {
		throw("Not enough memory!");
	}

	std::ifstream orderData;
	orderData.open("orders.dat", std::ios::in | std::ios::binary);
	if (!orderData) {
		throw("Could not open orders.dat!");
	}
	else {
		if (orderData.tellg() == 0) {
			orderData.close();
		}
		else {
			while (!orderData.eof())
			{
				char type[4];
				unsigned int walletId;
				double coins;
				orderData >> type >> walletId >> coins;
				if (strcmp(type, "SELL") == 0) {
					sellData[sizeSell++] = new(std::nothrow) Order(type, walletId, coins);
					if (!sellData[sizeSell - 1]) {
						throw("Not enough memory!");						
					}
					if (sizeSell == capacitySell) {
						resize("SELL");
					}
				}
				else {
					buyData[sizeBuy++] = new(std::nothrow) Order(type, walletId, coins);
					if (!buyData[sizeBuy - 1]) {
						throw("Not enough memory!");
					}
					if (sizeBuy == capacityBuy) {
						resize("BUY");
					}
				}
			}
			orderData.close();
		}
	}
}


OrderData::~OrderData()
{
	destroy("BUY");
	destroy("SELL");
}

void OrderData::add_order(Order * newOrder)
{
	if (newOrder->getType() == SELL) {
		sellData[sizeSell++] = new(std::nothrow) Order(newOrder->getType(), newOrder->getId(), newOrder->getCoins());
		if (!sellData[sizeSell - 1]) {
			throw("Not enough memory!");
		}
		if (sizeSell == capacitySell) {
			resize("SELL");
		}
	}
	else {
		buyData[sizeBuy++] = new(std::nothrow) Order(newOrder->getType(), newOrder->getId(), newOrder->getCoins());
		if (!buyData[sizeBuy - 1]) {
			throw("Not enough memory!");
		}
		if (sizeBuy == capacityBuy) {
			resize("BUY");
		}
	}
}

void OrderData::add_order(const char * type, const unsigned int id, const double coins)
{
	if (strcmp(type, "SELL") == 0) {
		sellData[sizeSell++] = new(std::nothrow) Order(type, id, coins);
		if (!sellData[sizeSell - 1]) {
			throw("Not enough memory!");
		}
		if (sizeSell == capacitySell) {
			resize("SELL");
		}
	}
	else {
		buyData[sizeBuy++] = new(std::nothrow) Order(type, id, coins);
		if (!buyData[sizeBuy - 1]) {
			throw("Not enough memory!");
		}
		if (sizeBuy == capacityBuy) {
			resize("BUY");
		}
	}
}

Order ** OrderData::getData(const char * type) const
{
	return (strcmp(type, "SELL") == 0 ? sellData : buyData);
}

size_t OrderData::getSize(const char * type) const
{
	return (strcmp(type, "SELL") == 0 ? sizeSell : sizeBuy);
}

void OrderData::update_orders()
{
	update_sell();
	update_buy();
	std::ofstream newOrders;
	newOrders.open("orders.dat", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!newOrders) {
		throw("Could not open orders.dat!");
	}
	else {
		for (size_t i = 0; i < sizeSell; ++i) {
			if (sellData[i]->isComplete()) {
				continue;
			}
			const char* type = "SELL";
			newOrders << type << " " << sellData[i]->getId() << " " << sellData[i]->getCoins() << std::endl;
		}
		for (size_t i = 0; i < sizeBuy; ++i) {
			if (buyData[i]->isComplete()) {
				continue;
			}
			const char* type = "BUY";
			newOrders << type << " " << buyData[i]->getId() << " " << buyData[i]->getCoins() << std::endl;
		}
		newOrders.close();
	}
}

void OrderData::update_sell()
{
	Order** orders = new(std::nothrow) Order*[capacitySell];
	size_t newSize = 0;
	for (size_t i = 0; i < sizeSell; ++i) {
		if (sellData[i]->isComplete()) {
			continue;
		}
		orders[newSize++] = new(std::nothrow) Order(sellData[i]->getType(), sellData[i]->getId(), sellData[i]->getCoins());
		if (!orders[newSize - 1]) {
			throw("Not enough memory!");
		}
	}
	destroy("SELL");
	sizeSell = newSize;
	sellData = orders;
}

void OrderData::update_buy()
{
	Order** orders = new(std::nothrow) Order*[capacityBuy];
	size_t newSize = 0;
	for (size_t i = 0; i < sizeBuy; ++i) {
		if (buyData[i]->isComplete()) {
			continue;
		}
		orders[newSize++] = new(std::nothrow) Order(buyData[i]->getType(), buyData[i]->getId(), buyData[i]->getCoins());
		if (!orders[newSize - 1]) {
			throw("Not enough memory!");
		}
	}
	destroy("BUY");
	sizeBuy = newSize;
	buyData = orders;
}

void OrderData::resize(const char* type)
{
	if (strcmp(type, "SELL") == 0) {
		capacitySell *= 2;
		Order** newData = new(std::nothrow)Order*[capacitySell];
		if (!newData) {
			throw("Not enough memory!");
		}
		for (size_t i = 0; i < sizeSell; ++i) {
			newData[i] = new(std::nothrow)Order("SELL", sellData[i]->getId(), sellData[i]->getCoins());
			if (!newData) {
				throw("Not enough memory!");
			}
		}
		destroy("SELL");
		sellData = newData;
	}
	else {
		capacityBuy *= 2;
		Order** newData = new(std::nothrow)Order*[capacityBuy];
		if (!newData) {
			throw("Not enough memory!");
		}
		for (size_t i = 0; i < sizeBuy; ++i) {
			newData[i] = new(std::nothrow)Order("BUY", buyData[i]->getId(), buyData[i]->getCoins());
			if (!newData) {
				throw("Not enough memory!");
			}
		}
		destroy("BUY");
		buyData = newData;

	}
}

void OrderData::destroy(const char * type)
{
	if (strcmp(type, "SELL") == 0) {
		for (size_t i = 0; i < sizeSell; ++i) {
			delete sellData[i];
		}
		delete[] sellData;
		sellData = nullptr;
	}
	else {
		for (size_t i = 0; i < sizeBuy; ++i) {
			delete buyData[i];
		}
		delete[] buyData;
		buyData = nullptr;
	}
}
