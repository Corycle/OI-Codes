#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
long long dzh(long long a,long long b,long long c)
{	if(b==1)return a%c;
	else{
		if(b%2==0)return ((dzh(a,b/2,c)%c)*(dzh(a,b/2,c)%c)%c);
		else return(((dzh(a,b/2,c)%c)*(dzh(a,b/2,c)%c))*(a%c)%c);
	}
}
int main(){
	long long b,p,k,s=1,i,v=1;
	scanf("%lld%lld%lld",&b,&p,&k);
	b%=k;
	printf("%lld",dzh(b,p,k));
	return 0;
}
