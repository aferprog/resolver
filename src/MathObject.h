#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "IResolvable.h"
#include "MathElement.h"

namespace rslv {

	template<typename ResultType>
	class MathObject: public IResolvable<ResultType> {
		std::vector<MathElement> elements;
		ResultType result;

	public:
		MathObject(ResultType initialValue);
		MathObject(const MathObject<ResultType>& other);
		MathObject(MathObject<ResultType>&& other);

		template<typename T>
		MathObject& operator+(const T& value);

		template<typename T>
		MathObject& operator-(const T& value);

		template<typename T>
		MathObject& operator*(const T& value);

		template<typename T>
		MathObject& operator/(const T& value);

		template<typename T>
		MathObject operator+(const T& value) const;

		template<typename T>
		MathObject operator-(const T& value) const;

		template<typename T>
		MathObject operator*(const T& value) const;

		template<typename T>
		MathObject operator/(const T& value) const;

		ResultType resolve() override;
	};

	template<typename ResultType>
	inline MathObject<ResultType>::MathObject(ResultType initialValue)
	{
		result = initialValue;
	}

	template<typename ResultType>
	inline MathObject<ResultType>::MathObject(const MathObject<ResultType>& other)
		: result(other.result), elements(other.elements)
	{
	}

	template<typename ResultType>
	inline MathObject<ResultType>::MathObject(MathObject<ResultType>&& other)
	{
		result = other.result;
		elements = std::move(other.elements);
	}

	template<typename ResultType>
	inline ResultType MathObject<ResultType>::resolve() {
		for (MathElement& el : elements) {
			ResultType value;
			if (MathObject<ResultType>* el_mo = el.getAsMathObject<ResultType>(); el_mo != nullptr)
				value = el_mo->resolve();
			else
				value = el.getValue<ResultType, TYPES>();

			switch (el.getOperation())
			{
			case Operations::ADD:
				result += value;
				break;
			case Operations::SUBSTRUCT:
				result -= value;
				break;
			case Operations::MULTIPLY:
				result *= value;
				break;
			case Operations::DIVIDE:
				result /= value;
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
	template<typename ResultType>
	template<typename T>
	inline MathObject<ResultType> MathObject<ResultType>::operator+(const T& value) const
	{
		return MathObject<ResultType>(*this) + value;
	}
	template<typename ResultType>
	template<typename T>
	inline MathObject<ResultType> MathObject<ResultType>::operator-(const T& value) const
	{
		return MathObject<ResultType>(*this) - value;
	}
	template<typename ResultType>
	template<typename T>
	inline MathObject<ResultType> MathObject<ResultType>::operator*(const T& value) const
	{
		return MathObject<ResultType>(*this) * value;
	}
	template<typename ResultType>
	template<typename T>
	inline MathObject<typename ResultType> MathObject<ResultType>::operator/(const T& value) const
	{
		return MathObject<ResultType>(*this) / value;
	}
}

