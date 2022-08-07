#pragma once

#include <iostream>
#include <memory>
#include "Box.h"

using namespace std;

class Container {
    // Exercise 2: Use smart pointer.

    //Box * pbox = nullptr;
    std::unique_ptr<Box> pbox;
public:
    static bool verbose;

//    Container(int content): pbox(new Box){
//        if(verbose) cout << "Creating Container" << endl;
//        pbox->setContent(content);
//    }
    explicit Container(int content) : pbox(std::make_unique<Box>(content)) {
        if (verbose) cout << "Creating Container" << endl;
    }

//    Container(const Container & container): pbox(new Box{*(container.pbox)}){
//        if(verbose) cout << "Creating copy of Container\n";
//    }
    Container(const Container &container) : pbox(std::make_unique<Box>(*(container.pbox))) {
        if (verbose) cout << "Creating copy of Container\n";
    }

//    Container & operator=(const Container &container){
//        if(this != &container) {
//            if(verbose) cout << "Copying Container\n";
//            *pbox = *container.pbox;
//        }
//        return *this;
//    }
    Container &operator=(const Container &container) {
        if (this != &container) {
            if (verbose) cout << "Copying Container\n";
            pbox->operator=(*container.pbox);
        }
        return *this;
    }

    Container(Container &&container) noexcept: pbox(std::move(container.pbox)) {
        if (verbose) cout << "Move constructor.\n";
    }

    Container &operator=(Container &&container) noexcept {
        if (this != &container) {
            if (verbose) cout << "Move assignment.\n";
            std::swap(pbox, container.pbox);
        }
        return *this;
    }

//    ~Container(){
//        if(verbose) cout << "Destroying Container \n";
//        delete pbox;
//    }
    ~Container() {
        if (verbose) cout << "Destroying Container \n";
    }

    friend Container operator+(const Container &p1, const Container &p2);

    friend std::ostream &operator<<(std::ostream &out, const Container &p) {
        return (out << " [" << p.pbox->getContent() << "] ");
    }
};

bool Container::verbose = false;

inline Container operator+(const Container &p1, const Container &p2) {
    Container sum(p1.pbox->getContent() + p2.pbox->getContent());
    return sum;
}
