#include <iostream>
#include "VectorTraits.h"
#include "Mixins.h"

class InitPolicy {
    typedef std::size_t size_type;
public:
    template<typename T>
    static void init(T *data, size_type N) {
        std::fill(data, data + N, VectorTraits<T>::default_value());
    }
};

class NoInitPolicy {
    typedef std::size_t size_type;
public:
    template<typename T>
    static void init(T *data, size_type N) {}
};

class CheckPolicy {
    typedef std::size_t size_type;
public:

    static void checkIndex(size_type index, size_type N) {
        if (index < 0 || index >= N) {
//            throw std::exception();
            std::cout << "exception" << std::endl;
        }
    }

    static void checkInit(size_type initSize, size_type N) {
        if (initSize > N) {
//            throw std::exception();
            std::cout << "exception" << std::endl;
        }
    }
};

class NoCheckPolicy {
    typedef std::size_t size_type;
public:

    static void checkIndex(size_type index, size_type N) {}
    static void checkInit(size_type initSize, size_type N) {}
};

using SafePolicy = Mixins<InitPolicy, CheckPolicy>;
using FastPolicy = Mixins<NoInitPolicy, NoCheckPolicy>;
using InitFastPolicy = Mixins<InitPolicy, NoCheckPolicy>;