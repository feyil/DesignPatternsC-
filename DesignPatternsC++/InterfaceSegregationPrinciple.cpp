#include "pch.h"
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <vector>
#include<fstream>

using namespace std;

class Document;

//class IMachine {
//	virtual void print(Document& doc) = 0;
//	virtual void fax(Document& doc) = 0;
//	virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine {
//public:
//	void print(Document& doc) override;
//	void fax(Document& doc) override;
//	void scan(Document& doc) override;
//};
//
//// 1. Recompile
//// 2. Client does not need this
//// 3. Forcing implementors to implement too much
//

struct IPrinter {
	virtual void print(Document& doc) = 0;
};

struct IScanner {
	virtual void scan(Document& doc) = 0;
};

class Printer : IPrinter {
public:
	void print(Document& doc) override;
};

class Scanner : IScanner {
public:
	void scan(Document& doc) override;
};

struct IMachine : IPrinter, IScanner {

};

class Machine : IMachine {
private:
	IPrinter& m_printer;
	IScanner& m_scanner;
public:
	Machine(IPrinter& printer, IScanner& scanner) : m_printer(printer), m_scanner(scanner) {
		
	}

	void print(Document& doc) override {
		m_printer.print(doc);
	}

	void scan(Document& doc) override {

	}
};

int main() {

}
