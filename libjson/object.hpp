#pragma once
#include "data.hpp"
#include "var.hpp"
#include <map>

namespace json {

	class Object : public Data {
		std::map<string, Var> _map;

		bool compareObject(Object const& data) const {
			return this->_map == data._map;
		}

	public:
		Object();
		Object(std::map<string, Var> const& data);
		Object(std::initializer_list<std::pair<std::string, Var>> data);

		bool isObject() const override;
		std::map<string, Var>& getObject();
		std::map<string, Var> const& getObject() const;
		std::vector<Var>& getArray();
		std::vector<Var> const& getArray() const;

		Var& operator[](string const& key);
		Var& at(string const& key);
		Var const& at(string const& key) const;

		std::unique_ptr<Data> clone() const override;
		std::unique_ptr<Data> eject() override;

		std::ostream& print(std::ostream& out) const override;

		bool equals(Data const& data) const override;
		bool operator==(Data const& data) const;
		bool operator!=(Data const& data) const;
	};
}

inline std::ostream& operator<<(std::ostream& out, json::Object object) {
	object.print(out);
	return out;
}

/*
inline bool operator==(json::Data const& data, json::Object const& object) {
	return object == data;
}

inline bool operator!=(json::Data const& data, json::Object const& object) {
	return !(object == data);
}
*/