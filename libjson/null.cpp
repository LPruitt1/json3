#include "null.hpp"

json::Null::Null() {
	_value = nullptr;
}

json::Null::Null(std::nullptr_t const& value) {
	_value = nullptr;
}

bool json::Null::isNull() const {
	return true;
}

std::map<string, json::Var>& json::Null::getObject() {
	throw json::TypeError("Wrong data type!");
}

std::map<string, json::Var> const& json::Null::getObject() const {
	throw json::TypeError("Wrong data type!");
}

std::vector<json::Var>& json::Null::getArray() {
	throw json::TypeError("Wrong data type!");
}

std::vector<json::Var> const& json::Null::getArray() const {
	throw json::TypeError("Wrong data type!");
}

std::ostream& json::Null::print(std::ostream& out) const {
	out << "null";
	return out;
}

bool json::Null::equals(Data const& data) const {
	if (data.isNull()) return true;
	else return false;
}

std::unique_ptr<json::Data> json::Null::clone() const {
	std::unique_ptr<Data> pointer = std::make_unique<Null>(nullptr);
	return pointer;
}