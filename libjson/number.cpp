#include "number.hpp"
#include "jsonmanip.hpp"

json::Number::Number() {
	_value = 0.0;
}

json::Number::Number(double value) {
	_value = value;
}

bool json::Number::isNumber() const {
	return true;
}

double& json::Number::getNumber() {
	return _value;
}

double const& json::Number::getNumber() const {
	return _value;
}

std::ostream& json::Number::print(std::ostream& out) const {
	out << json::json_number(_value);
	return out;
}

bool json::Number::equals(Data const& data) const {
	if (data.isNumber()) {
		if (_value == data.getNumber()) {
			return true;
		}
		else {
			return false;
		}
	}
}

std::unique_ptr<json::Data> json::Number::clone() const {
	std::unique_ptr<Data> pointer = std::make_unique<Number>(*this);
	return pointer;
}