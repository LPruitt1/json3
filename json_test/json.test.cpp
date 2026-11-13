#pragma once
#include "json.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>


// Part 1: The Scalar Types (Boolean, Null, Number, String)

TEST(DefaultConstruct, Boolean) {
	json::Boolean b;
	ASSERT_EQ(b.getBoolean(), false);
}

TEST(DefaultConstruct, Null) {
	json::Null n;
}

TEST(DefaultConstruct, Number) {
	json::Number n;
	ASSERT_EQ(n.getNumber(), 0);
}

TEST(DefaultConstruct, String) {
	json::String s;
	ASSERT_EQ(s.getString(), "");
}

TEST(ValueConstruct, Boolean) {
	json::Boolean bee = true;
	ASSERT_EQ(bee.getBoolean(), true);
}

TEST(ValueConstruct, Null) {
	json::Null inn = nullptr;
}

TEST(ValueConstruct, Number) {
	json::Number inn = 35.3;
	ASSERT_EQ(inn.getNumber(), 35.3);
}

TEST(ValueConstruct, String) {
	json::String ess = "yeehaw";
	ASSERT_EQ(ess.getString(), "yeehaw");
}

TEST(ValueConstruct, ConstChar) {
	char const* see = "woohoo";
	json::String ess = see;
	ASSERT_EQ(ess.getString(), "woohoo");
}

TEST(TypeIdentifiers, IsBooleanTrue) {
	json::Boolean b = true;
	ASSERT_EQ(true, b.isBoolean());
}

TEST(TypeIdentifiers, IsNullTrue) {
	json::Null n;
	ASSERT_EQ(true, n.isNull());
}

TEST(TypeIdentifiers, IsNumberTrue) {
	json::Number n;
	ASSERT_EQ(true, n.isNumber());
}

TEST(TypeIdentifiers, IsStringTrue) {
	json::String s = "yeah";
	ASSERT_EQ(true, s.isString());
}

TEST(TypeIdentifiers, IsBooleanFalse) {
	json::Null n;
	ASSERT_FALSE(n.isBoolean());
}

TEST(TypeIdentifiers, IsNullFalse) {
	json::Number n;
	ASSERT_FALSE(n.isNull());
}

TEST(TypeIdentifiers, IsNumberFalse) {
	json::String s;
	ASSERT_FALSE(s.isNumber());
}

TEST(TypeIdentifiers, IsStringFalse) {
	json::Boolean b;
	ASSERT_FALSE(b.isString());
}

TEST(GetValue, BooleanSuccess) {
	json::Boolean b = false;
	json::Boolean c = true;
	ASSERT_EQ(false, b.getBoolean());
	ASSERT_EQ(true, c.getBoolean());
}

TEST(GetValue, NumberSuccess) {
	json::Number n = 8;
	json::Number o = 99.3;
	ASSERT_EQ(8.0, n.getNumber());
	ASSERT_EQ(99.3, o.getNumber());
}

TEST(GetValue, StringSuccess) {
	json::String s = "ess";
	json::String t = "tee";
	ASSERT_EQ("ess", s.getString());
	ASSERT_EQ("tee", t.getString());
}

TEST(GetValue, BooleanError) {
	json::Boolean b;
	ASSERT_ANY_THROW(b.getNumber());
}

TEST(GetValue, NumberError) {
	json::Number n;
	ASSERT_ANY_THROW(n.getString());
}

TEST(GetValue, StringError) {
	json::String s;
	ASSERT_ANY_THROW(s.getBoolean());
}

TEST(SetValue, Boolean) {
	json::Boolean b;
	b.getBoolean() = true;
	ASSERT_EQ(true, b.getBoolean());
}

TEST(SetValue, Number) {
	json::Number n;
	n.getNumber() = 33.4;
	ASSERT_EQ(33.4, n.getNumber());
}

TEST(SetValue, String) {
	json::String s;
	s.getString() = "howdy";
	ASSERT_EQ("howdy", s.getString());
}

TEST(Print, Boolean) {
	json::Boolean b;
	std::ostringstream out;
	out << b;
	ASSERT_EQ(out.str(), "false");
}

