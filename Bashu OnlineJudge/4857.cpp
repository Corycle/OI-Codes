/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int N=305;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
char s[N],t[N];
int main(){
//	freopen("master.in","r",stdin);
//	freopen("master.out","w",stdout);
	n=read();m=read();
	scanf("%s%s",s+1,t+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int num=0,pos=0;
			for(int k=1;k<=min(n-i+1,n-j+1);k++){
				if(s[i+k-1]==t[j+k-1])Ans=max(Ans,k);
				else if(num<m){num++;Ans=max(Ans,k);}
				else break;
			}
		}
	}
	printf("%d\n",Ans);
	return 0;
}