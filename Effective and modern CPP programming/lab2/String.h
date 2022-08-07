#include <iostream>
#include <algorithm>
#include <memory>
#include "MyString.h"

using namespace std;

class String {
    using string = emcpp::MyString;
//    using string = std::string;

    /// Store a pointer to dynamically allocated string!
    shared_ptr<string> myString;

public:
    /// creates an empty string
    String() : myString(make_shared<string>()) {};

    /// copy C-string
    explicit String(const char *str) : myString(make_shared<string>(str)) {};

    /// no copy
    String(const String &s) : myString(s.myString) {};

    ~String() = default;

    /// no copy
    String operator=(const String &s) {
        if (this != &s)
            myString = s.myString;
        return *this;
    };

    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch) {
        if (myString.use_count() > 1) {
            myString.reset(new string(*myString));
        }
        myString->at(index) = ch;
    };

    /// no copy
    [[nodiscard]] char get(int index) const {
        return myString->at(index);
    };

    /// creates a new string only if both strings are non empty
    friend String operator+(const String &a, const String &b) {
        if (a.myString->length() == 0) {
            if (b.myString->length() == 0) {
                return *new String{};
            }
            return b;
        }
        if (b.myString->length() == 0) {
            return a;
        }
        auto newString = (*a.myString + *b.myString).c_str();
        String temp{newString};
        return temp;
    };

    friend std::ostream &operator<<(std::ostream &out, const String& s) {
        return (out << *s.myString);
    };
};
