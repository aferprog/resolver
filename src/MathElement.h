#pragma once
#include <any>

#define TYPES int, float, char, double, size_t, unsigned int

namespace rslv {
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
		void setValue(const T& newValue) {
			address = &newValue;
			value = newValue;
		}
	public:
		void setOperation(Operations newOperation) {
			operation = newOperation;
		}

		Operations getOperation() const {
			return operation;
		}

		template<typename T>
		MathElement(const T& newValue, Operations newOperation) {
			setValue(newValue);
			operation = newOperation;
		}

		template<typename ValueType, typename TypeOfAny, typename... OtherTypesOfAny>
		ValueType getValue() const {
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
		/*template<typename T>
		void operator=(const T& newValue) {
			setValue(newValue);
		}*/
	};
}