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
const ll inf=9e18;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
ll a[N],f[N];
struct Node{
	int v,w;
	double Calc(){return 1.0*v/w;}
	friend bool operator<(Node A,Node B){
		return A.Calc()>B.Calc();
	}
}P[N];
bool cmp(Node A,Node B){return A.w<B.w;}
priority_queue<Node>q;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		while(q.size())q.pop();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=m;i++){
			P[i].v=read();
			P[i].w=read();
		}
		sort(P+1,P+m+1,cmp);
		for(int i=0;i<=a[n];i++)f[i]=inf;
		for(int i=1;i<=a[1];i++)f[i]=0;
		for(int t=2,j=0;t<=n;t++){
			int Lim=a[t-1];
			while(P[j+1].w<=Lim)q.push(P[++j]);
			Node tmp=q.top();
//			cout<<t<<": "<<tmp.v<<" "<<tmp.w<<endl;
			for(int i=a[t-1]+1;i<=a[t];i++){
				f[i]=f[i-tmp.w]+tmp.v;
			}
		}
//		for(int i=1;i<=a[n];i++)cout<<f[i]<<" ";cout<<endl;
		int flag=1;
		for(int i=1;i<=a[n];i++){
			if(f[i]==inf){flag=0;break;}
		}
		if(!flag)puts("-1");
		else{
			ll Ans=0;
			for(int i=1;i<=a[n];i++)Ans+=f[i];
			printf("%lld\n",Ans);
		}
	}
	return 0;
}
