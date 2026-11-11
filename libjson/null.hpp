#pragma once
#include "data.hpp"

namespace json {

	class Null : public Data {
		std::nullptr_t _value;

	public:
		Null();
		Null(std::nullptr_t const& value);

		bool isNull() const override;

		std::ostream& print(std::ostream& out) const override;
		bool equals(Data const& data) const override;

		std::unique_ptr<Data> clone() const override;
		
	};
}