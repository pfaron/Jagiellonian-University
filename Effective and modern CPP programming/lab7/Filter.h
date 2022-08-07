#include <iostream>
#include <utility>
#include <algorithm>

template<class Container, typename Predicate>
class Filter {
private:
    Container container;
    Predicate predicate;

public:
    Filter(Container &&cont, Predicate &&pred) : container(std::forward<Container>(cont)),
                                                 predicate(std::forward<Predicate>(pred)) {}

    class Iterator {
    private:
        using cont_iterator = typename std::decay_t<Container>::iterator;

        Filter &filter;
        cont_iterator iterator;

        using cont_value = decltype(*iterator);

    public:
        Iterator(Filter &filter, cont_iterator iterator) : filter(filter), iterator(iterator) {}

        Iterator &operator++() {
            ++iterator;
            return *this;
        }

        Iterator operator++(int) {
            Iterator ret{*this};
            ++(*this);
            return ret;
        }

        cont_value &operator*() {
            getNextValid();
            return *iterator;
        }

        cont_value operator->(){
            getNextValid();
            return iterator;
        }

        bool operator==(Iterator other) const { return iterator == other.iterator; }

        bool operator!=(Iterator other) const { return !operator==(other); }

    private:
        void getNextValid() {
            while (iterator != filter.container.end() && !filter.predicate(*iterator)) {
                ++(*this);
            }
        }
    };

    using iterator = Iterator;

    iterator begin() {
        return iterator(*this, container.begin());
    }

    iterator end() {
        return iterator(*this, container.end());
    }
};

template<class Container, typename Predicate>
auto make_filter(Container &&c, Predicate &&p) {
    return Filter<Container, Predicate>(std::forward<Container>(c), std::forward<Predicate>(p));
}