template<typename T>
class Range {

    using value_type = T;
    using pointer_type = T *;
    using reference_type = T &;

    value_type start;
    value_type stop;
    value_type step;

public:

    Range(value_type start, value_type stop, value_type step) : start(start), stop(stop), step(step) {}

    explicit Range(value_type stop) : Range(0, stop, 1) {}

    Range(value_type start, value_type stop) : Range(start, stop, 1) {}

    class Iterator {

        value_type curr;
        const Range &range;

    public:
        explicit Iterator(const Range &range, value_type index = 0) : curr(index), range(range) {}

        Iterator &operator++() {
            value_type tmp = curr + range.step;
            curr = tmp < range.stop ? tmp : range.stop;
            return *this;
        }

        Iterator operator++(int) {
            Iterator ret = *this;
            ++(*this);
            return ret;
        }

        value_type operator*() {
            return curr;
        }

        bool operator==(Iterator other) const { return curr == other.curr; }
        bool operator!=(Iterator other) const { return !operator==(other); }

    };

    Iterator begin() {
        return Iterator(*this, start);
    }

    Iterator end() {
        return Iterator(*this, stop);
    }

};

template<typename T>
Range<T> make_range(T &&stop) {
    return Range<T>(0, std::forward<T>(stop), 1);
}

template<typename T>
Range<T> make_range(T &&start, T &&stop, T &&step = 1) {
    return Range<T>(std::forward<T>(start), std::forward<T>(stop), std::forward<T>(step));
}