TEST(Print, Null) {
	json::Null null;
	std::ostringstream out;
	out << null;
	ASSERT_EQ(out.str(), "null");
}

TEST(Print, Number) {
	json::Number num = 3.14;
	std::ostringstream out;
	out << num;
	ASSERT_EQ(out.str(), "3.14");
}

TEST(Print, String) {
	json::String s = "s";
	std::ostringstream out;
	out << s;
	ASSERT_EQ(out.str(), "\"s\"");
}

TEST(Equals, BooleanComp) {
	json::Boolean a = true;
	json::Boolean b = false;
	json::Boolean c = true;
	ASSERT_FALSE(a == b);
	ASSERT_FALSE(b == c);
	ASSERT_TRUE(a == c);
}

TEST(Equals, NullComp) {
	json::Null a, b;
	ASSERT_TRUE(a == b);
}

TEST(Equals, NumberComp) {
	json::Number a = 3.14;
	json::Number b = 5.166;
	json::Number c = 3.14;
	ASSERT_FALSE(a == b);
	ASSERT_FALSE(b == c);
	ASSERT_TRUE(a == c);
}

TEST(Equals, StringComp) {
	json::String a = "Hello!";
	json::String b = "Howdy!";
	json::String c = "Hello!";
	ASSERT_FALSE(a == b);
	ASSERT_FALSE(b == c);
	ASSERT_TRUE(a == c);
}

TEST(Clone, Boolean) {
	json::Boolean b = true;
	auto c = b.clone();
	ASSERT_TRUE(*c == b);
}

TEST(Clone, Null) {
	json::Null n;
	auto o = n.clone();
	ASSERT_TRUE(*o == n);
}

TEST(Clone, Number) {
	json::Number p;
	auto q = p.clone();
	ASSERT_TRUE(*q == p);
}

TEST(Clone, String) {
	json::String s = "Howdy!!";
	auto t = s.clone();
	ASSERT_TRUE(*t == s);
}

TEST(Eject, Boolean) {
	json::Boolean b = true;
	auto c = b.eject();
	ASSERT_TRUE(*c == b);
}

TEST(Eject, Null) {
	json::Null n;
	auto o = n.eject();
	ASSERT_TRUE(*o == n);
}

TEST(Eject, Number) {
	json::Number p;
	auto q = p.eject();
	ASSERT_TRUE(*q == p);
}

TEST(Eject, String) {
	json::String s = "Hello!";
	auto q = s.eject();
	ASSERT_TRUE(q->getString() == "Hello!");
	ASSERT_TRUE(s.getString() == "");
}


// Part 2: The Container (Var)

TEST(VarConstruct, DefaultConstruct) {
	json::Var v;
	ASSERT_TRUE(v->isNull());
}

TEST(VarConstruct, ValueConstructBool) {
	json::Var v{ std::make_unique<json::Boolean>(true) };
	json::Var w{ std::make_unique<json::Boolean>()};
	ASSERT_TRUE(v->isBoolean());
	ASSERT_TRUE(w->isBoolean());
	ASSERT_TRUE(v->getBoolean());
	ASSERT_FALSE(w->getBoolean());
}

TEST(VarConstruct, ValueConstructNull) {
	json::Var v{ std::make_unique<json::Null>() };
	ASSERT_TRUE(v->isNull());
}

TEST(VarConstruct, ValueConstructNumber) {
	json::Var v{ std::make_unique<json::Number>(3.0) };
	ASSERT_TRUE(v->isNumber());
	ASSERT_EQ(v->getNumber(), 3.0);
}

TEST(VarConstruct, ValueConstructString) {
	json::Var v{ std::make_unique<json::String>("Hi Theta!") };
	ASSERT_TRUE(v->isString());
	ASSERT_FALSE(v->isNumber());
	ASSERT_EQ(v->getString(), "Hi Theta!");
}

TEST(VarDereference, StarOp) {
	json::Var v{ std::make_unique<json::Number>(3.0) };
	ASSERT_TRUE((*v).isNumber());
	ASSERT_FALSE((*v).isBoolean());
	ASSERT_EQ((*v).getNumber(), 3.0);
}

