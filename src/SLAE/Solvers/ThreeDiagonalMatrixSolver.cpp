//
// Created by leeiozh on 05.02.2022.
//

#include "ThreeDiagonalMatrixSolver.hpp"
#include "iostream"

namespace Slae::Solvers {

std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col) {
    // алгоритм описан в docs -> Системы уравнений. Лекция 1. Прямые методы.pdf стр. 55-57

    std::vector<double> result(matrix.size());
    std::vector<double> coeffs(matrix.size() * 2); // коэффициенты гамма и бета соотвественно

#ifndef NDEBUG
    if (matrix.size() != col.size()) {
        // исключение выбрасывается в случае несовпадения размеров маттрицы и столбца свободных членов
        std::stringstream buff;
        buff << "Sizes didn't matched! Matrix size " << matrix.size() << "! Column size " << col.size() << "!"
             << std::endl;
        throw SlaeBaseException(buff.str());
    }
#endif //NDEBUG
    coeffs[0] = -matrix(0, 1) / matrix(0, 0);
    coeffs[1] = col[0] / matrix(0, 0);

    // цикл заполнения векторов коэффициентов
    for (int i = 1; i < matrix.size() - 1; ++i) {
        coeffs[2 * i] = -matrix(i, 2) / (matrix(i, 0) * coeffs[2 * (i - 1)] + matrix(i, 1));
        coeffs[2 * i + 1] = (col[i] - matrix(i, 0) * coeffs[2 * (i - 1) + 1]) /
                            (matrix(i, 0) * coeffs[2 * (i - 1)] + matrix(i, 1));
    }

    // обратный цикл подсчета самих решений
    int tmp_size = matrix.size() - 1;
    result[tmp_size] =
            (col[tmp_size] - matrix(tmp_size, 1) * coeffs[2 * (tmp_size - 1) + 1]) /
            (matrix(tmp_size, 2) + matrix(tmp_size, 1) * coeffs[2 * (tmp_size - 1)]);

    for (int i = matrix.size() - 2; i >= 0; --i) {
        result[i] = coeffs[2 * i] * result[i + 1] + coeffs[2 * i + 1];
    }
    return result;
}

} // namespace Slae::Solvers