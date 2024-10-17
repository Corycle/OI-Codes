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
const int Lim=1e5;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
struct Function{
	int m,k;
	int F(int x){return (x-m)*(x-m)+k;}
}P[N*2];
struct Node{
	int y,id;
	friend bool operator==(Node A,Node B){return A.y==B.y&&A.id==B.id;}
	friend bool operator<(Node A,Node B){return A.y!=B.y?A.y>B.y:A.id>B.id;}
};
struct Heap{
	priority_queue<Node>q1,q2;
	void Insert(Node A){q1.push(A);}
	void Delete(Node A){q2.push(A);}
	Node Top(){
		while(q2.size()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.size()?q1.top():(Node){inf,0};
	}
}F[N];
void Insert(int i){Ans++;F[P[i].m].Insert((Node){P[i].k,i});}
void Delete(int i){Ans--;F[P[i].m].Delete((Node){P[i].k,i});}
void Update(int x,int t){
	for(int i=x-1;i>=1;i--){if((x-i)*(x-i)>t)break;while(1){Node A=F[i].Top();if(A.id&&P[A.id].F(x)<=t)Delete(A.id);else break;}}
	for(int i=x;i<=Lim;i++){if((x-i)*(x-i)>t)break;while(1){Node A=F[i].Top();if(A.id&&P[A.id].F(x)<=t)Delete(A.id);else break;}}
}
int main(){
//	freopen("function.in","r",stdin);
//	freopen("function.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){P[i].m=read();P[i].k=read();Insert(i);}
	while(m--){
		int op=read();
		if(op==1){n++;P[n].m=read();P[n].k=read();Insert(n);}
		if(op==2){int x=read(),t=read();Update(x,t);}
		printf("%d\n",Ans);
	}
	return 0;
}