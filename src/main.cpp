#include "Resolver.h"
#include <iostream>

int main() {
	rslv::MathObject<double> mo = std::move(rslv::d0 + 3 + 3)-(rslv::d0+3+1);
	std::cout << mo.resolve() << std::endl;
}
