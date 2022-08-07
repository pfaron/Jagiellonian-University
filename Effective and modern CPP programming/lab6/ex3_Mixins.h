#include <iostream>
#include <vector>

template<class... Base>
class Mixins : public Base ... {
public:
    explicit Mixins(Base &&... mixins) : Base(std::forward<Base>(mixins))... {}
};