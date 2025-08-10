# riscv-submit

## https://github.com/adrianytw/riscv-submit


```shell
nairda@ROG-STRIX:~/riscv$ make all
g++ -O3 -Wall -std=c++17 ans.cpp -o ans_o3
g++ -O3 -Wall -std=c++17 -mavx ans.cpp -o ans_avx
nairda@ROG-STRIX:~/riscv$ make run
--- Running O3 version ---
./ans_o3
(a x b = c) with size 1024 x 1024
block size for tile is 32

naive multiplication time:              2.18509 seconds
tiling cached multiplication time:      0.928121 seconds
--- Running AVX version ---
./ans_avx
(a x b = c) with size 1024 x 1024
block size for tile is 32

naive multiplication time:              2.06813 seconds
tiling cached multiplication time:      0.908464 seconds
```
