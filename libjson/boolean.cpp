#include "boolean.hpp"

json::Boolean::Boolean() {
	_value = false;
}

json::Boolean::Boolean(bool value) {
	_value = value;
}

bool json::Boolean::isBoolean() const {
	return true;
}

bool& json::Boolean::getBoolean() {
	return _value;
}

bool const& json::Boolean::getBoolean() const {
	return _value;
}

std::vector<json::Var>& json::Boolean::getArray() {
	throw json::TypeError("Wrong data type!");
}

std::vector<json::Var> const& json::Boolean::getArray() const {
	throw json::TypeError("Wrong data type!");
}

std::map<string, json::Var>& json::Boolean::getObject() {
	throw json::TypeError("Wrong data type!");
}

std::map<string, json::Var> const& json::Boolean::getObject() const {
	throw json::TypeError("Wrong data type!");
}

std::ostream& json::Boolean::print(std::ostream& out) const {
	if (_value) {
		out << "true";
	}
	else {
		out << "false";
	}

	return out;
}

bool json::Boolean::equals(Data const& data) const {
	if (data.isBoolean()) {
		if (_value == data.getBoolean()) {
			return true;
		}
		else {
			return false;
		}
	}
}

std::unique_ptr<json::Data> json::Boolean::clone() const {
	std::unique_ptr<Data> pointer = std::make_unique<Boolean>(*this);
	return pointer;
}