#include <iostream>
#include "Matrix.hpp"

using namespace std;

namespace zich{
    Matrix::Matrix():rows(0), columns(0){}

    Matrix::Matrix(vector<double> vec, int n, int m):rows(n), columns(m){
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j] = vec[i+j];
            }
        }
    }

    Matrix::Matrix(const Matrix &other){
        this->rows = other.rows;
        this->columns = other.columns;
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j] = other.mat[i][j];
            }
        }
    }

    int Matrix::get_row_num(){
        return this->rows;
    }

    int Matrix::get_col_num(){
        return this->columns;
    }

    void size_check(const Matrix &a, const Matrix &b){
        if(a.rows != b.rows || a.columns != b.columns){
            throw("Can't use this operator on different size matrices");
        }
    }

    double mat_sum(const Matrix &mat1){
        int sum = 0;
        for(int i = 0; i < mat1.rows; i++){
            for(int j = 0; j < mat1.columns; j++){
                sum += mat1.mat[i][j];
            }
        }
        return sum;
    }

    Matrix& Matrix::operator=(const Matrix& mat){
        if(this == &mat){
            return(*this); 
        }else{
            Matrix copied(mat);
            return(copied);
        }
    }

    Matrix Matrix::operator+(const Matrix &other) const{
        size_check(*this, other);
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                vec[i+j] = this->mat[i][j] + other.mat[i][j];
            }
        }
        return(Matrix{vec, n, m});
    }

    Matrix Matrix::operator-(const Matrix &other) const{
        size_check(*this, other);
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                vec[i+j] = this->mat[i][j] - other.mat[i][j];
            }
        }
        return(Matrix{vec, n, m});
    }

    Matrix& Matrix::operator+=(const Matrix &other){
        size_check(*this, other);
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j] += other.mat[i][j];
            }
        }
        return *this;
    }
    Matrix& Matrix::operator-=(const Matrix &other){
        size_check(*this, other);
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j] -= other.mat[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator+() const{//onary +
        Matrix copied(*this);
        return(copied);
    }

    Matrix Matrix::operator-() const{//onary -
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                -(this->mat[i][j]);
            }
        }
        return *this;
    }
    bool operator==(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        for(int i=0; i<mat1.rows; i++){
            for(int j=0; j<mat1.columns; j++){
                if(mat1.mat[i][j] != mat2.mat[i][j]){
                    return(false);
                }
            }
        }
        return(true);
    }

    bool operator!=(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        return(!(mat1 == mat2));
    }

    bool operator<(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        int mat1_sum = mat_sum(mat1);
        int mat2_sum = mat_sum(mat2);
        return(mat1_sum < mat2_sum);
    }

    bool operator>(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        int mat1_sum = mat_sum(mat1);
        int mat2_sum = mat_sum(mat2);
        return(mat1_sum > mat2_sum);
    }

    bool operator<=(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        int mat1_sum = mat_sum(mat1);
        int mat2_sum = mat_sum(mat2);
        return(mat1_sum <= mat2_sum);
    }

    bool operator>=(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        int mat1_sum = mat_sum(mat1);
        int mat2_sum = mat_sum(mat2);
        return(mat1_sum >= mat2_sum);
    }

    Matrix& Matrix::operator++(){
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j]++;
            }
        }
        return *this;
    }

    Matrix& Matrix::operator--(){
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j]--;
            }
        }
        return *this;
    }

    const Matrix Matrix::operator++(const int dummy){
        Matrix copy(*this);
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j]++;
            }
        }
        return copy;
    }

    const Matrix Matrix::operator--(const int dummy){
        Matrix copy(*this);
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j]--;
            }
        }
        return copy;
    }

    Matrix Matrix::operator*(const Matrix &other) const{
        if(this->columns != other.rows){
            throw("Can't multiply the given matrices");
        }
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.columns; j++) {
                vec[i+j] = 0;
                for (int k = 0; k < other.rows; k++) {
                    vec[i+j] += this->mat[i][k] * other.mat[k][j];
                }
            }
        }
        return (Matrix{vec, n, m});
    }

    Matrix& Matrix::operator*=(const Matrix &other){
        vector <double> vec;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < other.columns; j++) {
                vec[i+j] = 0;
                for (int k = 0; k < other.rows; k++) {
                    vec[i+j] += this->mat[i][k] * other.mat[k][j];
                }
            }
        }
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j] = vec[i+j];
            }
        }
        return(*this);
    }

    Matrix& Matrix::operator*=(const double num){
        for(int i=0; i<this->rows; i++){
            for(int j=0; j<this->columns; j++){
                this->mat[i][j] *= num;
            }
        }
        return(*this);
    }

    Matrix Matrix::operator*(const double num){
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                vec[i+j] = this->mat[i][j] * num;
            }
        }
        return(Matrix{vec, n, m});
    }

    Matrix operator*(const double num, Matrix& mat){
        int n = mat.rows;
        int m = mat.columns;
        vector <double> vec;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                vec[i+j] = mat.mat[i][j] * num;
            }
        }
        return(Matrix{vec, n, m});
    }

    std::ostream& operator<<(std::ostream& output, const Matrix& other)
    {
        return output;
    }
    std::istream& operator>>(std::istream& input, Matrix& other)
    {
        input>>other.mat[0][0];
        return input;
    }
}