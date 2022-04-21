#include <iostream>
#include "sources/Matrix.hpp"

using namespace zich;
using namespace std;

int main(){
    Matrix my_mat;
    Matrix other{{0, 1, 2, 3, 4, 5, 6, 7, 8}, 3, 3};
    Matrix res;
    bool ans;
    // std::istream s; 
    cout<<"Enter a 3x3 matrix"<<endl;
    try{
        // std::getline(cin, s);
        cin>>my_mat;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    try{
        cout<<my_mat<<endl;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    try{
        res = my_mat + other;
        cout<<my_mat<<" + "<<other<<" = "<<res<<endl;
        res = my_mat - other;
        cout<<my_mat<<" - "<<other<<" = "<<res<<endl;
        res = -my_mat;
        cout<<"-"<<my_mat<<" = "<<other<<endl;
        ans = (my_mat == other);
        cout<<"is "<<my_mat<<" == "<<other<<"? "<<ans<<endl;
        ans = (my_mat <= other);
        cout<<"is "<<my_mat<<" <= "<<other<<"? "<<ans<<endl;
        ans = (my_mat >= other);
        cout<<"is "<<my_mat<<" >= "<<other<<"? "<<ans<<endl;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    try{
        res = my_mat * other;
        cout<<my_mat<<" * "<<other<<" = "<<res<<endl;
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    res = my_mat * 3;
    cout<<my_mat<<" * 3 = "<<res<<endl;
    cout<<"++"<<my_mat<<" = "<<(++my_mat)<<endl;
}