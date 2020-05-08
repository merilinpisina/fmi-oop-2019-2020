#include "transaction.h"

Transaction::Transaction():data(), isAuthorized(false){}

Transaction::Transaction(unsigned int senderId, unsigned int receiverId, double fmiCoins, long long time) :
	data(senderId, receiverId, fmiCoins, time), isAuthorized(false)
{
	if (time == 0) {
		saveRecord();
	}
	//std::cout << "saved" << std::endl;
}

Transaction::Transaction(const Transaction & other)
{
	data.fmiCoins = other.data.fmiCoins;
	data.receiverId = other.data.receiverId;
	data.senderId = other.data.senderId;
	data.time = other.data.time;
	isAuthorized = other.isAuthorized;
}

Transaction & Transaction::operator=(const Transaction & other)
{
	if (this != &other) {
		data.fmiCoins = other.data.fmiCoins;
		data.receiverId = other.data.receiverId;
		data.senderId = other.data.senderId;
		data.time = other.data.time;
		isAuthorized = other.isAuthorized;
	}
	return *this;
}

long long Transaction::getTime() const
{
	return data.time;
}

unsigned int Transaction::getSenderId() const
{
	return data.senderId;
}

unsigned int Transaction::getReceiverId() const
{
	return data.receiverId;
}

double Transaction::getCoins() const
{
	return data.fmiCoins;
}

bool Transaction::is_authorized() const
{
	return isAuthorized;
}

void Transaction::setAuthorized(bool is_authorized)
{
	isAuthorized = is_authorized;
}

void Transaction::saveRecord() const
{
	std::ofstream transaction;
	// File should be config.dat
	transaction.open("transactions.dat", std::ios::out | std::ios::binary | std::ios::app);
	if (!transaction) {
		std::cout << "Not opened\n";
		//handle it
	}
	else {
		transaction << getTime() << " " << getSenderId() << " " << getReceiverId() << " " << getCoins() << std::endl;
		transaction.close();
	}
}
