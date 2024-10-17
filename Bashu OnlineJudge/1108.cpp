#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
long long minmin(long a,long b){
   if(a<b)return(a);
   else return(b);
}
main(){
  long long n,m,i,f[100];
  cin>>n>>m;
  f[0]=1;
  for(i=1;i<=n;i++){
    if(i-m-1==-1)f[i]=f[i-1]*2-1;
    else if(i-m-1<-1)f[i]=f[i-1]*2;
    else f[i]=f[i-1]*2-f[i-m-1];
  }
  cout<<f[n];
}