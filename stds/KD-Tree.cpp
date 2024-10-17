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
const int M=2;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,D,Max,Min,root,q[M];
struct Tree{int ch[2],d[M],Max[M],Min[M];};
bool cmp(Tree A,Tree B){return A.d[D]<B.d[D];}
struct KD_Tree{
	Tree t[N];
	void Pushup(int p){
		for(int i=0;i<K;i++){
			if(t[p].ch[0]){
				t[p].Max[i]=max(t[p].Max[i],t[t[p].ch[0]].Max[i]);
				t[p].Min[i]=min(t[p].Min[i],t[t[p].ch[0]].Min[i]);
			}
			if(t[p].ch[1]){
				t[p].Max[i]=max(t[p].Max[i],t[t[p].ch[1]].Max[i]);
				t[p].Min[i]=min(t[p].Min[i],t[t[p].ch[1]].Min[i]);
			}
		}
	}
	void Build(int &p,int l,int r,int d){
		int mid=(l+r)>>1;p=mid;D=d;
		nth_element(t+l,t+mid,t+r+1,cmp);
		for(int i=0;i<K;i++){
			t[p].Max[i]=t[p].Min[i]=t[p].d[i];
		}
		if(l<mid)Build(t[p].ch[0],l,mid-1,d^1);
		if(r>mid)Build(t[p].ch[1],mid+1,r,d^1);
		Pushup(p);
	}
	int Guess1(int p){
		int ans=0;
		for(int i=0;i<K;i++){
			ans+=max(abs(t[p].Max[i]-q[i]),abs(t[p].Min[i]-q[i]));
		}
		return ans;
	}
	int Guess2(int p){
		int ans=0;
		for(int i=0;i<K;i++){
			if(q[i]>t[p].Max[i])ans+=abs(t[p].Max[i]-q[i]);
			if(q[i]<t[p].Min[i])ans+=abs(t[p].Min[i]-q[i]);
		}
		return ans;
	}
	int Dist(int p){
		int ans=0;
		for(int i=0;i<K;i++){
			ans+=abs(t[p].d[i]-q[i]);
		}
		return ans;
	}
	void Ask1(int p){
		if(!p)return;
		int dist=Dist(p);
		if(dist)Max=max(Max,dist);
		int dl=Guess1(t[p].ch[0]);
		int dr=Guess1(t[p].ch[1]);
		if(dl>dr){
			if(dl>Max)Ask1(t[p].ch[0]);
			if(dr>Max)Ask1(t[p].ch[1]);
		}
		else{
			if(dr>Max)Ask1(t[p].ch[1]);
			if(dl>Max)Ask1(t[p].ch[0]);
		}
	}
	void Ask2(int p){
		if(!p)return;
		int dist=Dist(p);
		if(dist)Min=min(Min,dist);
		int dl=Guess2(t[p].ch[0]);
		int dr=Guess2(t[p].ch[1]);
		if(dl<dr){
			if(dl<Min)Ask2(t[p].ch[0]);
			if(dr<Min)Ask2(t[p].ch[1]);
		}
		else{
			if(dr<Min)Ask2(t[p].ch[1]);
			if(dl<Min)Ask2(t[p].ch[0]);
		}
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=2;
	for(int i=1;i<=n;i++){
		tree.t[i].d[0]=read();
		tree.t[i].d[1]=read();
	}
	int Ans=inf;
	tree.Build(root,1,n,0);
	for(int i=1;i<=n;i++){
		q[0]=tree.t[i].d[0];
		q[1]=tree.t[i].d[1];
		Max=-inf;Min=inf;
		tree.Ask1(root);
		tree.Ask2(root);
		Ans=min(Ans,Max-Min);
	}
	printf("%d",Ans);
	return 0;
}
