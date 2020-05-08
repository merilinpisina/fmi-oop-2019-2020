#ifndef ORDER_H
#define ORDER_H

#include <string.h>
#include <memory>
#include "id.h"

enum OrderType { SELL, BUY };

class Order
{
public:
	Order();
	explicit Order(const char* type, const unsigned int id, const double coins);
	explicit Order(OrderType type, const unsigned int id, const double coins);
	~Order();

	void complete();

	OrderType getType()const;
	const unsigned int getId()const;
	const double getCoins()const;
	bool isComplete()const;

	void saveRecord() const;

private:
	struct order {
		OrderType type;
		unsigned int walletId;
		double fmiCoins;

		order(): walletId(system_id), fmiCoins(0) {}

		order(OrderType t, const unsigned int id, const double coins) :
			walletId(id), fmiCoins(coins), type(t) {}

		order(const char* t, const unsigned int id, const double coins) :
			walletId(id), fmiCoins(coins) {
			if (strcmp(t, "SELL") == 0) {
				type = SELL;
			}
			else {
				type = BUY;
			}
		}
	} data;
	bool isCompleted;
};

#endif