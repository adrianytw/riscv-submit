#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#define MATRIX_SIZE 1024

// https://youtu.be/xsZk3c7Oxyw

void naive_mul(const std::vector<std::vector<double>> &a,
               const std::vector<std::vector<double>> &b,
               std::vector<std::vector<double>> &c) {
  /* this code is the most obvious way to do it personally and i would consider
   * it naive or brute forcing this makes is easy to make sense and understand
   *  rank 8
   */

  int n = a.size();

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {

      double sum = 0;

      for (int k = 0; k < n; ++k)
        sum += a[i][k] * b[k][j];

      c[i][j] = sum;
    }
  }
}

// https://youtu.be/WcmdaB5sVyY
// https://open-catalog.codee.com/Glossary/Loop-tiling/
// https://youtu.be/aU1zsFk36l0

#define BLOCK_SIZE 32

void cache_mul(const std::vector<std::vector<double>> &a,
               const std::vector<std::vector<double>> &b,
               std::vector<std::vector<double>> &c) {
  /* this code uses attempts >.< to use loop-tiling/blocking
   *  kinda like divide and conquer, breaking down into smaller chucks then and
   * keeping them in cache to process while needed for fast cache
   */

  int n = a.size();
  int b_size = BLOCK_SIZE;

  for (int i = 0; i < n; i += b_size) {
    for (int j = 0; j < n; j += b_size) {
      for (int k = 0; k < n; k += b_size) {

        // inner block
        for (int ii = i; ii < i + b_size && ii < n; ++ii) {
          for (int jj = j; jj < j + b_size && jj < n; ++jj) {

            double sum = 0;
            for (int kk = k; kk < k + b_size && kk < n; ++kk) {
              sum += a[ii][kk] * b[kk][jj];
            }
            c[ii][jj] += sum;
          }
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {

  std::cout << "(a x b = c) with size " << MATRIX_SIZE << " x " << MATRIX_SIZE
            << std::endl;
  std::cout << "block size for tile is " << BLOCK_SIZE << std::endl;

  // Initialize matrices A and B with random values
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10.0, 10.0);

  std::vector<std::vector<double>> A(MATRIX_SIZE,
                                     std::vector<double>(MATRIX_SIZE));
  std::vector<std::vector<double>> B(MATRIX_SIZE,
                                     std::vector<double>(MATRIX_SIZE));
  std::vector<std::vector<double>> C_naive(
      MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 0.0));
  std::vector<std::vector<double>> C_cache(
      MATRIX_SIZE, std::vector<double>(MATRIX_SIZE, 0.0));

  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      A[i][j] = dis(gen);
      B[i][j] = dis(gen);
    }
  }

  // --- Naive Multiplication Benchmark ---
  auto start_naive = std::chrono::high_resolution_clock::now();
  naive_mul(A, B, C_naive);
  auto end_naive = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration_naive = end_naive - start_naive;

  std::cout << std::endl;
  std::cout << "naive multiplication time: \t\t" << duration_naive.count()
            << " seconds" << std::endl;

  // --- Tiled Multiplication Benchmark ---
  auto start_tiled = std::chrono::high_resolution_clock::now();
  cache_mul(A, B, C_cache);
  auto end_tiled = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration_tiled = end_tiled - start_tiled;

  std::cout << "tiling cached multiplication time: \t" << duration_tiled.count()
            << " seconds" << std::endl;

  return 0;
}
