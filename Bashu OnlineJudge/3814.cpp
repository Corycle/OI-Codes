#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,s,flag;
int gcd(int x,int y){
	return y==0?x:gcd(y,x%y);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	if(n==1){printf("1");return 0;}
	for(int i=1;i<=n;i++){
		if(gcd(i,n)==1)s++;
	}
	for(int i=1;i<=n;i++){
		int t=1;
		for(int j=1;j<=s;j++){
			t=t*i%n;
			if(t==1){
				if(j==s){
					printf("%d\n",i);
					flag=1;
				}
				break;
			}
		}
	}
	if(!flag)printf("-1");
	return 0;
}