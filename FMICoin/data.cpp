#include "data.h"

Data::Data() {
	load_transactions();
}

Data::~Data(){}

void Data::load_transactions()
{
	Transaction** transactionData = transactions.getData();
	for (size_t i = 0; i < transactions.getSize(); ++i) {
		Wallet* sender = wallets.findByID(transactionData[i]->getSenderId());
		Wallet* receiver = wallets.findByID(transactionData[i]->getReceiverId());

		if (transactionData[i]->getSenderId() == system_id) {
			receiver->setCoins(receiver->getCoins() + transactionData[i]->getCoins());
			continue;
		}
		if (sender == nullptr) {
			continue;
		}

		if (sender != nullptr && receiver != nullptr) {
			if (sender->getCoins() >= transactionData[i]->getCoins()) {
				sender->setCoins(sender->getCoins() - transactionData[i]->getCoins());
				receiver->setCoins(receiver->getCoins() + transactionData[i]->getCoins());
			}
		}
	}
}

void Data::add_wallet(Wallet * newWallet)
{
	wallets.add_wallet(newWallet);
}

void Data::add_wallet(const char * name, double fiatMoney)
{
	const unsigned int newId = wallets.add_wallet(name, fiatMoney);
	transactions.add_transaction(system_id, newId, fiatMoney / 375);
}

void Data::add_transaction(Transaction* newTransaction)
{
	transactions.add_transaction(newTransaction);
}

void Data::add_transaction(unsigned int senderId, unsigned int receiverId, double fmiCoins)
{
	transactions.add_transaction(senderId, receiverId, fmiCoins);

	Transaction* transaction = transactions.getLast();
	Wallet* sender = wallets.findByID(transaction->getSenderId());
	Wallet* receiver = wallets.findByID(transaction->getReceiverId());

	if (transaction->getSenderId() == system_id) {
		return;
	}
	if (sender == nullptr || receiver == nullptr) {
		throw("Enter valid IDs for sender and receiver!");
		return;
	}
	if (sender != nullptr && receiver != nullptr) {
		if (sender->getCoins() >= transaction->getCoins()) {
			sender->setCoins(sender->getCoins() - transaction->getCoins());
			receiver->setCoins(receiver->getCoins() + transaction->getCoins());
		}
		else {
			throw("Not enough money in sender's wallet!");
		}
	}
}

void Data::add_order(const char * type, const unsigned int id, const double coins)
{
	if (wallets.findByID(id) == nullptr) {
		throw("Not a valid ID");
	}
	orders.add_order(type, id, coins);
	double neededCoins = coins;
	Order** buyData = orders.getData("BUY"), **sellData = orders.getData("SELL");
	size_t sizeBuy = orders.getSize("BUY"), sizeSell = orders.getSize("SELL");

	if (strcmp(type, "SELL") == 0) {
		for (size_t i = 0; i < sizeBuy; ++i) {
			if (buyData[i]->isComplete()) {
				continue;
			}
			if (wallets.findByID(buyData[i]->getId()) == nullptr) {
				buyData[i]->complete();
				continue;
			}
			if (wallets.findByID(buyData[i]->getId())->getMoney() < buyData[i]->getCoins() * 375) {
				continue;
			}
			if (neededCoins <= buyData[i]->getCoins()) {
				Wallet* seller = wallets.findByID(id);
				seller->setMoney(seller->getMoney() + neededCoins * 375);
				Wallet* buyer = wallets.findByID(buyData[i]->getId());
				buyer->setMoney(buyer->getMoney() - neededCoins * 375);

				buyData[i]->complete();
				sellData[sizeSell - 1]->complete();
				add_transaction(id, buyData[i]->getId(), neededCoins);
				neededCoins -= buyData[i]->getCoins();
				if (neededCoins < 0) {
					add_order("BUY", buyData[i]->getId(), abs(neededCoins));
				}
				break;
			}
			else {
				Wallet* seller = wallets.findByID(id);
				seller->setMoney(seller->getMoney() + buyData[i]->getCoins() * 375);
				Wallet* buyer = wallets.findByID(buyData[i]->getId());
				buyer->setMoney(buyer->getMoney() - buyData[i]->getCoins() * 375);

				buyData[i]->complete();
				neededCoins -= buyData[i]->getCoins();
				add_transaction(id, buyData[i]->getId(), buyData[i]->getCoins());
			}
		}
	}
	else {
		for (size_t i = 0; i < sizeSell; ++i) {
			if (sellData[i]->isComplete()) {
				continue;
			}
			if (wallets.findByID(sellData[i]->getId()) == nullptr) {
				sellData[i]->complete();
				continue;
			}
			if (wallets.findByID(sellData[i]->getId())->getCoins() < sellData[i]->getCoins()) {
				std::cout << "Not enough coins\n";
				continue;
			}
			if (neededCoins <= sellData[i]->getCoins()) {
				Wallet* seller = wallets.findByID(sellData[i]->getId());
				seller->setMoney(seller->getMoney() + neededCoins * 375);
				Wallet* buyer = wallets.findByID(id);
				buyer->setMoney(buyer->getMoney() - neededCoins * 375);

				sellData[i]->complete();
				buyData[sizeBuy - 1]->complete();
				add_transaction(sellData[i]->getId(), id, neededCoins);
				neededCoins -= sellData[i]->getCoins();
				if (neededCoins < 0) {
					add_order("SELL", sellData[i]->getId(), abs(neededCoins));
				}
				break;
			}
			else {
				Wallet* seller = wallets.findByID(sellData[i]->getId());
				seller->setMoney(seller->getMoney() + sellData[i]->getCoins() * 375);
				Wallet* buyer = wallets.findByID(id);
				buyer->setMoney(buyer->getMoney() - sellData[i]->getCoins() * 375);

				sellData[i]->complete();
				neededCoins -= sellData[i]->getCoins();
				add_transaction(sellData[i]->getId(), id, sellData[i]->getCoins());
			}
		}
	}
	if (sizeSell + sizeBuy >= 100) {
		orders.update_orders();
	}
}

void Data::wallet_info(const unsigned int ID) const
{
	if (!wallets.findByID(ID)) {
		throw("No instance of wallet with this ID.");
	}
	else {
		wallets.findByID(ID)->info();
	}
}

void Data::print() const
{
	transactions.print();
}

//void Data::executeTransactions()
//{
//	for (size_t i = 0; i < transactions.getSize(); ++i) {
//		Wallet* sender = wallets.findByID(transactions.data[i]->getSenderId());
//		Wallet* receiver = wallets.findByID(transactions.data[i]->getReceiverId());
//		if (sender != nullptr && receiver != nullptr) {
//			if (sender->getCoins() >= transactions.data[i]->getCoins()) {
//				sender->setCoins(sender->getCoins() - transactions.data[i]->getCoins());
//				receiver->setCoins(receiver->getCoins() + transactions.data[i]->getCoins());
//			}
//		}
//	}
//}
