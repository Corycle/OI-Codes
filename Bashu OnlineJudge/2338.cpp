#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-8;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
double m;
struct Point{
	int x,y;
}p1[N],p2[N];
string Name[N];
map<string,int>id1,id2,s;
int p[N],visx[N],visy[N];
int lx[N],ly[N],w[N][N];
double Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
bool DFS(int x){
	visx[x]=1;
	for(int y=1;y<=n;y++){
		if(!visy[y]&&lx[x]+ly[y]==w[x][y]){
			visy[y]=1;
			if(!p[y]||DFS(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
void Adjust(){
	int d=inf;
	for(int i=1;i<=n;i++){
		if(!visx[i])continue;
		for(int j=1;j<=n;j++){
			if(!visy[j])d=min(d,lx[i]+ly[j]-w[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		if(visx[i])lx[i]-=d;
		if(visy[i])ly[i]+=d;
	}
}
void KM(){
	for(int i=1;i<=n;i++){
		lx[i]=-inf;
		ly[i]=0;
		for(int j=1;j<=n;j++){
			lx[i]=max(lx[i],w[i][j]);
		}
	}
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++){
		while(1){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(DFS(i))break;
			Adjust();
		}
	}
}
void Change(string &x){
	int len=x.length()-1;
	for(int i=0;i<=len;i++){
		if('A'<=x[i]&&x[i]<='Z')x[i]=x[i]-'A'+'a';
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	m=read();
	n=read();
	string A,B;
	for(int i=1;i<=n;i++){
		p1[i].x=read();
		p1[i].y=read();
		cin>>A;
		Change(A);
		id1[A]=i;
		s[A]=1;
	}
	for(int i=1;i<=n;i++){
		p2[i].x=read();
		p2[i].y=read();
		cin>>A;
		Change(A);
		id2[A]=i;
		s[A]=2;
	}
	while(1){
		cin>>A;
		if(A=="End")break;
		cin>>B;
		Change(A);Change(B);
		if(s[A]==2)swap(A,B);
		int x=id1[A],y=id2[B];
		w[x][y]=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!w[i][j])w[i][j]=1;
			double len=Dist(p1[i],p2[j]);
			if(len>m)w[i][j]=-inf;
			for(int k=1;k<=n;k++){
				double dis1=len-Dist(p1[i],p1[k])-Dist(p1[k],p2[j]);
				double dis2=len-Dist(p1[i],p2[k])-Dist(p2[k],p2[j]);
				if((k!=i&&dis1>=0&&dis1<eps)||(k!=j&&dis2>=0&&dis2<eps)){
					w[i][j]=-inf;
					break;
				}
			}
		}
	}
	KM();
	int ans=0;
	for(int i=1;i<=n;i++){
		if(p[i])ans+=w[p[i]][i];
	}
	printf("%d",ans);
	return 0;
}