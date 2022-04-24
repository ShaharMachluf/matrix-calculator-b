#include <iostream>
#include "sources/Matrix.hpp"

using namespace zich;
using namespace std;

int main(){
    Matrix my_mat;//user's matrix
    Matrix other{{0, 1, 2, 3, 4, 5, 6, 7, 8}, 3, 3};
    Matrix res;//result matrix
    bool ans;
    cout<<"Enter a 3x3 matrix"<<endl;
    try{
        cin>>my_mat;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    try{
        cout<<"your matrix is:\n"<<my_mat<<endl<<endl;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    cout<<"actions on your matrix"<<endl;
    try{//matrices must be with the same size
        //arithmetic 
        res = my_mat + other;
        cout<<my_mat<<"\n + \n"<<other<<"\n = \n"<<res<<endl<<endl;
        res = my_mat - other;
        cout<<my_mat<<"\n - \n"<<other<<"\n = \n"<<res<<endl<<endl;
        res = -my_mat;
        cout<<"-"<<my_mat<<"\n = \n"<<res<<endl<<endl;
        //comparing
        ans = (my_mat == other);
        cout<<"is \n"<<my_mat<<"\n == \n"<<other<<"\n? \n";
        cout<<boolalpha;
        cout<<ans<<endl<<endl;
        ans = (my_mat <= other);
        cout<<"is \n"<<my_mat<<"\n <= \n"<<other<<"\n? \n"<<ans<<endl<<endl;
        ans = (my_mat >= other);
        cout<<"is \n"<<my_mat<<"\n >= \n"<<other<<"\n? \n"<<ans<<endl<<endl;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    try{//my_mat's rows have to be the same size as other's columns
        res = my_mat * other;
        cout<<my_mat<<"\n * \n"<<other<<"\n = \n"<<res<<endl<<endl;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    res = my_mat * 3;
    cout<<my_mat<<"\n * 3 = \n"<<res<<endl<<endl;
    cout<<"++"<<my_mat<<"\n = \n"<<(++my_mat)<<endl;
}