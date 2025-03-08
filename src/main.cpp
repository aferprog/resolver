#include "Resolver.h"
#include <iostream>

int main() {
	auto mo = rslv::m0() + 10 - 5.5 - 1;
	std::cout << mo.resolve() << std::endl;
}
