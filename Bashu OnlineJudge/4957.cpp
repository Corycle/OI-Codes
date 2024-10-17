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
#include<unordered_map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int M=2000005;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,D,tot,MC,MaxC;
int a[N],w[N],C[N],f[N][N];
unordered_map<int,int>vis[N];
struct Attact{int d,val;}P[M];
struct Node{int d,F,L;};
bool cmp(Attact A,Attact B){return A.val!=B.val?A.val<B.val:A.d<B.d;}
void BFS(){
	queue<Node>q;
	q.push((Node){1,1,0});
	while(q.size()){
		Node A=q.front();q.pop();
		if(A.d==D)continue;
		q.push((Node){A.d+1,A.F,A.L+1});
		if(A.L&&1ll*A.F*A.L<=MaxC&&!vis[A.d+1][A.F*A.L]){
			q.push((Node){A.d+1,A.F*A.L,A.L});
			P[++tot]=(Attact){A.d+1,A.F*A.L};
			vis[A.d+1][A.F*A.L]=1;
		}
	}
}
void Prepare(){
	memset(f,-0x3f,sizeof(f));
	f[0][MC]=0;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=MC;j++){
			int k=min(j-a[i]+w[i],MC);
			f[i][k]=max(f[i][k],f[i-1][j]);
			f[i][j-a[i]]=max(f[i][j-a[i]],f[i-1][j]+1);
			D=max(D,max(f[i][k],f[i][j-a[i]]));
		}
	}
	BFS();
	sort(P+1,P+tot+1,cmp);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();MC=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=m;i++){
		C[i]=read();
		MaxC=max(MaxC,C[i]);
	}
	Prepare();
	for(int i=1;i<=m;i++){
		if(C[i]<=D){puts("1");continue;}
		int Ans=0,Max=-inf,k=1;
		for(int j=tot;j>=1;j--){
			while(k<tot&&P[j].val+P[k].val<=C[i]){
				Max=max(Max,P[k].val-P[k].d);
				k++;
			}
			if(P[j].val-P[j].d+Max>=C[i]-D){Ans=1;break;}
			if(P[j].val<=C[i]&&P[j].val-P[j].d>=C[i]-D){Ans=1;break;}
		}
		printf("%d\n",Ans);
	}
	return 0;
}