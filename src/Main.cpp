#include <iostream>
#include <iomanip> 
#include <string>   
#include <cassert> 
#include <utility>
#include "String.h"

using namespace tcii::ex;

inline void printTestHeader(const std::string& title) {

    std::cout << "\n\n" << std::string(70, '=') << "\n";
    std::cout << "TEST: " << title << "\n";
    std::cout << std::string(70, '-') << "\n";

}

inline void printStringState(const char* name, const String& s) {

    std::cout << std::left << std::setw(35) << name
              << " | Value: \"" << s.c_str() << "\"\n"
              << std::setw(35) << ""
              << " | Size: " << s.size()
              << ", Capacity: " << s.capacity()
              << ", Empty: " << (s.empty() ? "yes" : "no") << "\n\n";

}

inline void testConstructors() {

    printTestHeader("Constructors");

    std::cout << "Testing Default Constructor:\n";

    String s1;

    printStringState("String s1", s1);
    assert(s1.empty());

    std::cout << "Testing Constructor with const char*:\n";

    String s2 = "PagliosaPagl";

    printStringState("String s2 = short text", s2);
    assert(s2.size() == 12);
    assert(s2.capacity() >= 15);

    std::cout << "Testing Constructor with'const char*:\n";

    String s3 = "Pagliosa Pagliosa Pagliosa PagliosaPagliosaPagliosaPagliosa";

    printStringState("String s3 = long text", s3);

    assert(s3.size() == 59);
    assert(s3.capacity() > 15);

    std::cout << "Testing Copy Constructor:\n";

    String s4 = s3;

    printStringState("String s4 = s3", s4);

    assert(s4 == s3);
    assert(s4.size() == s3.size());

    std::cout << "Testing Move Constructor:\n";

    String s5 = std::move(s4);

    printStringState("String s5 = std::move(s4)", s5);
    printStringState("State of s4 after move:", s4);

    assert(s5 == s3);
    assert(s4.empty());

}

inline void testAssignments() {

    printTestHeader("Assignment Operators =");
    String s, t;

    std::cout << "Assignment with const char*:\n";
    s = "Pagliosa Pagl";
    printStringState("s = initial value", s);
    assert(s == "Pagliosa Pagl");

    std::cout << "Copy Assignment:\n";
    t = s;
    printStringState("t = s", t);
    assert(t == s);

    std::cout << "Self Assignment:\n";
    s = s;
    printStringState("s = s", s);
    assert(s == "Pagliosa Pagl");

    std::cout << "Move Assignment:\n";

    String longStr = "Pagliosa Pagliosa Pagliosa Pagliosa Paglio";

    printStringState("longStr before move", longStr);

    s = std::move(longStr);
    
    printStringState("s = std::move(longStr)", s);
    printStringState("longStr after move", longStr);

    assert(s == "Pagliosa Pagliosa Pagliosa Pagliosa Paglio");
    assert(longStr.empty());

}

inline void testConcatenation() {

    printTestHeader("Concatenation Operators + and +=");

    std::cout << "Testing concatenation with +=:\n";

    String s = "Paglio";

    printStringState("s initial", s);

    s += ", ";

    printStringState("s += \", \"", s);

    s += String("oilgaP");

    printStringState("s += String(\"Oilgap\")", s);

    assert(s == "Paglio, oilgaP");

    std::cout << "\nTesting concatenation with +:\n";

    String s1 = "Paulo";
    String s2 = "Pagliosa";
    String res = s1 + " " + s2 + "!";

    printStringState("s1", s1);
    printStringState("s2", s2);
    printStringState("res = s1 + \" \" + s2 + \"!\"", res);

    assert(res == "Paulo Pagliosa!");
    assert(s1 == "Paulo");

    std::cout << "\nTesting reallocation during concatenation:\n";

    String r = "Pagliosa Pag";

    printStringState("r before reallocation", r);

    r += " Paulo Pagliosa Paulo Pagliosa Paulo Pagliosa Paulo Paglio";

    printStringState("r after reallocation", r);

    assert(r.capacity() > 15);

}

inline void testAdditionalMethods() {

    printTestHeader("Additional Methods clear, [], etc...");
    
    std::cout << "Testing clear():\n";
    String s = "Paulo Pagliosa pau";

    printStringState("s before clear", s);

    s.clear();

    printStringState("s.clear()", s);

    assert(s.empty());
    assert(s.size() == 0);

    std::cout << "\nTesting Access with operator[]:\n";

    String t = "Paulo";

    printStringState("t original", t);

    t[0] = 'X';
    t[4] = 'Z';

    printStringState("t[0] = 'X', t[4] = 'Z'", t);

    assert(t == "XaulZ");
    
    const String& c_t = t;

    std::cout << "Accessing t[1]: " << c_t[1] << "\n";

    assert(c_t[1] == 'a');

}

inline void
stringTest() 
{

    testConstructors();
    
    testAssignments();
    
    testConcatenation();

    testAdditionalMethods();
  
}
//
// Main function
//
int
main()
{
  stringTest();
  return 0;
}
