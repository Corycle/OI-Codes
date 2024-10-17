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
const ll inf=0x3f3f3f3f;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,num,Ans1,Ans2;
struct Node{
	ll sum,len;
	friend bool operator<(Node A,Node B){
		return A.sum!=B.sum?A.sum>B.sum:A.len>B.len;
	}
};
priority_queue<Node>q;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++){
		q.push((Node){read(),0});
	}
	int t=(m-1-(n-1)%(m-1))%(m-1);num=n+t;
	for(int i=1;i<=t;i++)q.push((Node){0,0});
	while(num>1){
		num-=m-1;
		ll sum=0,len=0;
		for(ll i=1;i<=m;i++){
			Node A=q.top();q.pop();
			len=max(len,A.len+1);
			sum+=A.sum;
		}
		q.push((Node){sum,len});
		Ans1+=sum;Ans2=max(Ans2,len);
	}
	printf("%lld\n%lld",Ans1,Ans2);
	return 0;
}