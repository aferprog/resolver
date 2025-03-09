#pragma once
#include "MathObject.h"

namespace rslv {
	const MathObject<double> d0{ 0. };
	const MathObject<double> d1{ 1. };

	template<typename ResultType>
	inline MathObject<ResultType> m(ResultType InitialValue) {
		return MathObject<ResultType>{InitialValue};
	}
}