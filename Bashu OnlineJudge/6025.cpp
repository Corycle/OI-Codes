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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int w[N],v[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=m;i++)v[i]=read();
	sort(v+1,v+m+1);v[m+1]=v[m]*2;
	for(int i=1,lst=0;i<=m;i++){
		if(v[i]==v[i+1])continue;
		int num=i-lst;lst=i;
		for(int j=1;j<=n;j++){
			int k=(w[j]%v[i+1])/v[i];
			if(k<num){w[j]-=v[i]*k;Ans+=k;num-=k;}
			else{w[j]-=v[i]*num;Ans+=num;num=0;break;}
		}
		for(int j=1;j<=n;j++){
			int k=w[j]/v[i];
			if(k<num){w[j]-=v[i]*k;Ans+=k;num-=k;}
			else{w[j]-=v[i]*num;Ans+=num;num=0;break;}
		}
	}
	printf("%d",Ans);
	return 0;
}