#include "pch.h"
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <vector>
#include<fstream>

using namespace std;

// Object in a program should be replaceable wit instances of their subtypes

class Rectangle {
protected:
	int width, height;
public:
	Rectangle(const int width, const int height) : width(width), height(height) {

	}

	int get_width() const { return width; }
	virtual void set_width(const int width) { this->width = width; }
	int get_height() const { return height; }
	virtual void set_height(const int heigth) { this->height = height; }

	int area() const { return width * height; }
};

class Square : public Rectangle {
public:
	Square(int size) : Rectangle(size, size) {

	}

	void set_width(const int width) override {
		this->width = height = width;
	}

	void set_height(const int height) override {
		this->height = width = height;
	}
};

class RectangleFactory {
	static Rectangle create_rectanlge(int w, int h);
	static Rectangle create_square(int size);
};

void process(Rectangle& r) {
	int w = r.get_width();
	r.set_height(10);

	cout << "expected area = " << (w * 10) << ", got " << r.area() << endl;
}

int main() {
	Rectangle r{ 5,5 };
	process(r);

	Square s{ 5 };
	process(s);

	return 0;
}