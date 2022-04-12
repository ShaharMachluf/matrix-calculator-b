#include <iostream>
#include <ctype.h>
#include "Matrix.hpp"

using namespace std;
constexpr int SHIFT_LEFT = 10;

namespace zich{
    //empty constructor
    Matrix::Matrix():rows(0), columns(0){}

    //regular constructor
    Matrix::Matrix(vector<double> vec, int n, int m):rows(n), columns(m){
        if(n<=0 || m<=0){
            throw("Rows and columns must be positive");
        }
        if(vec.size()!=(n*m)){
            throw("Rows and columns doesn't mach the vector's size");
        }
        unsigned int k=0;
        for(unsigned int i=0; i<n; i++){
            vector <double> v1;
            for(unsigned int j=0; j<m; j++){
                v1.push_back(vec[k]);
                k++;
            }
            this->mat.push_back(v1);
        }
    }

    //copy constructor
    Matrix::Matrix(const Matrix &other){
        this->rows = other.rows;
        this->columns = other.columns;
        this->mat = other.mat;
    }

    int Matrix::get_row_num() const{
        return this->rows;
    }

    int Matrix::get_col_num() const{
        return this->columns;
    }

    //validation
    void size_check(const Matrix &a, const Matrix &b){
        if(a.rows != b.rows || a.columns != b.columns){
            throw("Can't use this operator on different size matrices");
        }
    }

    //get the sum of the elements in the matrix for comperacent
    double mat_sum(const Matrix &mat1){
        int sum = 0;
        for(unsigned int i = 0; i < mat1.rows; i++){
            for(unsigned int j = 0; j < mat1.columns; j++){
                sum += mat1.mat[i][j];
            }
        }
        return sum;
    }

    //Placement
    Matrix& Matrix::operator=(const Matrix& mat){
        if(this == &mat){//a=a
            return(*this); 
        }
        this->rows = mat.rows;
        this->columns = mat.columns;
        this->mat = mat.mat;
        return *this;
    }

    //A = B+C 
    Matrix Matrix::operator+(const Matrix &other) const{
        size_check(*this, other);
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for(unsigned int i=0; i<n; i++){
            for(unsigned int j=0; j<m; j++){
                vec.push_back(this->mat[i][j] + other.mat[i][j]);
            }
        }
        return(Matrix{vec, n, m});
    }

    //A = B-C
    Matrix Matrix::operator-(const Matrix &other) const{
        size_check(*this, other);
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for(unsigned int i=0; i<n; i++){
            for(unsigned int j=0; j<m; j++){
                vec.push_back(this->mat[i][j] - other.mat[i][j]);
            }
        }
        return(Matrix{vec, n, m});
    }

