#pragma once
#include "data.hpp"
#include "var.hpp"

namespace json {

	class Boolean : public Data {
		bool _value;

	public:
		Boolean();
		Boolean(bool value);

		bool isBoolean() const override;
		bool& getBoolean() override;
		bool const& getBoolean() const override;

		std::vector<Var>& getArray();
		std::vector<Var> const& getArray() const;
		std::map<string, Var>& getObject();
		std::map<string, Var> const& getObject() const;

		std::ostream& print(std::ostream& out) const override;
		bool equals(Data const& data) const override;

		std::unique_ptr<Data> clone() const override;
	};
}