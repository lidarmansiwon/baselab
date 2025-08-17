#pragma once
#include <vector>
#include <complex>
#include <cmath>

namespace signal_processing::signal {

using cd = std::complex<double>;
constexpr double PI = 3.14159265358979323846;

/**
 * @brief 1‑D Discrete Fourier Transform (naive O(N²))
 * @param x           입력 시퀀스 (time‑domain)
 * @param inverse     true → IDFT, false → DFT
 * @return std::vector<cd>  변환 결과
 */
inline std::vector<cd> dft(const std::vector<cd>& x, bool inverse = false)
{
    const std::size_t N = x.size();
    std::vector<cd> X(N);

    const double sign = inverse ? +2.0 : -2.0;  // e^{±j 2π kn/N}

    for (std::size_t k = 0; k < N; ++k) {
        cd acc{0.0, 0.0};
        for (std::size_t n = 0; n < N; ++n) {
            double angle = sign * PI * static_cast<double>(k * n) / static_cast<double>(N);
            acc += x[n] * std::exp(cd{0.0, angle});
        }
        if (inverse) acc /= static_cast<double>(N);
        X[k] = acc;
    }
    return X;
}

} // namespace baselab::signal
