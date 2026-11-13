#include "json.hpp"
#include "var.hpp"

json::Var::Var() {
	_ptr = std::make_unique<Null>(nullptr);
}

json::Var::Var(std::unique_ptr<Data> data) {
	_ptr = data->clone();
}

json::Var::Var(Data const& data) {
	_ptr = data.clone();
}

json::Var::Var(Data&& data) {
	_ptr = data.eject();
}

/*
json::Var::Var(Boolean const& data) {
	_ptr = std::make_unique<Boolean>(data);
}

json::Var::Var(Null const& data) {
	_ptr = std::make_unique<Null>(data);
}

json::Var::Var(Number const& data) {
	_ptr = std::make_unique<Number>(data);
}

json::Var::Var(String const& data) {
	_ptr = std::make_unique<String>(data);
}
*/

json::Var::Var(bool const& data) {
	_ptr = std::make_unique<Boolean>(data);
}

json::Var::Var(std::nullptr_t const& data) {
	_ptr = std::make_unique<Null>(data);
}

json::Var::Var(double value) {
	_ptr = std::make_unique<Number>(value);
}

json::Var::Var(std::string const& data) {
	_ptr = std::make_unique<String>(data);
}

json::Var::Var(char const* data) {
	_ptr = std::make_unique<String>(data);
}

json::Var::Var(std::vector<json::Var> const& data) {
	_ptr = std::make_unique<Array>(data);
}

json::Var::Var(std::map<string, json::Var> const& data) {
	_ptr = std::make_unique<Object>(data);
}

json::Data& json::Var::operator*() {
	return *_ptr;
}

json::Data const& json::Var::operator*() const {
	return *_ptr;
}

json::Data* json::Var::operator->() {
	return _ptr.get();
}

json::Data const* json::Var::operator->() const {
	return _ptr.get();
}

json::Var::Var(Var const& other) {
	_ptr = (other._ptr)->clone();
}

json::Var& json::Var::operator=(Var const& other) {
	if (this != &other) {
		_ptr = (other._ptr)->clone();
	}
	return *this;
}

json::Var::Var(Var&& other) {
	if (this != &other) {
		_ptr = other._ptr->clone();
		other._ptr = std::make_unique<json::Null>();
	}
}

json::Var& json::Var::operator=(Var&& other) {
	if (this != &other) {
		_ptr = other._ptr->clone();
		other._ptr = std::make_unique<json::Null>();
	}
	return *this;
}

json::Var& json::Var::operator=(Data const& other) {
	_ptr = other.clone();
	return *this;
}

json::Var& json::Var::operator=(Data&& other) {
	_ptr = other.eject();
	return *this;
}

bool json::Var::operator==(Var const& other) const {
	if (typeid(*this) == typeid(other)) {
		if (other->isBoolean()) {
			if ((*this)->getBoolean() == other->getBoolean()) return true;
			else return false;
		}
		else if (other->isNull()) {
			return true;
		}
		else if (other->isNumber()) {
			if ((*this)->getNumber() == other->getNumber()) return true;
			else return false;
		}
		else if (other->isString()) {
			if ((*this)->getString() == other->getString()) return true;
			else return false;
		}
	}
	else return false;
}

bool json::Var::operator!=(Var const& other) const {
	return !(*this == other);
}

bool json::Var::operator==(Data const& other) const {
	if (typeid(*_ptr) == typeid(other)) {
		if (other.isBoolean()) {
			if (_ptr->getBoolean() == other.getBoolean()) return true;
			else return false;
		}
		else if (other.isNull()) return true;
		else if (other.isNumber()) {
			if (_ptr->getNumber() == other.getNumber()) return true;
			else return false;
		}
		else if (other.isString()) {
			if (_ptr->getString() == other.getString()) return true;
			else return false;
		}
	}
	else return false;
}

bool json::Var::operator!=(Data const& other) const {
	return !(*this == other);
}