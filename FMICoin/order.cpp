#include "order.h"

Order::Order() : data(), isCompleted(false) {}

Order::Order(const char * type, const unsigned int id, const double coins):
	data(type, id, coins), isCompleted(false)
{
	saveRecord();
}

Order::Order(OrderType type, const unsigned int id, const double coins):
	data(type, id, coins), isCompleted(false)
{
	saveRecord();
}

Order::~Order(){}

void Order::complete()
{
	isCompleted = true;
}

OrderType Order::getType() const
{
	return data.type;
}

const unsigned int Order::getId() const
{
	return data.walletId;
}

const double Order::getCoins() const
{
	return data.fmiCoins;
}

bool Order::isComplete() const
{
	return isCompleted;
}

void Order::saveRecord() const
{
	std::ofstream orders;
	orders.open("orders.dat", std::ios::out | std::ios::binary | std::ios::app);
	if (!orders) {
		std::cout << "Not opened\n";
		//handle it
	}
	else {
		const char* type = (getType() == SELL ? "SELL" : "BUY");
		orders << type << " " << getId() << " " << getCoins() << std::endl;
		std::cout << type << " " << getId() << " " << getCoins() << std::endl;
		orders.close();
	}
}
