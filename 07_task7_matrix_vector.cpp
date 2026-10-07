#include <iostream>
#include <thread>
#include <vector>
#include <array>

void worker_multiply_row(
    int row,
    const std::array<std::array<int, 3>, 3>& matrix,
    const std::array<int, 3>& vec,
    std::array<int, 3>& result) {

    int sum = 0;
    for (int col = 0; col < 3; ++col)
        sum += matrix[row][col] * vec[col];

    result[row] = sum;
}

int main() {
    std::array<std::array<int, 3>, 3> matrix{{
        {{1, 2, 3}},
        {{4, 5, 6}},
        {{7, 8, 9}}
    }};
    std::array<int, 3> vec{{1, 2, 3}};
    std::array<int, 3> result{{0, 0, 0}};

    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i)
        threads.emplace_back(worker_multiply_row, i,
                             std::cref(matrix), std::cref(vec),
                             std::ref(result));

    for (auto& t : threads) t.join();

    std::cout << "Result Vector : [";
    for (int i = 0; i < 3; ++i) {
        std::cout << result[i] << (i == 2 ? "" : ", ");
    }
    std::cout << "]\n";

    return 0;
}
