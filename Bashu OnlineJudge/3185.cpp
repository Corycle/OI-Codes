#include<iostream>
using namespace std;
int main(){
    int a=0,n;
    cin>>n;
    while(n!=0)
    {   a=a*10+n%10;
        n=n/10;}
    cout<<a<<endl;
    return 0;
}