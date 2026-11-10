#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using std::string;

namespace json {

	class TypeError : public std::runtime_error {
	public:
		TypeError(string const& message) : std::runtime_error(message) {
			
		}
	};
	

	class Data {
	protected:
		
	public:
		virtual ~Data();

		virtual bool isNull() const;
		virtual bool isBoolean() const;
		virtual bool isNumber() const;
		virtual bool isString() const;

		virtual bool& getBoolean();
		virtual bool const& getBoolean() const;
		virtual double& getNumber();
		virtual double const& getNumber() const;
		virtual string& getString();
		virtual string const& getString() const;
		
		virtual std::ostream& print(std::ostream& out) const = 0;
		virtual bool equals(Data const& data) const = 0;

		virtual std::unique_ptr<Data> clone() const = 0;
		virtual std::unique_ptr<Data> eject();

	};

}

inline std::ostream& operator<<(std::ostream& out, json::Data const& data) {
	data.print(out);
	return out;
}

inline bool operator==(json::Data const& left, json::Data const& right) {
	return left.equals(right);
}