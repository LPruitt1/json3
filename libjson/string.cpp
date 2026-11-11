#include "string.hpp"
#include "jsonmanip.hpp"

json::String::String() {
	_value = "";
}

json::String::String(string const& value) {
	_value = value;
}

json::String::String(char const* value) {
	_value = value;
}

bool json::String::isString() const {
	return true;
}

string& json::String::getString() {
	return _value;
}

string const& json::String::getString() const {
	return _value;
}

std::ostream& json::String::print(std::ostream& out) const {
	out << json::json_string(_value);
	return out;
}

bool json::String::equals(Data const& data) const {
	if (data.isString()) {
		if (_value == data.getString()) return true;
		else return false;
	}
}

std::unique_ptr<json::Data> json::String::clone() const {
	std::unique_ptr<Data> pointer = std::make_unique<String>(*this);
	return pointer;
}

std::unique_ptr<json::Data> json::String::eject() {
	std::unique_ptr<Data> pointer = std::make_unique<String>(std::move(*this));
	_value.clear();
	return pointer;
}