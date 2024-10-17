#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int main(){
    int a,s=0,c=0,i,o;
    for(i=1;i<=12;i++){
        s+=300;
        cin>>a;
        if(s>=a){
            o=(s-a)/100*100;
            c+=o;s-=o+a;
        }
        else{
            cout<<"-"<<i;
            return 0;
        }
    }
    s+=c*12/10;
    cout<<s;
    return 0;
}