#include <iostream>
#include <vector>

using namespace std;

namespace zich{
    class Matrix{
        vector<vector<double>> mat;
        int rows;
        int columns;
        public:
        Matrix();
        Matrix(vector<double> vec, int n, int m);
        Matrix(const Matrix &other); 
        int get_row_num();
        int get_col_num();
        friend void size_check(const Matrix &a, const Matrix &b);
        friend double mat_sum(const Matrix &mat1);
        Matrix& operator=(const Matrix &mat);
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix& operator+=(const Matrix &other);
        Matrix& operator-=(const Matrix &other);
        Matrix operator+() const;
        Matrix operator-() const;
        friend bool operator==(const Matrix &mat1, const Matrix &mat2);
        friend bool operator!=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>(const Matrix &mat1, const Matrix &mat2);
        friend bool operator<=(const Matrix &mat1, const Matrix &mat2);
        friend bool operator>=(const Matrix &mat1, const Matrix &mat2);
        Matrix& operator++();
        Matrix& operator--();
        const Matrix operator++(const int dummy);
        const Matrix operator--(const int dummy);
        Matrix operator*(double num);
        friend Matrix operator*(const double num, Matrix& mat);
        Matrix& operator*=(const double num);
        Matrix operator*(const Matrix &other) const;
        Matrix& operator*=(const Matrix &other);
        friend std::ostream& operator<<(std::ostream& stream, const Matrix& mat);
        friend std::istream& operator>>(std::istream& stream, Matrix& mat);
    };
};