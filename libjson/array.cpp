#include "array.hpp"

json::Array::Array() {
	_array = {};
}

json::Array::Array(std::vector<Var> const& data) {
	_array = data;
}

json::Array::Array(std::initializer_list<Var> data) {
	_array = data;
}

bool json::Array::isArray() const {
	return true;
}

std::vector<json::Var>& json::Array::getArray() {
	return _array;
}

std::vector<json::Var> const& json::Array::getArray() const {
	return _array;
}

json::Var& json::Array::operator[](int i) {
	return _array[i];
}

json::Var const& json::Array::operator[](int i) const {
	return _array[i];
}

json::Var& json::Array::at(int i) {
	/*
	if (_array.size() > i) {
		return _array[i];
	}
	else {
		throw std::out_of_range("Out of range!");
	}
	*/

	return _array.at(i);
}

json::Var const& json::Array::at(int i) const {
	/*
	if (_array.size() > i) {
		return _array[i];
	}
	else {
		throw std::out_of_range("Out of range!");
	}
	*/

	return _array.at(i);
}

std::map<string, json::Var>& json::Array::getObject() {
	throw json::TypeError("Wrong data type!");
}

std::map<string, json::Var> const& json::Array::getObject() const {
	throw json::TypeError("Wrong data type!");
}

std::unique_ptr<json::Data> json::Array::clone() const {
	std::unique_ptr<Array> pointer = std::make_unique<Array>(*this);
	return pointer;
}

std::unique_ptr<json::Data> json::Array::eject() {
	std::unique_ptr<Array> pointer = std::make_unique<Array>(std::move(*this));
	return pointer;
}

std::ostream& json::Array::print(std::ostream& out) const {
	for (Var const& thing : _array) {
		thing->print(out);
	}
	return out;
}

bool json::Array::equals(Data const& data) const {
	if (data.isArray()) {
		return this->compareArray((Array&)data);
	}
	else {
		return false;
	}
}

bool json::Array::operator==(Data const& data) const {
	return this->equals(data);
}

bool json::Array::operator!=(Data const& data) const {
	return !(this->equals(data));
}