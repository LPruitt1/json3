#include "data.hpp"
#include <iostream>
#include <memory>
#include <string>

json::Data::~Data() {
	// do something
}

bool json::Data::isNull() const {
	return false;
}

bool json::Data::isBoolean() const {
	return false;
}

bool json::Data::isNumber() const {
	return false;
}

bool json::Data::isString() const {
	return false;
}

bool json::Data::isArray() const {
	return false;
}

bool json::Data::isObject() const {
	return false;
}

bool& json::Data::getBoolean() {
	throw json::TypeError("Wrong data type!");
}

double& json::Data::getNumber() {
	throw json::TypeError("Wrong data type!");
}

std::string& json::Data::getString() {
	throw json::TypeError("Wrong data type!");
}

bool const& json::Data::getBoolean() const {
	throw json::TypeError("Wrong data type!");
}

double const& json::Data::getNumber() const {
	throw json::TypeError("Wrong data type!");
}

std::string const& json::Data::getString() const {
	throw json::TypeError("Wrong data type!");
}

std::vector<json::Var>& json::Data::getArray() {
	throw json::TypeError("Wrong data type!");
}

std::vector<json::Var> const& json::Data::getArray() const {
	throw json::TypeError("Wrong data type!");
}

std::map<string, json::Var>& json::Data::getObject() {
	throw json::TypeError("Wrong data type!");
}

std::map<string, json::Var> const& json::Data::getObject() const {
	throw json::TypeError("Wrong data type!");
}

std::unique_ptr<json::Data> json::Data::eject() {
	return this->clone();
}