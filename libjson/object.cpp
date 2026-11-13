#include "object.hpp"
#include "jsonmanip.hpp"

json::Object::Object() {
	_map = {};
}

json::Object::Object(std::map<string, Var> const& data) {
	_map = data;
}

json::Object::Object(std::initializer_list<std::pair<std::string, Var>> data) {
	for (std::pair<string, Var> const& element : data) {
		_map.insert(element);
	}
}

bool json::Object::isObject() const {
	return true;
}

std::map<string, json::Var>& json::Object::getObject() {
	return _map;
}

std::map<string, json::Var> const& json::Object::getObject() const {
	return _map;
}

json::Var& json::Object::operator[](string const& key) {
	return _map[key];
}

json::Var& json::Object::at(string const& key) {
	return _map.at(key);
}

json::Var const& json::Object::at(string const& key) const {
	return _map.at(key);
}

std::unique_ptr<json::Data> json::Object::clone() const {
	std::unique_ptr<Object> pointer = std::make_unique<Object>(*this);
	return pointer;
}

std::unique_ptr<json::Data> json::Object::eject() {
	std::unique_ptr<Object> pointer = std::make_unique<Object>(std::move(*this));
	return pointer;
}

std::ostream& json::Object::print(std::ostream& out) const {
	
	out << '{';

	for (auto const& _pair : _map) {
		if (_pair != *(begin(_map))) {
			out << ',';
		}
		out << json::json_string(_pair.first) << ":";
		_pair.second->print(out);
	}

	out << '}';

	return out;
}

bool json::Object::equals(Data const& data) const {
	if (data.isObject()) {
		return this->compareObject((Object&)data);
	}
	else {
		return false;
	}
}

bool json::Object::operator==(Data const& data) const {
	return this->equals(data);
}

bool json::Object::operator!=(Data const& data) const {
	return !(this->equals(data));
}