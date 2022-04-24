 /** AUTHORS: Shahar Machluf
 * 
 * Date: 4-2-2022
 */

#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;

#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

/**
 * Returns the input string without the whitespace characters: space, newline and tab.
 * Requires std=c++2a.
 */
string nospaces(string input) {
	std::erase(input, ' ');
	std::erase(input, '\t');
	std::erase(input, '\n');
	std::erase(input, '\r');
	return input;
}

TEST_CASE("Build Matrix"){
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    CHECK_NOTHROW(Matrix(identity, 3, 3));
    CHECK_NOTHROW(Matrix(identity, 1, 9));
    CHECK_THROWS(Matrix(identity, 2, 3));
    CHECK_THROWS(Matrix(identity, 3, 2));
    CHECK_THROWS(Matrix(identity, 4, 3));
    CHECK_THROWS(Matrix(identity, 3, 4));
}

TEST_CASE("Plus/Minus"){
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    Matrix a{identity, 3, 3};
    Matrix b{arr, 3, 3};
    //good input
    Matrix c{{4, 0, 0, 0, 4, 0, 0, 0, 4}, 3, 3};
    CHECK((a+b) == (c));
    Matrix d{{2, 0, 0, 0, 2, 0, 0, 0, 2}, 3, 3};
    CHECK((b-a) == (d));
    Matrix e{{-2, 0, 0, 0, -2, 0, 0, 0, -2}, 3, 3};
    CHECK((a-b) == (e));
    Matrix f= +a;//copy 'a' to 'f'
    a+=b;
    CHECK(a == c);
    a-=b;
    CHECK(a == f);
    Matrix g = -b;
    Matrix h = {{-3, 0, 0, 0, -3, 0, 0, 0, -3}, 3, 3};
    CHECK(g == h);
    //bad input
    Matrix i = {{1, 0, 0, 0, 1, 0}, 2, 3};
    CHECK_THROWS(a+i);
    CHECK_THROWS(a-i);
    CHECK_THROWS(i+a);
    CHECK_THROWS(i-a);
    CHECK_THROWS(a+=i);
    CHECK_THROWS(a-=i);
    CHECK_THROWS(i+=a);
    CHECK_THROWS(i-=a);
}

TEST_CASE("Comparing"){
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    Matrix a{identity, 3, 3};
    Matrix b{arr, 3, 3};
    Matrix c{{3, 0, 0, 0, 3, 0, 0, 0, 3}, 3, 3};
    Matrix d{{3,3,3}, 3, 1};
    Matrix e{{2, 0, 0, 0, 3, 0, 0, 0, 4}, 3, 3};
    CHECK(b==c);
    CHECK_FALSE(a==b);
    CHECK(a!=b);
    CHECK_FALSE(b!=c);
    CHECK(b>a);
    CHECK_FALSE(a>b);
    CHECK(a<b);
    CHECK_FALSE(b<a);
    CHECK(b>=a);
    CHECK_FALSE(a>=b);
    CHECK(a<=b);
    CHECK_FALSE(b<=a);
    CHECK(b<=e);
    CHECK(e<=b);
    CHECK_FALSE(b==e);
    //bad input, not the same size
    CHECK_THROWS(bool ans =(a == d));
    CHECK_THROWS(bool ans = (a != d));
    CHECK_THROWS(bool ans = (a <= d));
    CHECK_THROWS(bool ans=(a >= d));
    CHECK_THROWS(bool ans=(a < d));
    CHECK_THROWS(bool ans=(a > d));
}

TEST_CASE("Increase/Decrease"){
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    Matrix a{arr, 3, 3};
    Matrix b{arr, 3, 3};
    Matrix c{{4, 1, 1, 1, 4, 1, 1, 1, 4}, 3, 3};
    Matrix d{{2, -1, -1, -1, 2, -1, -1, -1, 2}, 3, 3};
    CHECK(++a==c);
    CHECK((--b)==d);
    Matrix e{arr, 3, 3};
    Matrix f{arr, 3, 3};
    CHECK((e++)!=c);
    CHECK(e==c);
    CHECK((f--)!=d);
    CHECK(f==d);
}

TEST_CASE("Multiply"){
    std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
    Matrix a{arr, 3, 3};
    Matrix b{{9, 0, 0, 0, 9, 0, 0, 0, 9}, 3, 3};
    //multiply by number
    CHECK((a*3) == b);
    CHECK((3*a) == b);
    CHECK((b*(1/3)) == a);
    CHECK(((1/3)*b) == a);
    a*=3;
    CHECK(a==b);
    Matrix c{{1,2,3,4}, 2, 2};
    Matrix d{{1,2,3,4}, 2, 2};
    Matrix e{{7, 10, 15, 22}, 2, 2};
    //multiply 2 matrices
    CHECK((c*d) == e);
    CHECK_THROWS(a*c);
    CHECK_THROWS(c*a);
    c*=d;
    CHECK(c==e);
    //not square matrices
    Matrix f{{1,2,3,4,5,6}, 2, 3};
    Matrix g{{1,2,3,4,5,6}, 3, 2};
    CHECK_NOTHROW(c*f);
    CHECK_NOTHROW(g*c);
    CHECK_NOTHROW(g*f);
    CHECK_NOTHROW(f*g);
    CHECK_THROWS(f*c);
}

TEST_CASE("output"){
    Matrix a{{1,2,3,4,5,6}, 2, 3};
    ostringstream os1;
    os1<<a;
    CHECK(os1.str() == "[1 2 3]\n[2 5 6]");
    Matrix b{{1,2,3,4,5,6}, 3, 2};
    ostringstream os2;
    os2<<b;
    CHECK(os2.str() == "[1 2]\n[3 4]\n[5 6]");
}

TEST_CASE("input"){
    Matrix a;
    Matrix b{{1,1,1,1},2 ,2};
    istringstream is1{"[1 1][1 1]\n"};
    CHECK_THROWS(is1>>a);
    istringstream is2{"[1 1],[1 1]\n"};
    CHECK_THROWS(is2>>a);
    istringstream is3{"[1 1], 1 1]\n"};
    CHECK_THROWS(is3>>a);
    istringstream is4{"1 1], [1 1]\n"};
    CHECK_THROWS(is4>>a);
    istringstream is5{"[1 1], [1 1 1]\n"};
    CHECK_THROWS(is5>>a);
    istringstream is6{"[1 1], [1 1]\n"};
    CHECK_NOTHROW(is6>>a);
    is6>>a;
    CHECK(a==b);
}