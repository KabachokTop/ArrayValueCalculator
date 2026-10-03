#include <iostream>
#include <vector>
#include <clocale>

using namespace std;

class ArraySizeException {
public:
    size_t rows;
    size_t cols;
    ArraySizeException(size_t r, size_t c) : rows(r), cols(c) {}
};

class ArrayDataException {
public:
    size_t row;
    size_t col;
    const char* value;
    ArrayDataException(size_t r, size_t c, const char* v) : row(r), col(c), value(v) {}
};

int parseInt(const char* s, size_t row, size_t col) {
    if (s == nullptr || *s == '\0') {
        throw ArrayDataException(row, col, s ? s : "");
    }

    int sign = 1;
    if (*s == '-') {
        sign = -1;
        ++s;
    }
    else if (*s == '+') {
        ++s;
    }

    if (*s == '\0') {
        throw ArrayDataException(row, col, s);
    }

    int result = 0;
    while (*s != '\0') {
        if (*s < '0' || *s > '9') {
            throw ArrayDataException(row, col, s);
        }
        result = result * 10 + (*s - '0');
        ++s;
    }
    return result * sign;
}

class ArrayValueCalculator {
public:
    int doCalc(const vector<vector<const char*>>& array) {
        if (array.size() != 4) {
            throw ArraySizeException(array.size(), 0);
        }
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i].size() != 4) {
                throw ArraySizeException(array.size(), array[i].size());
            }
        }

        int sum = 0;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                sum += parseInt(array[i][j], i, j);
            }
        }
        return sum;
    }
};

int main() {
	setlocale(LC_ALL, "uk_UA.UTF-8");
    ArrayValueCalculator calculator;

    vector<vector<const char*>> correctArray = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };

    try {
        int result = calculator.doCalc(correctArray);
        cout << "Результат розрахунку: " << result << endl;
    }
    catch (const ArraySizeException& e) {
        cout << "ArraySizeException: масив повинен бути 4x4. "
            << "Отримано rows=" << e.rows;
        if (e.cols != 0) cout << ", cols=" << e.cols;
        cout << endl;
    }
    catch (const ArrayDataException& e) {
        cout << "ArrayDataException: невірні дані в комірці ["
            << e.row << "][" << e.col << "]: \"" << (e.value ? e.value : "") << "\"" << endl;
    }
    catch (...) {
        cout << "Unexpected exception" << endl;
    }

    return 0;
}