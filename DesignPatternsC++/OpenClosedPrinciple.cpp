#include "pch.h"
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <vector>
#include<fstream>

using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

class Product {
private:
	string m_name;
	Color m_color;
	Size m_size;

public:
	Product(string name, Color color, Size size) : m_name(name), m_color(color), m_size(size) {

	}

	string get_name() { return m_name; }
	Color get_color() { return m_color; }
	Size get_size() { return m_size; }
};

class ProductFilter {
private:
	typedef vector<Product*> Items;
public:
	Items by_color(Items items, const Color color) {
		Items result;
		for (auto& i : items)
			if (i->get_color() == color)
				result.push_back(i);
		return result;
	}

	Items by_size(Items items, const Size size) {
		Items result;
		for (auto& i : items)
			if (i->get_size() == size)
				result.push_back(i);
		return result;
	}

	Items by_size_and_color(Items items, const Size size, const Color color) {
		Items result;
		for (auto& i : items)
			if (i->get_size() == size && i->get_color() == color)
				result.push_back(i);
		return result;
	}
};

// define an interface
template <typename T> class AndSpecification;

template <typename T> class Specification {
private:
public:

	virtual bool is_satisfied(T* item) const = 0;
};

template <typename T> class Filter;

template <typename T> class Filter {
	virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

class BetterFilter : Filter<Product> {
public:
	vector<Product*> filter(vector<Product*> items, Specification<Product> &spec) override {
		vector<Product*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};

class ColorSpecification : public Specification<Product> {
private:
	Color m_color;
public:
	ColorSpecification(Color color) : m_color(color) {

	}

	bool is_satisfied(Product *item) const override {
		return item->get_color() == m_color;
	}
};

class SizeSpecification : public Specification<Product> {
private:
	Size m_size;
public:
	SizeSpecification(Size size) : m_size(size) {

	}

	bool is_satisfied(Product *item) const override {
		return item->get_size() == m_size;
	}
};

template <typename T> class AndSpecification : public Specification<T> {
private:
	const Specification<T>& m_first;
	const Specification<T>& m_second;
public:
	AndSpecification(Specification<T>& first, Specification<T>& second) : m_first(first), m_second(second) {

	}

	Specification<T>& get_first() { return m_first; }
	Specification<T>& get_second() { return m_second; }

	bool is_satisfied(T *item) const override {
		return m_first.is_satisfied(item) && m_second.is_satisfied(item);
	}
};

//int main() {
//	Product apple{ "Apple", Color::green, Size::small };
//	Product tree{ "Tree", Color::green, Size::large };
//	Product house{ "House", Color::blue, Size::large };
//
//	const vector<Product*> all{ &apple, &tree, &house };
//
//	//ProductFilter filter;
//	//vector<Product*> result = filter.by_color(all, Color::green);
//	//for (auto& i : result) {
//	//	cout << i->get_name() << endl;
//	//}
//
//	BetterFilter bf;
//	ColorSpecification green(Color::green);
//	vector<Product*> green_things = bf.filter(all, green);
//	for (auto& x : green_things)
//		cout << x->get_name() << " is green\n";
//
//	SizeSpecification large(Size::large);
//	AndSpecification<Product> green_and_large(green, large);
//
//	vector<Product*> result = bf.filter(all, green_and_large);
//	for (auto& i : result)
//		cout << i->get_name() << endl;
//
//	return 0;
//}