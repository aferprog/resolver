#pragma once
#include <any>
#include <iostream>
#include "IResolvable.h"

#define TYPES int, float, char, double, size_t, unsigned int



namespace rslv {

	template <typename T>
	class MathObject;

	enum class Operations
	{
		ADD,
		SUBSTRUCT,
		DIVIDE,
		MULTIPLY
	};

	class MathElement {
		std::any value;
		const void* address;
		Operations operation;

		template<typename T>
		void setValue(const T& newValue);
	public:
		template<typename MathObjectResultType>
		bool isMathObject() const;

		void setOperation(Operations newOperation);
		Operations getOperation() const;

		template<class T>
		MathElement(const T& newValue, Operations newOperation);

		template<typename ValueType, typename TypeOfAny, typename... OtherTypesOfAny>
		ValueType getValue();

		template<typename MathObjectResultType>
		MathObject<MathObjectResultType>* getAsMathObject();
	};

	template<typename T>
	inline void MathElement::setValue(const T& newValue) {
		address = &newValue;
		value = newValue;
	}

	template<typename T>
	inline MathElement::MathElement(const T& newValue, Operations newOperation) {
		setValue(newValue);
		operation = newOperation;
	}

	template<typename ValueType, typename TypeOfAny, typename ...OtherTypesOfAny>
	inline ValueType MathElement::getValue() {
		if (value.type() == typeid(TypeOfAny)) {
			TypeOfAny t = std::any_cast<TypeOfAny>(value);
			return t;
		}

		if constexpr (sizeof...(OtherTypesOfAny) > 0) {
			getValue<ValueType, OtherTypesOfAny...>();
		}
		else {
			std::cerr << "Not determined type of std::any value. Try to update #define TYPES. Undefined type name: " << value.type().name() << std::endl;
			return ValueType{};
		}
	}

	template<typename MathObjectResultType>
	inline MathObject<MathObjectResultType>* MathElement::getAsMathObject()
	{
		return std::any_cast<MathObject<MathObjectResultType>>(&value);
	}

	template<typename MathObjectResultType>
	inline bool MathElement::isMathObject() const
	{
		return value.type() == typeid(MathObject<MathObjectResultType>);
	}

	inline void rslv::MathElement::setOperation(Operations newOperation) {
		operation = newOperation;
	}

	inline Operations MathElement::getOperation() const {
		return operation;
	}

}