TEST(VarDereference, StarOpConst) {
	const json::Var V{ std::make_unique <json::Number>(5.0) };
	ASSERT_TRUE((*V).isNumber());
}

TEST(VarDereference, PointOp) {
	json::Var v{ std::make_unique<json::String>("Hi Theta!") };
	ASSERT_TRUE(v->isString());
	ASSERT_EQ(v->getString(), "Hi Theta!");
}

TEST(VarDereference, PointOpConst) {
	const json::Var V{ std::make_unique<json::String>("Hi Theta!") };
	ASSERT_TRUE(V->isString());
	ASSERT_EQ(V->getString(), "Hi Theta!");
}

TEST(VarCopy, DefaultCopy) {
	json::Var v;
	json::Var w = v;
	ASSERT_TRUE(w->isNull());
}

TEST(VarCopy, ValueConstructAndCopy) {
	json::Var v{ std::make_unique<json::Boolean>(true) };
	json::Var w = v;
	ASSERT_TRUE(w->getBoolean());
}

TEST(VarMove, NumberMove) {
	json::Var v = { std::make_unique<json::Number>(4.5) };
	json::Var w = std::move(v);
	ASSERT_TRUE(w->isNumber());
	ASSERT_EQ(w->getNumber(), 4.5);
	ASSERT_TRUE(v->isNull());
}

TEST(VarMove, StringMove) {
	json::Var v = { std::make_unique<json::String>("Hi Theta!") };
	json::Var w = std::move(v);
	ASSERT_TRUE(w->isString());
	ASSERT_EQ(w->getString(), "Hi Theta!");
	ASSERT_TRUE(v->isNull());
}

TEST(VarConvertValue, ConvertBool) {
	json::Var v{true};
	ASSERT_TRUE(v->isBoolean());
	ASSERT_TRUE(v->getBoolean());
}

TEST(VarConvertValue, ConvertNull) {
	json::Var v{nullptr};
	ASSERT_TRUE(v->isNull());
}

TEST(VarConvertValue, ConvertNumber) {
	json::Var v{3.5};
	ASSERT_TRUE(v->isNumber());
	ASSERT_EQ(v->getNumber(), 3.5);
}

TEST(VarConvertValue, ConvertString) {
	std::string s = "Hello!";
	json::Var v{s};
	ASSERT_TRUE(v->isString());
	ASSERT_EQ(v->getString(), "Hello!");
}

TEST(VarConvertValue, ConvertConstCharStar) {
	json::Var v{ "Hello!" };
	ASSERT_TRUE(v->isString());
	ASSERT_EQ(v->getString(), "Hello!");
}

TEST(VarConvertValue, ConvertInt) {
	json::Var v{ 3 };
	ASSERT_TRUE(v->isNumber());
	ASSERT_EQ(v->getNumber(), 3.0);
}

TEST(VarConvertValue, ConvertShortInt) {
	short int x = 4;
	json::Var v{ x };
	ASSERT_TRUE(v->isNumber());
	ASSERT_EQ(v->getNumber(), 4.0);
}

TEST(VarConvertData, CopyDataObject) {
	json::Var v = json::Number(3);
	ASSERT_TRUE(v->isNumber());
	ASSERT_EQ(v->getNumber(), 3);
}

TEST(VarConvertData, MoveDataObject) {
	json::String s = "Yeah!";
	json::Var v{ std::move(s) };
	ASSERT_TRUE(s.isString());
	ASSERT_TRUE(v->isString());
	ASSERT_EQ(s.getString(), "");
	ASSERT_EQ(v->getString(), "Yeah!");
}

TEST(VarPrint, PrintBooleanVar) {
	json::Var v = true;
	std::ostringstream out;
	out << v;
	ASSERT_EQ(out.str(), "true");
}

TEST(VarPrint, PrintNullVar) {
	json::Var v;
	std::ostringstream out;
	out << v;
	ASSERT_EQ(out.str(), "null");
}

TEST(VarPrint, PrintNumberVar) {
	json::Var v = 3.14;
	std::ostringstream out;
	out << v;
	ASSERT_EQ(out.str(), "3.14");
}

