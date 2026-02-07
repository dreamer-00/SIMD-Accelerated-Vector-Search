#SIMD-Accelerated Vector Search

A high-performance, single-header C++ vector search engine designed for low-latency memory retrieval.

## Key Features

🚀 AVX2 Optimized: Uses 256-bit SIMD registers for dot-product calculations.

⚡ 2.5x Speedup: Benchmarked against standard scalar implementation (Show your screenshot here).

🧠 Manual Memory Management: Custom allocation strategies to minimize cache misses.

🛠 No Dependencies: Pure C++17.

## Benchmarks

Scalar: 13ms (1M vectors)

AVX2: 5ms (1M vectors)

## Usage g++ -O3 -mavx2 main.cpp -o engine
