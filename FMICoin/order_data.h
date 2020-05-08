#ifndef ORDER_DATA
#define ORDER_DATA

#include "order.h"

class OrderData
{
public:
	OrderData();
	OrderData(const OrderData&) = delete;
	OrderData& operator=(const OrderData&) = delete;
	~OrderData();

	void add_order(Order * newOrder);
	void add_order(const char * type, const unsigned int id, const double coins);

	Order** getData(const char* type)const;
	size_t getSize(const char* type)const;

	void update_orders();
	void update_sell();
	void update_buy();

private:
	Order** buyData;
	Order** sellData;
	size_t sizeBuy, capacityBuy;
	size_t sizeSell, capacitySell;

	void resize(const char* type);
	void destroy(const char* type);
};

#endif