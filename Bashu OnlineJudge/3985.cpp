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
int n,m,s[N];
ll Ans,s1[N],s2[N];
struct Node{int x,g,d;}P[N];
bool cmp(Node A,Node B){return A.x<B.x;}
ll F(int x){return s2[x-1]-P[x].x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();
		P[i].g=read();
		P[i].d=read();
	}
	sort(P+1,P+n+1,cmp);
	for(int i=1;i<=n;i++){
		s1[i]=s1[i-1]+P[i].g;
		s2[i]=s2[i-1]+P[i].d;
	}
	s[++s[0]]=1;Ans=P[1].g;
	for(int i=2;i<=n;i++){
		if(F(i)<F(s[s[0]]))s[++s[0]]=i;
		int l=1,r=s[0],pos=i;
		while(l<=r){
			int mid=(l+r)>>1;
			if(s2[i]-P[i].x>=F(s[mid])){
				pos=s[mid];r=mid-1;
			}
			else l=mid+1;
		}
		Ans=max(Ans,s1[i]-s1[pos-1]);
	}
	printf("%lld",Ans);
	return 0;
}