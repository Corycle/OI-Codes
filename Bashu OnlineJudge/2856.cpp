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
const int Mod=19997;//一个质数 
const int M=20005;
const int N=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,lst;
int k1,k2,fx,fy,s1;
int num[2],a[N],P[N],Hash[M],f[2][M];
int Map[N][N],val[N][N][2],data[2][M];
void Change(int x[],int y){
	int i=1;
	while(y){x[i++]=y%3;y/=3;}
	while(i<=m+1)x[i++]=0;
}
void Update(int s2,int Val){
	int i=s2%Mod;
	while(Hash[i]){
		if(data[k2][Hash[i]]==s2){
			f[k2][Hash[i]]=min(f[k2][Hash[i]],f[k1][lst]+Val);
			return;
		}
		i=(i+1)%Mod;
	}
	Hash[i]=++num[k2];
	data[k2][Hash[i]]=s2;
	f[k2][Hash[i]]=f[k1][lst]+Val;
}
void Shift(int x,int y){
	if(P[y]==0&&P[y+1]==0&&Map[x+1][y]&&Map[x][y+1]){//##->()
		Update(s1+a[y-1]+2*a[y],val[x][y][0]+val[x][y][1]);
		return;
	}
	if(P[y]==1&&P[y+1]==1){//((->##
		int flag=1,i;
		for(i=y+2;i<=m+1;i++){
			if(P[i]==1)flag++;
			if(P[i]==2)flag--;
			if(!flag)break;
		}
		Update(s1-a[y-1]-a[y]-a[i-1],0);
	}
	if(P[y]==2&&P[y+1]==2){//))->##
		int flag=1,i;
		for(i=y-1;i>=1;i--){
			if(P[i]==1)flag--;
			if(P[i]==2)flag++;
			if(!flag)break;
		}
		Update(s1-2*a[y-1]-2*a[y]+a[i-1],0);
	}
	if(P[y]==2&&P[y+1]==1){//)(->##
		Update(s1-2*a[y-1]-a[y],0);
	}
	if(P[y]==1&&P[y+1]==2&&x==fx&&y==fy){//()->##
		Update(s1-a[y-1]-2*a[y],0);
	}
	if(P[y]==0&&P[y+1]!=0){//#(->#( && #(->#) && #)->#) && #)->)# 
		if(Map[x][y+1])Update(s1,val[x][y][0]);
		if(Map[x+1][y])Update(s1-P[y+1]*a[y]+P[y+1]*a[y-1],val[x][y][1]);
	}
	if(P[y]!=0&&P[y+1]==0){//(#->(# && (#->#( && )#->)# && )#->#)
		if(Map[x+1][y])Update(s1,val[x][y][1]);
		if(Map[x][y+1])Update(s1-P[y]*a[y-1]+P[y]*a[y],val[x][y][0]);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	a[0]=1;
	for(int i=1;i<=13;i++){
		a[i]=a[i-1]*3;
	}
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			Map[i][j]=1;
			fx=i;fy=j;
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			val[i][j][1]=read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			val[i][j][0]=read();
		}
	}
	num[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			k2=k1^1;num[k2]=0;//滚动数组 
			memset(Hash,0,sizeof(Hash));
			for(lst=1;lst<=num[k1];lst++){
				s1=data[k1][lst];//取出状态 
				Change(P,s1);//转为三进制 
				Shift(i,j);//更新 
			}
			k1=k2;
		}
		for(int j=1;j<=num[k2];j++){
			data[k2][j]*=3;//到下一行，状态后移一位 
		}
	}
	int ans=inf;
	for(int i=1;i<=num[k2];i++){
		ans=min(ans,f[k2][i]);
	}
	printf("%d\n",ans);
	return 0;
}