TEST(VarPrint, PrintStringVar) {
	json::Var v = "Hi Theta!";
	std::ostringstream out;
	out << v;
	ASSERT_EQ(out.str(), "\"Hi Theta!\"");
}

TEST(VarEquality, EqualsVar) {
	json::Var v{ 3.14 };
	json::Var w{ 3.14 };
	ASSERT_TRUE(v == w);
}

TEST(VarEquality, NotEqualsVar) {
	json::Var v{ true };
	json::Var w{ false };
	ASSERT_TRUE(v != w);
}

TEST(VarEquality, EqualsBool) {
	json::Var v{ false };
	bool b = false;
	ASSERT_TRUE(v == b);
}

TEST(VarEquality, NotEqualsBool) {
	json::Var v{ false };
	bool b = true;
	ASSERT_TRUE(v != b);
}

TEST(VarEquality, EqualsNumber) {
	json::Var v{ 3.0 };
	int n = 3;
	ASSERT_TRUE(v == n);
}

TEST(VarEquality, NotEqualsNumber) {
	json::Var v{ 3.5 };
	double d = 3.44;
	ASSERT_TRUE(v != d);
}

TEST(VarEquality, EqualsString) {
	json::Var v{ "Hi Rome!" };
	std::string s = "Hi Rome!";
	ASSERT_TRUE(v == s);
}

TEST(VarEquality, NotEqualsString) {
	json::Var v{ "Hi Rome!" };
	std::string s = "Hi Theta!";
	ASSERT_TRUE(v != s);
}

TEST(VarEquality, ReverseOrder) {
	json::Var v{ "Hi Theta!" };
	json::String s = "Hi Theta!";
	ASSERT_TRUE(s == v);
}


// Part 3: The Application (Array & Object)

TEST(DSDefaultConstruct, ArrayDefaultConstruct) {
	json::Array a;
	ASSERT_EQ((a.getArray()).size(), 0);
}

TEST(DSDefaultConstruct, ObjectDefaultConstruct) {
	json::Object o;
	ASSERT_EQ((o.getObject()).size(), 0);
}

TEST(DSValueConstruct, ArrayVCSize) {
	std::vector<json::Var> v = { 1, 2, 3, "yeah!" };
	json::Array a = v;
	ASSERT_EQ((a.getArray()).size(), 4);
}

TEST(DSValueConstruct, ArrayVCElements) {
	std::vector<json::Var> v = { 1, 2, 3, "yeah!" };
	json::Array a = v;
	ASSERT_EQ((a.getArray())[0], 1);
	ASSERT_EQ((a.getArray())[1], 2);
	ASSERT_EQ((a.getArray())[2], 3);
	ASSERT_EQ((a.getArray())[3], "yeah!");
}

TEST(DSValueConstruct, ObjectVCSize) {
	std::map<string, json::Var> m = { {"one", 1}, {"two", 2}, {"red", "fish"}, {"blue", "fish"} };
	json::Object o = m;
	ASSERT_EQ((o.getObject()).size(), 4);
}

TEST(DSValueConstruct, ObjectVCElements) {
	std::map<string, json::Var> m = { {"one", 1}, {"two", 2}, {"red", "fish"}, {"blue", "fish"} };
	json::Object o = m;
	ASSERT_EQ((o.getObject())["one"], 1);
	ASSERT_EQ((o.getObject())["two"], 2);
	ASSERT_EQ((o.getObject())["red"], "fish");
	ASSERT_EQ((o.getObject())["blue"], "fish");

}

TEST(DSInitializerList, ArrayILSize) {
	json::Array a = { 3, "abc", true, nullptr };
	ASSERT_EQ((a.getArray()).size(), 4);
}

TEST(DSInitializerList, ArrayILElements) {
	json::Array a = { 3, "abc", true, nullptr };
	ASSERT_EQ((a.getArray())[0], 3);
	ASSERT_EQ((a.getArray())[1], "abc");
	ASSERT_EQ((a.getArray())[2], true);
	ASSERT_EQ((a.getArray())[3], nullptr);
}

