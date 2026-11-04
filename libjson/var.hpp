#pragma once
#include "json.hpp"
#include <typeinfo>
#include <type_traits>

namespace json {
	
	class Var {
		std::unique_ptr<Data> _ptr;

	public:
		Var(); // default construct
		Var(std::unique_ptr<Data> data); // value construct
		Var(Data const& data); // value construct (copy)
		Var(Data&& data); // value construct (move)

		Var(bool const& data); // next few lines are all convert value via overloading constructor
		Var(std::nullptr_t const& data);
		Var(double const& data);
		Var(std::string const& data);
		Var(char const* data);

		
		/*template<typename T> requires std::is_arithmetic_v<T>
		Var::Var(T src) : Var((double)src) {
		}*/
		

		// These might need to be all four const at the end and two consts as part of the return type instead of
		// what it currently is, which is two const at the end and zero consts as part of the return type
		Data& operator*();
		Data const& operator*() const;
		Data* operator->();
		Data const* operator->() const;

		Var(Var const& other); // copy constructor
		Var& operator=(Var const& other); // copy assignment
		Var(Var&& other); // move constructor
		Var& operator=(Var&& other); // move assignment

		Var& operator=(Data const& other); // copy data assignment
		Var& operator=(Data&& other); // move data assignment

		bool operator==(Var const& other) const;
		bool operator!=(Var const& other) const;
	};


}

inline std::ostream& operator<<(std::ostream& out, json::Var const& v) {
	v->print(out);
	return out;
}