    //A+=B
    Matrix& Matrix::operator+=(const Matrix &other){
        size_check(*this, other);
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j] += other.mat[i][j];
            }
        }
        return *this;
    }

    //A-=B
    Matrix& Matrix::operator-=(const Matrix &other){
        size_check(*this, other);
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j] -= other.mat[i][j];
            }
        }
        return *this;
    }

    //A = +B (A=B)
    Matrix Matrix::operator+() const{//onary +
        Matrix copied(*this);
        return(copied);
    }

    //A = -B
    Matrix Matrix::operator-() const{//onary -
        vector <double> vec;
        unsigned int l=0;
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                vec.push_back((this->mat[i][j]) * -1);
            }
        }
        return (Matrix{vec, this->rows, this->columns});
    }

    //A==B (all the elements are the same)
    bool operator==(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        for(unsigned int i=0; i<mat1.rows; i++){
            for(unsigned int j=0; j<mat1.columns; j++){
                if(mat1.mat[i][j] != mat2.mat[i][j]){
                    return(false);
                }
            }
        }
        return(true);
    }

    //A!=B (not all the elements are the same)
    bool operator!=(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        return(!(mat1 == mat2));
    }

    //A<B (the sum of A < the sum of B)
    bool operator<(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        double mat1_sum = mat_sum(mat1);
        double mat2_sum = mat_sum(mat2);
        return(mat1_sum < mat2_sum);
    }

    //A>B (the sum of A > the sum of B)
    bool operator>(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        double mat1_sum = mat_sum(mat1);
        double mat2_sum = mat_sum(mat2);
        return(mat1_sum > mat2_sum);
    }

    //A<=B (the sum of A <= the sum of B)
    bool operator<=(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        double mat1_sum = mat_sum(mat1);
        double mat2_sum = mat_sum(mat2);
        return(mat1_sum <= mat2_sum);
    }

    //A>=B (the sum of A >= the sum of B)
    bool operator>=(const Matrix &mat1, const Matrix &mat2){
        size_check(mat1, mat2);
        double mat1_sum = mat_sum(mat1);
        double mat2_sum = mat_sum(mat2);
        return(mat1_sum >= mat2_sum);
    }

    //++A (increase all the elements by 1)
    Matrix& Matrix::operator++(){
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j]++;
            }
        }
        return *this;
    }

    //--A (dencrease all the elements by 1)
    Matrix& Matrix::operator--(){
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j]--;
            }
        }
        return *this;
    }

    //A++ (increase all the elements by 1)
    Matrix Matrix::operator++(const int dummy){
        Matrix copy(*this);
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j]++;
            }
        }
        return copy;
    }

    //A-- (dencrease all the elements by 1)
    Matrix Matrix::operator--(const int dummy){
        Matrix copy(*this);
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j]--;
            }
        }
        return copy;
    }

    //A = B*C
    Matrix Matrix::operator*(const Matrix &other) const{
        if(this->columns != other.rows){
            throw("Can't multiply the given matrices");
        }
        unsigned int l = 0;
        vector <double> vec;
        for (unsigned int i = 0; i < this->rows; i++) {
            for (unsigned int j = 0; j < other.columns; j++) {
                vec.push_back(0);
                for (unsigned int k = 0; k < other.rows; k++) {
                    vec[l] += this->mat[i][k] * other.mat[k][j];
                }
                l++;
            }
        }
        return (Matrix{vec, this->rows, other.columns});
    }

    //A *= B
    Matrix& Matrix::operator*=(const Matrix &other){
        if(this->columns != other.rows){
            throw("Can't multiply the given matrices");
        }
        unsigned int l = 0;
        vector <double> vec;
        for (unsigned int i = 0; i < this->rows; i++) {
            for (unsigned int j = 0; j < other.columns; j++) {
                vec.push_back(0);
                for (unsigned int k = 0; k < other.rows; k++) {
                    vec[l] += this->mat[i][k] * other.mat[k][j];
                }
                l++;
            }
        }
        l=0;
        for(unsigned int i=0; i<this->rows; i++){//put everything back to 'this'
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j] = vec[l++];
            }
        }
        return(*this);
    }

    //A *= num
    Matrix& Matrix::operator*=(const double num){
        for(unsigned int i=0; i<this->rows; i++){
            for(unsigned int j=0; j<this->columns; j++){
                this->mat[i][j] *= num;
            }
        }
        return(*this);
    }

    //A = B * num
    Matrix Matrix::operator*(const double num){
        int n = this->rows;
        int m = this->columns;
        vector <double> vec;
        for(unsigned int i=0; i<n; i++){
            for(unsigned int j=0; j<m; j++){
                vec.push_back(this->mat[i][j] * num);
            }
        }
        return(Matrix{vec, n, m});
    }

    //A = num * B
    Matrix operator*(const double num, Matrix& mat){
        int n = mat.rows;
        int m = mat.columns;
        vector <double> vec;
        for(unsigned int i=0; i<n; i++){
            for(unsigned int j=0; j<m; j++){
                vec.push_back(mat.mat[i][j] * num);
            }
        }
        return(Matrix{vec, n, m});
    }

    //cout<<A (output)
    std::ostream& operator<<(std::ostream& output, const Matrix& other)
    {
        string res;
        for(unsigned int i=0; i < other.rows; i++){
            res+="[";
            for(unsigned int j=0; j < other.columns; j++){
                res+=to_string((int)other.mat[i][j]);
                if(j<other.columns-1){
                    res+=" ";
                }
            }
            res+="]";
            if(i<other.rows-1){
                res+="\n";
            }
        }
        return(output<<res);
    }

    //cin>>A (input)
    std::istream& operator>>(std::istream& input, Matrix& other)
    {
        string s;
        unsigned int i=0;
        unsigned int j=0;
        unsigned int cols = 0;
        unsigned int l = 0;
        double temp = 0;
        vector <vector<double>> vec;
        getline(input, s, {});
        while(l< s.length()){
            if(s[l] != '['){
                throw("invalid input");
            }
            l++;
            i++;//new row
            vector <double> v1;
            while(s[l]!=']'){//row is not over
                if(s[l] == ' '){
                    l++;
                    continue;
                }
                temp = 0;
                while(s[l] != ' ' && s[l] != ']'){
                    temp = temp*SHIFT_LEFT + (double)s[l];
                    l++;
                }
                v1.push_back(temp);
                j++;//new element in the row
            }
            vec.push_back(v1);
            if(cols != 0 && cols != j){//not all the rows are in the same length
                throw("invalid input");
            }
            if(cols == 0){
                cols = j;
            }
            l++;
            if(s[l] == '\n'){//end of input
                break;
            }
            if(s[l]!= ','){
                throw("invalid input");
            }
            l++;
            if(s[l] != ' '){
                throw("invalid input");
            }
            l++;
            j=0;
        }
        other.rows = (int)i;
        other.columns = (int)cols;
        other.mat = vec;
        return input;
    }
}