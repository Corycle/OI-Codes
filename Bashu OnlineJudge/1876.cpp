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
int n,Ans;
struct Node{int a,id;}P[N];
bool cmp(Node A,Node B){
	return A.a!=B.a?A.a<B.a:A.id<B.id;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].a=read();
		P[i].id=i;
	}
	sort(P+1,P+n+1,cmp);
	for(int i=1;i<=n;i++){
		Ans=max(Ans,P[i].id-i+1);
	}
	printf("%d",Ans);
	return 0;
}