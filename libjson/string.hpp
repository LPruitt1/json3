#pragma once
#include "data.hpp"
#include "var.hpp"

namespace json {

	class String : public Data {
		string _value;

	public:
		String();
		String(string const& value);
		String(char const* value);

		bool isString() const override;
		string& getString() override;
		string const& getString() const override;

		std::ostream& print(std::ostream& out) const override;
		bool equals(Data const& data) const override;

		std::unique_ptr<Data> clone() const override;
		std::unique_ptr<Data> eject() override;
	};
}