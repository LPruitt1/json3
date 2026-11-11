#pragma once
#include "data.hpp"
#include "var.hpp"

namespace json {

	class Null : public Data {
		std::nullptr_t _value;

	public:
		Null();
		Null(std::nullptr_t const& value);

		bool isNull() const override;

		std::vector<Var>& getArray();
		std::vector<Var> const& getArray() const;
		std::map<string, Var>& getObject();
		std::map<string, Var> const& getObject() const;

		std::ostream& print(std::ostream& out) const override;
		bool equals(Data const& data) const override;

		std::unique_ptr<Data> clone() const override;
		
	};
}