#ifndef TRANSACTION_DATA
#define TRANSACTION_DATA

#include "transaction.h"

class TransactionData
{
public:
	TransactionData();
	TransactionData(const TransactionData&) = delete;
	TransactionData& operator=(const TransactionData&) = delete;
	~TransactionData();

	void add_transaction(Transaction* newTransaction);
	void add_transaction(unsigned int sender, unsigned int receiver, double coins);

	void print()const;

	size_t getSize()const;
	Transaction** getData();
	Transaction* getLast()const;

private:
	Transaction** data;
	size_t size, capacity;

	void resize();
	void destroy();
};

#endif