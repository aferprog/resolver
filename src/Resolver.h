#pragma once
#include "MathObject.h"

namespace rslv {

	inline MathObject<double> m0() {
		return MathObject<double>{0.};
	}

	inline MathObject<double> m1() {
		return MathObject<double>{1.};
	}

	template<typename ResultType>
	inline MathObject<ResultType> m(ResultType InitialValue) {
		return MathObject<ResultType>{InitialValue};
	}
}