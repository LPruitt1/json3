#pragma once
#include "data.hpp"
#include "var.hpp"
#include <stdexcept>
#include <vector>

namespace json {

	class Array : public Data {
		std::vector<json::Var> _array;

		bool compareArray(Array const& data) const {
			return this->_array == data._array;
		}

	public:
		Array();
		Array(std::vector<Var> const& data);
		Array(std::initializer_list<Var> data);

		bool isArray() const override;
		std::vector<Var>& getArray() override;
		std::vector<Var> const& getArray() const override;

		Var& operator[](int i);
		Var const& operator[](int i) const;
		Var& at(int i);
		Var const& at(int i) const;

		std::unique_ptr<Data> clone() const override;
		std::unique_ptr<Data> eject() override;

		std::ostream& print(std::ostream& out) const override;

		bool equals(Data const& data) const override;
		bool operator==(Data const& data) const;
		bool operator!=(Data const& data) const;
		
	};
}

inline std::ostream& operator<<(std::ostream& out, json::Array array) {
	array.print(out);
	return out;
}

/*
inline bool operator==(json::Data const& data, json::Array const& array) {
	return array == data;
}

inline bool operator!=(json::Data const& data, json::Array const& array) {
	return !(array == data);
}
*/