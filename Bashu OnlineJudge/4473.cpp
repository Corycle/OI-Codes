/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt=1;
vector<int>V[N];
int f[N][2],fr[N][2],vst[N][2];
int bfx[N],bfy[N],btx[N],bty[N];
int lst_fx[N],lst_tx[N],lst_ty[N];
int h[N],H[N],dis[N],vis[N],down[N];
struct Point{int x,y,id,fx,fy,tx,ty,Up,Lup,Rup;}P[N];
bool cmpx(Point A,Point B){return A.x==B.x?A.y<B.y:A.x<B.x;}
bool cmpy(Point A,Point B){return A.y==B.y?A.x<B.x:A.y<B.y;}
bool cmp(Point A,Point B){return A.id<B.id;}
struct edge{int to,next,flow;}d[N*10];
void Add(int x,int y,int z){
	d[++cnt]=(edge){y,h[x],z};h[x]=cnt;
	d[++cnt]=(edge){x,h[y],0};h[y]=cnt;
}
void Prepare(){
	sort(bfx+1,bfx+bfx[0]+1);bfx[0]=unique(bfx+1,bfx+bfx[0]+1)-bfx-1;
	sort(bfy+1,bfy+bfy[0]+1);bfy[0]=unique(bfy+1,bfy+bfy[0]+1)-bfy-1;
	sort(btx+1,btx+btx[0]+1);btx[0]=unique(btx+1,btx+btx[0]+1)-btx-1;
	sort(bty+1,bty+bty[0]+1);bty[0]=unique(bty+1,bty+bty[0]+1)-bty-1;
	for(int i=1;i<=n;i++){
		P[i].fx=lower_bound(bfx+1,bfx+bfx[0]+1,P[i].fx)-bfx;
		P[i].fy=lower_bound(bfy+1,bfy+bfy[0]+1,P[i].fy)-bfy;
		P[i].tx=lower_bound(btx+1,btx+btx[0]+1,P[i].tx)-btx;
		P[i].ty=lower_bound(bty+1,bty+bty[0]+1,P[i].ty)-bty;
	}
	sort(P+1,P+n+1,cmpy);
	for(int i=n;i>=1;i--){
		if(lst_fx[P[i].fx])P[i].Up=lst_fx[P[i].fx];
		if(lst_tx[P[i].tx])P[i].Rup=lst_tx[P[i].tx];
		if(lst_ty[P[i].ty])P[i].Lup=lst_ty[P[i].ty];
		lst_fx[P[i].fx]=lst_tx[P[i].tx]=lst_ty[P[i].ty]=P[i].id;
	}
	sort(P+1,P+n+1,cmpx);
	for(int i=1;i<=n;i++)V[P[i].fy].push_back(P[i].id);
	sort(P+1,P+n+1,cmp);
}
void Print(int x){
	if(x==n)return;
	Print(fr[fr[x][1]][0]);
	if(x==fr[x][1])printf("%d ",x);
	else{
		printf("%d ",fr[x][1]);
		int a=fr[x][1],b=x,y=P[x].fy;
		int num=V[y].size(),fx=0,fy=0;
		for(int i=0;i<num;i++){
			if(V[y][i]==a)fx=i;
			if(V[y][i]==b)fy=i;
		}
		if(fx<fy){
			for(int i=fx-1;i>=0;i--)printf("%d ",V[y][i]);
			for(int i=fx+1;i<=fy;i++)printf("%d ",V[y][i]);
		}
		if(fx>fy){
			for(int i=fx+1;i<num;i++)printf("%d ",V[y][i]);
			for(int i=fx-1;i>=fy;i--)printf("%d ",V[y][i]);
		}
	}
}
void Old_Driver(){
	Prepare();
	memset(f,-0x3f,sizeof(f));
	int ans=0,Max=0,id=0;f[n][0]=0;
	for(int i=1;i<=bfy[0];i++){
		int num=V[i].size();
		Max=-inf;id=0;
		for(int j=0;j<num;j++){
			int x=V[i][j];
			if(f[x][1]<Max+j+1){f[x][1]=Max+j+1;fr[x][1]=id;}
			if(f[x][0]>Max){Max=f[x][0];id=x;}
		}
		Max=-inf;id=0;
		for(int j=num-1;j>=0;j--){
			int x=V[i][j];
			if(f[x][1]<Max+num-j){f[x][1]=Max+num-j;fr[x][1]=id;}
			if(f[x][0]>Max){Max=f[x][0];id=x;}
		}
		for(int j=0;j<num;j++){
			int x=V[i][j];
			if(f[x][1]<f[x][0]+1){f[x][1]=f[x][0]+1;fr[x][1]=x;}
			if(f[P[x].Up][0]<f[x][1]){f[P[x].Up][0]=f[x][1];fr[P[x].Up][0]=x;}
			if(f[P[x].Lup][0]<f[x][1]){f[P[x].Lup][0]=f[x][1];fr[P[x].Lup][0]=x;}
			if(f[P[x].Rup][0]<f[x][1]){f[P[x].Rup][0]=f[x][1];fr[P[x].Rup][0]=x;}
		}
	}
	printf("%d\n",f[0][0]-1);
	Print(fr[0][0]);printf("\n");
}
bool BFS(int s,int t){
	for(int i=1;i<=n+2;i++)dis[i]=-1;
	queue<int>q;q.push(s);dis[s]=0;
	while(q.size()){
		int x=q.front();q.pop();
		if(x==t)return true;
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(d[i].flow&&dis[y]==-1){
				dis[y]=dis[x]+1;q.push(y);
			}
		}
	}
	return false;
}
int DFS(int x,int maxx,int t){
	int ans=0;
	if(x==t||!maxx)return maxx;
	for(int &i=H[x];i;i=d[i].next){
		int y=d[i].to;
		if(d[i].flow&&dis[y]==dis[x]+1){
			int dlt=DFS(y,min(d[i].flow,maxx),t);
			if(!dlt)dis[y]=-1;
			d[i].flow-=dlt;
			d[i^1].flow+=dlt;
			maxx-=dlt;ans+=dlt;
			if(!maxx)return ans;
		}
	}
	return ans;
}
int Dinic(int s,int t){
	int ans=0;
	while(BFS(s,t)){
		for(int i=1;i<=n+2;i++)H[i]=h[i];
		ans+=DFS(s,inf,t);
	}
	return ans;
}
void Addedge(int x,int y){
	for(int i=h[x];i;i=d[i].next){
		if(y==d[i].to)return;
	}
	if(!y)return;
	Add(x,y,inf);
	down[y]++;down[x]--;
}
void Build(int y,int id){
	int num=V[y].size(),p=V[y][id],flag=0;
	if(vst[P[p].Up][0]&&f[P[p].Up][0]==f[p][1]){Addedge(p,P[p].Up);vst[p][1]=1;}
	if(vst[P[p].Lup][0]&&f[P[p].Lup][0]==f[p][1]){Addedge(p,P[p].Lup);vst[p][1]=1;}
	if(vst[P[p].Rup][0]&&f[P[p].Rup][0]==f[p][1]){Addedge(p,P[p].Rup);vst[p][1]=1;}
	if(!vst[p][1])return;
	if(f[p][1]==f[p][0]+1)vst[p][0]=1;
	for(int i=0;i<id;i++){
		int x=V[y][i];
		if(f[p][1]==f[x][0]+id+1)vst[x][0]=1;
	}
	for(int i=id+1;i<num;i++){
		int x=V[y][i];
		if(f[p][1]==f[x][0]+num-id)vst[x][0]=1;
	}
}
void Little_Gardener(){
	vst[0][0]=1;
	for(int i=bfy[0];i>=1;i--){
		int num=V[i].size();
		for(int j=0;j<num;j++){
			Build(i,j);
		}
	}
	int id=cnt,sum=0;
	int S=n+1,T=n+2;
	for(int i=1;i<=n;i++){
		if(down[i]>0){
			sum+=down[i];
			Add(S,i,down[i]);
		}
		if(down[i]<0)Add(i,T,-down[i]);
	}
	printf("%d",sum-Dinic(S,T));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		P[i].x=read();P[i].y=read();
		bfx[++bfx[0]]=P[i].fx=P[i].x;
		bfy[++bfy[0]]=P[i].fy=P[i].y;
		btx[++btx[0]]=P[i].tx=P[i].y-P[i].x;
		bty[++bty[0]]=P[i].ty=P[i].y+P[i].x;
		P[i].id=i;
	}
	P[++n].id=n;
	bfx[0]++;bfy[0]++;
	btx[0]++;bty[0]++;
	Old_Driver();
	Little_Gardener();
	return 0;
}