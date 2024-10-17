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
#include<set>
#define ll long long
#define set_it set<Node>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double Y;
int n,tot,f[N],fa[N];
double Sqr(double x){return x*x;}
struct Circle{double x,y,r;int val;}C[N];
struct Node{
	int id,addv;
	double GetPos(){return C[id].x-addv*sqrt(Sqr(C[id].r)-Sqr(C[id].y-Y));}
	friend bool operator<(Node A,Node B){return A.id!=B.id?A.GetPos()<B.GetPos():A.addv>B.addv;}
}F[N];
set<Node>S;
bool cmp(Node A,Node B){
	return C[A.id].y-A.addv*C[A.id].r<C[B.id].y-B.addv*C[B.id].r;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		C[i].x=read();C[i].y=read();
		C[i].r=read();C[i].val=read();
		F[++tot]=(Node){i,1};
		F[++tot]=(Node){i,-1};
	}
	sort(F+1,F+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int id=F[i].id,addv=F[i].addv;
		if(addv==1){
			Y=C[id].y-C[id].r;
			if(S.size()){
				set_it it=S.lower_bound(F[i]);
				if(it!=S.end()){
					if((*it).addv==1)fa[id]=fa[(*it).id];
					if((*it).addv==-1)fa[id]=(*it).id;
				}
			}
			S.insert((Node){id,1});
			S.insert((Node){id,-1});
		}
		else{
			S.erase((Node){id,1});
			S.erase((Node){id,-1});
			f[fa[id]]+=max(f[id],C[id].val);
		}
	}
	printf("%d",f[0]);
	return 0;
}