/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
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
inline int gcd(int a,int b){
	return (b==0)?a:gcd(b,a%b);
}
int ans,a1,a0,b1,b0,t;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	t=read();
	while(t--){
		a0=read();a1=read();b0=read();b1=read();
		if(a0%a1||b1%b0||b1%a1){
			printf("0\n");
			continue;
		}
		ans=0;
		for(int i=1;i*i<=b1;i++){
			if(b1%i==0){
				if(i%a1==0&&gcd(i/a1,a0/a1)==1&&gcd(b1/b0,b1/i)==1)ans++;
				int j=b1/i;
				if(j%a1!=0||i==j)continue;//i*i=b1
				if(gcd(j/a1,a0/a1)==1&&gcd(b1/b0,b1/j)==1)ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}