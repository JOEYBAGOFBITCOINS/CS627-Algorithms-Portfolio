#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

using Clock = std::chrono::high_resolution_clock;

// In-place reverse of an int array.
// Returns a simple step-count model t(n) based on a consistent per-iteration count.
//
// Model idea (worst case is the only case here because this always does ~n/2 swaps):
// k = floor(n/2) iterations of the while-loop.
// Per iteration, we do: 1 comparison (l < r) + 3 assignments for swap + 2 index updates = 6 steps.
// The loop condition is evaluated k+1 times.
// So a simple model is: t(n) = 6k + (k+1) = 7k + 1, where k = floor(n/2).
std::uint64_t reverse_in_place(std::vector<int>& a) {
    std::uint64_t n = static_cast<std::uint64_t>(a.size());
    std::uint64_t k = n / 2;

    std::size_t l = 0;
    std::size_t r = a.empty() ? 0 : (a.size() - 1);

    while (l < r) {
        int temp = a[l];
        a[l] = a[r];
        a[r] = temp;
        ++l;
        --r;
    }

    return 7ULL * k + 1ULL;
}

// Generate a random int array of size n
std::vector<int> make_random_array(std::size_t n, std::uint32_t seed) {
    std::vector<int> a(n);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(-1'000'000, 1'000'000);
    for (std::size_t i = 0; i < n; ++i) a[i] = dist(rng);
    return a;
}

bool is_reversed_correctly(const std::vector<int>& original, const std::vector<int>& reversed) {
    if (original.size() != reversed.size()) return false;
    for (std::size_t i = 0; i < original.size(); ++i) {
        if (original[i] != reversed[original.size() - 1 - i]) return false;
    }
    return true;
}

int main() {
    // Assignment suggests sizes like 500, 1500, 2500.
    // We'll include a couple extra to make the plot smoother.
    std::vector<std::size_t> sizes = {500, 1500, 2500, 3500, 4500};

    // Trials per size to reduce noise
    const int trials = 30;

    std::ofstream csv("runtime.csv");
    if (!csv) {
        std::cerr << "Error: could not open runtime.csv for writing.\n";
        return 1;
    }
    csv << "n,avg_us,min_us,max_us,step_model\n";

    std::cout << "In-place reversal benchmark (int arrays)\n";
    std::cout << "Trials per n: " << trials << "\n\n";

    for (std::size_t n : sizes) {
        std::uint64_t total_us = 0;
        std::uint64_t min_us = std::numeric_limits<std::uint64_t>::max();
        std::uint64_t max_us = 0;

        // Step model once per n (same n => same t(n) in this model)
        std::vector<int> dummy(n);
        std::uint64_t step_model = reverse_in_place(dummy);

        for (int t = 0; t < trials; ++t) {
            auto a = make_random_array(n, 1337u + static_cast<std::uint32_t>(t));
            auto original = a;

            auto start = Clock::now();
            reverse_in_place(a);
            auto end = Clock::now();

            if (!is_reversed_correctly(original, a)) {
                std::cerr << "Error: reversal correctness check failed for n=" << n << "\n";
                return 1;
            }

            auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::uint64_t u = static_cast<std::uint64_t>(us);

            total_us += u;
            min_us = std::min(min_us, u);
            max_us = std::max(max_us, u);
        }

        double avg_us = static_cast<double>(total_us) / static_cast<double>(trials);

        std::cout << "n=" << n
                  << " | avg=" << std::fixed << std::setprecision(2) << avg_us << "us"
                  << " | min=" << min_us << "us"
                  << " | max=" << max_us << "us"
                  << " | step_model t(n)=" << step_model
                  << "\n";

        csv << n << ","
            << std::fixed << std::setprecision(2) << avg_us << ","
            << min_us << ","
            << max_us << ","
            << step_model
            << "\n";
    }

    std::cout << "\nWrote runtime.csv (for plotting)\n";
    return 0;
}