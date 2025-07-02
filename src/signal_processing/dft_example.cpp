#include <iostream>
#include <iomanip>          // ← fixed, setprecision 사용
#include <cmath>            // ← std::abs
#include "baselab/signal_processing/dft.hpp"
#include "baselab/matplotlibcpp.h"


int main()
{
    using namespace baselab::signal;
    namespace plt = matplotlibcpp;

    constexpr std::size_t N = 8;
    std::vector<cd> signal;
    signal.reserve(N);

    // (1) x[n] = cos(2π·1·n/N)
    for (std::size_t n = 0; n < N; ++n) {
        signal.emplace_back(std::cos(2.0 * PI * 1.0 * n / N), 0.0);
    }

    // (2) DFT
    auto spectrum = dft(signal);

    // ────────────────────────────────────────────────
    // (3) 출력 helper: tiny 값은 0 처리
    auto pretty = [](double v, double eps = 1e-12)
    {
        return (std::abs(v) < eps) ? 0.0 : v;
    };

    // (4) 결과 출력
    std::cout << std::fixed << std::setprecision(6);   // 소수 6자리로 고정
    std::cout << "k\tRe\t\tIm\t\t|X[k]|" << std::endl;
    for (std::size_t k = 0; k < N; ++k) {
        std::cout << k << '\t'
                  << pretty(spectrum[k].real()) << '\t'
                  << pretty(spectrum[k].imag()) << '\t'
                  << pretty(std::abs(spectrum[k])) << '\n';
    }

    std::vector<double> k_vals, mags;
    for (std::size_t k = 0; k < spectrum.size(); ++k) {
        k_vals.push_back(static_cast<double>(k));
        mags.push_back(std::abs(spectrum[k]));
    }
    plt::stem(k_vals, mags);        // 막대형(stem) 플롯
    plt::xlabel("k (frequency bin)");
    plt::ylabel("|X[k]|");
    plt::title("DFT Magnitude");
    plt::show();
    return 0;
}
