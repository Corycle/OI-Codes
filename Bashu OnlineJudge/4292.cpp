#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
using namespace std;
int i,j,n;
void dzh(int f){
    int a=0,k,l;
    for(l=1;l<f;l++)a=a+n*4-l*8+4;
    if(j>=i)cout<<a+j+i-2*f+1;
    else cout<<a+(n-2*f+1)*4-j-i+f+f+1;
}
int main(){
	int p1,p2;
    cin>>n>>i>>j;
    p1=j;p2=i;
    if(p1>n/2)p1=n-p1+1;
    if(p2>n/2)p2=n-p2+1;
    if(p1>p2)dzh(p2);
        else dzh(p1);
	return 0;
}