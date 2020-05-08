#include "transaction_data.h"

TransactionData::TransactionData() : data(nullptr), size(0), capacity(128)
{
	data = new(std::nothrow) Transaction*[capacity];
	if (!data) {
		throw("Not enough memory!");
	}
	std::ifstream transactionData;
	
	transactionData.open("transactions.dat", std::ios::in | std::ios::binary);
	if (!transactionData) {
		throw("Could not open file transactions.dat!");
	}
	if (transactionData.tellg() == 0) {
		transactionData.close();
	}
	else {
		while (!transactionData.eof())
		{
			long long time;
			unsigned int sender;
			unsigned int receiver;
			double coins;
			transactionData >> time >> sender >> receiver >> coins;
			data[size++] = new(std::nothrow)Transaction(sender, receiver, coins, time);
			if (!data[size-1]) {
				throw("Not enough memory!");
			}
			if (size == capacity) {
				resize();
			}
		}
		transactionData.close();
	}
}


TransactionData::~TransactionData()
{
	destroy();
}

void TransactionData::add_transaction(Transaction* newTransaction)
{
	data[size++] = new(std::nothrow) Transaction(newTransaction->getSenderId(), newTransaction->getReceiverId(), newTransaction->getCoins());
	if (!data[size]) {
		throw("Not enough memory!");
	}
	if (size == capacity) {
		resize();
	}
}

void TransactionData::add_transaction(unsigned int sender, unsigned int receiver, double coins)
{
	data[size++] = new(std::nothrow)Transaction(sender, receiver, coins);
	if (!data[size-1]) {
		throw("Not enough memory!");
	}
	if (size == capacity) {
		resize();
	}
}

void TransactionData::print() const
{
	for (size_t i = 0; i < size; ++i) {
		std::cout << data[i]->getSenderId() << " " << data[i]->getReceiverId() << " " << data[i]->getCoins() << " " << data[i]->getTime() << std::endl;
	}
}

size_t TransactionData::getSize() const
{
	return size;
}

Transaction ** TransactionData::getData()
{
	return data;
}

Transaction * TransactionData::getLast() const
{
	return data[size-1];
}


void TransactionData::resize()
{
	capacity *= 2;
	Transaction** newData = new(std::nothrow)Transaction*[capacity];
	if (!newData) {
		throw("Not enough memory!");
	}
	for (size_t i = 0; i < size; ++i) {
		newData[i] = new(std::nothrow)Transaction(data[i]->getSenderId(), data[i]->getReceiverId(), data[i]->getCoins(), data[i]->getTime());
		if (!newData) {
			throw("Not enough memory!");
		}
		newData[i]->setAuthorized(data[i]->is_authorized());
	}
	destroy();
	data = newData;
}

void TransactionData::destroy()
{
	for (size_t i = 0; i < size; ++i) {
		delete data[i];
	}
	delete[] data;
	data = nullptr;
}
