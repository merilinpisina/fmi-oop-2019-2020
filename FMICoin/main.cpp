#include "data.h"

int main() {
	data::initialize();
	Data d;

	char command[32];
	do {
		std::cout << "Enter a command: ";
		std::cin >> command;
		if (strcmp(command, "wallet-info") == 0) {
			unsigned int id;
			std::cout << "Enter walletID: ";
			std::cin >> id;
			try {
				d.wallet_info(id);
			}
			catch (const char* tex) {
				std::cout << tex << std::endl;
			}
			continue;
		}
		if (strcmp(command, "transfer") == 0) {
			unsigned int sender, receiver;
			double coins;
			std::cout << "senderID: ";
			std::cin >> sender;
			std::cout << "receiverID: ";
			std::cin >> receiver;
			std::cout << "fmiCoins: ";
			std::cin >> coins;
			try {
				d.add_transaction(sender, receiver, coins);
			}
			catch (const char* tex) {
				std::cout << tex << std::endl;
				continue;
			}
			std::cout << "Transfer: " << sender << " -> " << receiver << " completed!\n";
			continue;
		}
		if (strcmp(command, "add-wallet") == 0) {
			char owner[32];
			double fiatMoney;
			std::cout << "Owner: ";
			std::cin >> owner;
			std::cout << "Fiat money: ";
			std::cin >> fiatMoney;
			try {
				d.add_wallet(owner, fiatMoney);
			}
			catch (const char* tex) {
				std::cout << tex << std::endl;
				continue;
			}
			continue;
		}
		if (strcmp(command, "make-order") == 0) {
			char type[4];
			unsigned int walletId;
			double coins;
			std::cout << "Type of order (SELL/BUY): ";
			std::cin >> type;
			std::cout << "Wallet ID: ";
			std::cin >> walletId;
			std::cout << "FMI coin: ";
			std::cin >> coins;
			try {
				d.add_order(type, walletId, coins);
			}
			catch (const char* tex) {
				std::cout << tex << std::endl;
			}
			continue;
		}
	} while (strcmp(command, "quit") != 0);

	system("pause");
	return 0;
}