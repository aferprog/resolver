#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "MathElement.h"

namespace rslv {

	template<typename ResultType>
	class MathObject {
		std::vector<MathElement> elements;
		ResultType result;

	public:
		MathObject(ResultType initialValue);
		template<typename T>
		MathObject& operator+(const T& value);

		template<typename T>
		MathObject& operator-(const T& value);

		template<typename T>
		MathObject& operator*(const T& value);

		template<typename T>
		MathObject& operator/(const T& value);

		ResultType resolve();
	};

	template<typename ResultType>
	inline MathObject<ResultType>::MathObject(ResultType initialValue)
	{
		result = initialValue;
	}

	template<typename ResultType>
	inline ResultType MathObject<ResultType>::resolve() {
		for (const MathElement& el : elements) {
			switch (el.getOperation())
			{
			case Operations::ADD:
				result += el.getValue<ResultType, TYPES>();
				break;
			case Operations::SUBSTRUCT:
				result -= el.getValue<ResultType, TYPES>();
				break;
			case Operations::MULTIPLY:
				result *= el.getValue<ResultType, TYPES>();
				break;
			case Operations::DIVIDE:
				result /= el.getValue<ResultType, TYPES>();
				break;
			default:
				std::cerr << "Undefined operaton" << std::endl;
				break;
			}
		}
		return result;
	}

	template<typename ResultType>
	template<typename T>
	inline  MathObject<ResultType>& MathObject<ResultType>::operator+(const T& value) {
		elements.push_back({ value, Operations::ADD });
		return *this;
	}

	template<typename ResultType>
	template<typename T>
	inline  MathObject<ResultType>& MathObject<ResultType>::operator-(const T& value) {
		elements.push_back({ value, Operations::SUBSTRUCT });
		return *this;
	}

	template<typename ResultType>
	template<typename T>
	inline MathObject<ResultType>& MathObject<ResultType>::operator*(const T& value) {
		elements.push_back({ value, Operations::MULTIPLY });
		return *this;
	}

	template<typename ResultType>
	template<typename T>
	inline MathObject<ResultType>& MathObject<ResultType>::operator/(const T& value) {
		elements.push_back({ value, Operations::DIVIDE });
		return *this;
	}
}