TEST(DSInitializerList, ObjectILSize) {
	json::Object o = { {"a", 3}, {"b", "abc"}, {"c", true}, {"d", nullptr} };
	ASSERT_EQ((o.getObject()).size(), 4);
}

TEST(DSInitializerList, ObjectILElements) {
	json::Object o = { {"a", 3}, {"b", "abc"}, {"c", true}, {"d", nullptr} };
	ASSERT_EQ((o.getObject())["a"], 3);
	ASSERT_EQ((o.getObject())["b"], "abc");
	ASSERT_EQ((o.getObject())["c"], true);
	ASSERT_EQ((o.getObject())["d"], nullptr);
}

TEST(DSTypeIdentifiers, ArrayIsArray) {
	json::Array a;
	ASSERT_TRUE(a.isArray());
}

TEST(DSTypeIdentifiers, NumberNotArray) {
	json::Number n;
	ASSERT_FALSE(n.isArray());
}

TEST(DSTypeIdentifiers, ArrayNotOthers) {
	json::Array a;
	ASSERT_FALSE(a.isBoolean());
	ASSERT_FALSE(a.isNull());
	ASSERT_FALSE(a.isNumber());
	ASSERT_FALSE(a.isString());
	ASSERT_FALSE(a.isObject());
}

TEST(DSTypeIdentifiers, ObjectIsObject) {
	json::Object o;
	ASSERT_TRUE(o.isObject());
}

TEST(DSTypeIdentifiers, StringNotObject) {
	json::String s;
	ASSERT_FALSE(s.isObject());
}

TEST(DSTypeIdentifiers, ObjectNotOthers) {
	json::Object o;
	ASSERT_FALSE(o.isBoolean());
	ASSERT_FALSE(o.isNull());
	ASSERT_FALSE(o.isNumber());
	ASSERT_FALSE(o.isString());
	ASSERT_FALSE(o.isArray());
}

TEST(DSGetValue, ArrayGetter) {
	json::Array a = { 1, 2, "bro" };
	json::Array b = a.getArray();
	ASSERT_EQ(a, b);
}

TEST(DSGetValue, ArrayElementGetter) {
	json::Array a = { true, true, false };
	ASSERT_EQ((a.getArray())[0], (a.getArray())[1]);
}

TEST(DSGetValue, ObjectGetter) {
	json::Object o = { {"red", true}, {"blue", false}, {"green", 255} };
	json::Object p = o;
	ASSERT_EQ(o, p);
}

TEST(DSGetValue, ObjectElementGetter) {
	json::Object o = { {"red", true}, {"blue", false}, {"green", 255} };
	ASSERT_EQ((o.getObject())["red"], true);
	ASSERT_EQ((o.getObject())["blue"], false);
	ASSERT_EQ((o.getObject())["green"], 255);
}

TEST(DSSetValue, ArraySetter) {
	json::Array a = { 1, 2, 3, "steel!" };
	ASSERT_EQ((a.getArray()).size(), 4);

	a.getArray() = { 1, 2, 4 };

	ASSERT_EQ((a.getArray()).size(), 3);
	ASSERT_EQ((a.getArray())[2], 4);
}

TEST(DSSetValue, ArrayElementSetter) {
	json::Array a = { true, true, "fish" };
	ASSERT_EQ((a.getArray())[1], true);

	(a.getArray())[1] = false;
	ASSERT_EQ((a.getArray())[1], false);

	(a.getArray())[0] = 3;
	ASSERT_EQ((a.getArray())[0], 3);
}

TEST(DSSetValue, ObjectSetter) {
	json::Object o;
	ASSERT_EQ((o.getObject()).size(), 0);

	o.getObject() = { {"string", "a"}, {"number", 2} };

	ASSERT_EQ((o.getObject()).size(), 2);
	ASSERT_EQ((o.getObject())["string"], "a");
	ASSERT_EQ((o.getObject())["number"], 2);
}

TEST(DSSetValue, ObjectElementSetter) {
	json::Object o = { {"string", "a"}, {"number", 2} };
	ASSERT_EQ((o.getObject())["string"], "a");

	(o.getObject())["string"] = "b";
	ASSERT_EQ((o.getObject())["string"], "b");

	(o.getObject())["string"] = false;
	ASSERT_EQ((o.getObject())["string"], false);

	(o.getObject())["number"] = 55.45;
	ASSERT_EQ((o.getObject())["number"], 55.45);
}

