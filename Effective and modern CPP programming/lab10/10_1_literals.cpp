#include <iostream>

using namespace std;

/**
    Computes velocity in meters per seconds.
    @param distance  distance in meters
    @param time      time in seconds
    @return velocity in meters per seconds.
*/
double compute_velocity_m_per_s(double distance, double time) {
    return distance / time;
}

auto operator "" _km(long double x) {
    return x * 1000.;
}

auto operator "" _km(unsigned long long x) {
    return x * 1000;
}

auto operator "" _m(long double x) {
    return x;
}

auto operator "" _m(unsigned long long x) {
    return x;
}

auto operator "" _cm(long double x) {
    return x / 100.;
}

long double operator "" _cm(unsigned long long x) {
    return x / 100.;
}

constexpr int HOUR_TO_S = 60 * 60;

auto operator "" _h(long double x) {
    return x * HOUR_TO_S;
}

auto operator "" _h(unsigned long long x) {
    return x * HOUR_TO_S;
}

auto operator "" _s(long double x) {
    return x;
}

auto operator "" _s(unsigned long long x) {
    return x;
}

auto operator "" _ms(long double x) {
    return x / 1000.;
}

long double operator "" _ms(unsigned long long x) {
    return x / 1000.;
}

int main() {
    cout << compute_velocity_m_per_s(100_m, 5_s) << endl;     //20
    cout << compute_velocity_m_per_s(360_km, 2.0_h) << endl;  //50
    cout << compute_velocity_m_per_s(3.6_km, 0.02_h) << endl; //50
    cout << compute_velocity_m_per_s(250_cm, 2.5_ms) << endl; //1000
    return 0;
}
