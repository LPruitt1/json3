#pragma once
#include "data.hpp"

namespace json {

	class Number : public Data {
		double _value;

	public:
		Number();
		Number(double value);

		bool isNumber() const override;
		double& getNumber() override;
		double const& getNumber() const override;

		std::ostream& print(std::ostream& out) const override;
		bool equals(Data const& data) const override;

		std::unique_ptr<Data> clone() const override;

	};
}