TEST(DSPrint, ArrayPrintMethod) {
	json::Array a = { true, true, 33 };
	std::ostringstream out;
	a.print(out);
	ASSERT_EQ(out.str(), "[true,true,33]");
}

TEST(DSPrint, ArrayPrintOperator) {
	json::Array a = { true, true, 33 };
	std::ostringstream out;
	out << a;
	ASSERT_EQ(out.str(), "[true,true,33]");
}

TEST(DSPrint, ObjectPrintMethod) {
	json::Object o = { {"one", 1}, {"two", 2} };
	std::ostringstream out;
	o.print(out);
	ASSERT_EQ(out.str(), "{\"one\":1,\"two\":2}");
}

TEST(DSPrint, ObjectPrintOperator) {
	json::Object o = { {"one", 1}, {"two", 2} };
	std::ostringstream out;
	out << o;
	ASSERT_EQ(out.str(), "{\"one\":1,\"two\":2}");
}

TEST(DSEquals, ArrayEqualsMethod) {
	json::Array a = { true, true, 33 };
	json::Array b = { true, true, 33 };
	json::Number n = 33;
	ASSERT_TRUE(a.equals(b));
	ASSERT_TRUE(b.equals(a));
	ASSERT_FALSE(a.equals(n));
	ASSERT_FALSE(b.equals(n));
}

TEST(DSEquals, ArrayEqualsOperator) {
	json::Array a = { 1, 2, "skip a few", 99, 100 };
	json::Array b = { 1, 2, "skip a few", 99, 100 };
	ASSERT_TRUE(a == b);
}

TEST(DSEquals, ArrayUnequalsOperator) {
	json::Array a = { 1, 2, 3, "yeah" };
	json::Array b = { 1, 2, 4, "yeah" };
	ASSERT_TRUE(a != b);
}

TEST(DSEquals, ObjectEqualsMethod) {
	json::Object o = { {"1", 1}, {"2", 2}, {"3", 3} };
	json::Object p = { {"1", 1}, {"2", 2}, {"3", 3} };
	json::Object q = { {"4", 4}, {"5", 5}, {"6", 6} };
	ASSERT_TRUE(o.equals(p));
	ASSERT_TRUE(p.equals(o));
	ASSERT_FALSE(o.equals(q));
	ASSERT_FALSE(p.equals(q));
	ASSERT_FALSE(q.equals(o));
	ASSERT_FALSE(q.equals(p));
}

TEST(DSEquals, ObjectEqualsOperator) {
	json::Object o = { {"1", 1}, {"2", 2}, {"3", 3} };
	json::Object p = { {"1", 1}, {"2", 2}, {"3", 3} };
	ASSERT_TRUE(o == p);
}

TEST(DSEquals, ObjectUnequalsOperator) {
	json::Object o = { {"1", 1}, {"2", 2}, {"3", 3} };
	json::Object p = { {"4", 4}, {"5", 5}, {"6", 6} };
	ASSERT_TRUE(o != p);
}

TEST(DSClone, ArrayCopy) {
	json::Array a = { 1, 2, 99, "1999", nullptr, true };
	auto ptr = a.clone();
	ASSERT_TRUE(*ptr == a);
}

TEST(DSClone, ArrayMove) {
	json::Array a = { 1, 2, 99, "1999", nullptr, true };
	auto ptr = a.eject();
	ASSERT_FALSE(*ptr == a);
	ASSERT_EQ((a.getArray()).size(), 0);
}

TEST(DSClone, ObjectCopy) {
	json::Object o = { {"one", 1}, {"two", 2} };
	auto ptr = o.clone();
	ASSERT_TRUE(*ptr == o);
}

TEST(DSClone, ObjectMove) {
	json::Object o = { {"one", 1}, {"two", 2} };
	auto ptr = o.eject();
	ASSERT_FALSE(*ptr == o);
	ASSERT_EQ((o.getObject()).size(), 0);
}