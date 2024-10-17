#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();
		int m=0,t=0;
		for(int i=1;i<=n;i++){
			int x=read();
			if(x<=1)t++;
			m^=x;
		}
		if(m==0&&t==n)printf("Cio\n");
		if(m!=0&&t!=n)printf("Cio\n");
		if(m!=0&&t==n)printf("Nod\n");
		if(m==0&&t!=n)printf("Nod\n");
	}
	return 0;
}