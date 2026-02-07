#include<iostream>
#include<vector>
#include<chrono>
#include<immintrin.h>
using namespace std;
// This code demonstrates the performance difference between a scalar implementation of the dot product and an AVX-optimized version.

// The scalar version computes the dot product using a simple loop, while the AVX version uses 256-bit wide SIMD registers to process 8 floats at a time, significantly improving performance on large vectors.
float scalar_dot_product(const vector<float>& A, const vector<float>& B ){
    float sum=0.0f;
    for(size_t i=0; i< A.size(); i++){
        sum+=A[i]*B[i];
    }
    return sum;
}
// AVX version of the dot product
float avx_dot_product(const vector<float>& A, const vector<float>& B){
    __m256 sum_vec=_mm256_setzero_ps();
    size_t i=0;
    for(; i+8 <=A.size(); i+=8){
        __m256 vecA=_mm256_loadu_ps(&A[i]);       // Load 8 floats from A into an AVX register
        __m256 vecB=_mm256_loadu_ps(&B[i]);       // Load 8 floats from B into another AVX register
        __m256 res=_mm256_mul_ps(vecA, vecB);     // Perform element-wise multiplication of the two vectors
        sum_vec=_mm256_add_ps(sum_vec, res);      // Accumulate the results into sum_vec
    };
    float temp[8];                                // Store the accumulated sum_vec back to a temporary array
    _mm256_storeu_ps(temp, sum_vec);
    float total_sum=0.0f;
    for(int j=0; j<8; j++){
        total_sum+=temp[j];
    }
    for(; i<A.size(); ++i){                       // Handle any remaining elements if the size of the vectors is not a multiple of 8
        total_sum+=A[i]*B[i];
    }
    return total_sum;
};
    
int main() {
    // Create HUGE vectors to see the difference
    size_t N = 1000000; // 1 Million Dimensions
    vector<float> A(N, 1.0f);
    vector<float> B(N, 2.0f);

    cout << "Benchmarking Dot Product on " << N << " elements..." << endl;

    // Time Scalar
    auto start = chrono::high_resolution_clock::now();
    float res1 = scalar_dot_product(A, B);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> scalar_time = end - start;
    cout << "[Scalar] Result: " << res1 << " | Time: " << scalar_time.count() << "s" << endl;

    // Time AVX
    start = chrono::high_resolution_clock::now();
    float res2 = avx_dot_product(A, B);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> avx_time = end - start;
    cout << "[AVX]    Result: " << res2 << " | Time: " << avx_time.count() << "s" << endl;
    //Measure Speedup
    cout << "Speedup: " << scalar_time.count() / avx_time.count() << "x FASTER" << endl;
    return 0;
}