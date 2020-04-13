#include "OnlineStore.h"

std::ostream & operator<<(std::ostream &out, const OnlineStore &store)
{
	out << "Number of items in store: " << store.size << std::endl;

	for (int i = 0; i < store.size; ++i) {
		out << store.items[i] << std::endl;
	}
	return out;
}
