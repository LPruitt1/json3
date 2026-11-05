#pragma once
#include "json.hpp"
#include <gtest/gtest.h>
#include <iostream>


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

TEST(VarEquality, Equals) {
	json::Var v{ 3.14 };
	json::Var w{ 3.14 };
	ASSERT_TRUE(v == w);
}

TEST(VarEquality, NotEquals) {
	json::Var v{ true };
	json::Var w{ false };
	ASSERT_TRUE(v != w);
}