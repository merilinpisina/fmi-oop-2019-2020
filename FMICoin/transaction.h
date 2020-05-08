#ifndef TRANSACTION
#define TRANSACTION

#include "id.h"
#include <ctime>

class Transaction
{
public:
	explicit Transaction();
	explicit Transaction(unsigned int senderId, unsigned int receiverId, double fmiCoins, long long time = 0);
	Transaction(const Transaction& other);
	Transaction& operator=(const Transaction& other);
	~Transaction() = default;

	long long getTime() const;
	unsigned int getSenderId() const;
	unsigned int getReceiverId() const;
	double getCoins() const;
	bool is_authorized()const;

	void setAuthorized(bool is_authorized);
	void saveRecord() const;

private:
	struct transaction {
		long long time;
		unsigned int senderId;
		unsigned int receiverId;
		double fmiCoins;

		transaction() :senderId(0), receiverId(0), fmiCoins(0), time(0) {}

		transaction(unsigned int sender, unsigned int receiver, double coins, long long t = 0) :
			senderId(sender), receiverId(receiver), fmiCoins(coins), time(t)
		{
			if (time == 0) {
				time_t tt;
				tt = std::time(NULL);
				time = long long(tt);
			}
		}
	} data;
	bool isAuthorized;
};



#endif