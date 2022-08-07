template<typename T>
class VectorTraits {
public:
    typedef T basic_type;
    typedef basic_type scalar_type;
    typedef const basic_type &pass_type;

    static basic_type multiply(scalar_type scalar, pass_type elem) {
        return scalar * elem;
    }

    static basic_type default_value() {
        return basic_type{};
    }
};

template<>
class VectorTraits<int> {
public:
    typedef int basic_type;
    typedef basic_type scalar_type;
    typedef basic_type pass_type;

    static basic_type multiply(scalar_type scalar, pass_type elem) {
        return scalar * elem;
    }

    static basic_type default_value() {
        return 0;
    }
};

template<>
class VectorTraits<double> {
public:
    typedef double basic_type;
    typedef basic_type scalar_type;
    typedef basic_type pass_type;

    static basic_type multiply(scalar_type scalar, pass_type elem) {
        return scalar * elem;
    }

    static basic_type default_value() {
        return 0.;
    }
};

template<>
class VectorTraits<std::string> {
public:
    typedef std::string basic_type;
    typedef int scalar_type;
    typedef const basic_type &pass_type;

    static basic_type multiply(scalar_type scalar, pass_type elem) {
        std::string ret{};
        ret.reserve(scalar * elem.capacity());

        for (int i = 0; i < scalar; i++) {
            ret += elem;
        }

        return ret;
    }

    static basic_type default_value() {
        return "";
    }
};