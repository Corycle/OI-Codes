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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,a[N],b[N];
int main(){
//	freopen("str.in","r",stdin);
//	freopen("str.out","w",stdout);
	int Case=read();
	while(Case--){
		m=read();scanf("%s",s+1);
		for(int i=1;i<=m;i++)a[i]=b[i]=0;n=0;
		for(int i=1;i<=m;i++){if(s[i]!=s[i-1])a[++n]=s[i]-'0';b[n]++;}
		int p1=1,p2=1,flag=0,ans=0;
		while(p1<=n){
			p2=max(p2,p1);
			while(p2<=n&&b[p2]==1)p2++;
			if(p2>n)flag=1;else b[p2]--;
			if(flag)p1++;p1++;ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}