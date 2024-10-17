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
const int Mod=19997;
const int M=20005;
const int N=15;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[2][M];
int n,m,lst,s1,fx,fy;
int k1,k2,t1,t2,p1,p2;
int MaP[N][N],data[2][M];
int num[2],a[N],P[N],Hash[M];
void Change(int x[],int y){
	int i=1;
	while(y){x[i++]=y%4;y/=4;}
	while(i<=m+1)x[i++]=0;
}
void Update(int s2){
	int i=s2%Mod;
	while(Hash[i]){
		if(data[k2][Hash[i]]==s2){
			f[k2][Hash[i]]+=f[k1][lst];
			return;
		}
		i=(i+1)%Mod;
	}
	Hash[i]=++num[k2];
	data[k2][Hash[i]]=s2;
	f[k2][Hash[i]]=f[k1][lst];
}
//#()*
//0123
int Get_I1(int y){
	int flag=1,i;
	for(i=y+2;i<=m+1;i++){
		if(P[i]==1)flag++;
		if(P[i]==2)flag--;
		if(!flag)break;
	}
	return i;
}
int Get_I2(int y){
	int flag=1,i;
	for(i=y-1;i>=1;i--){
		if(P[i]==1)flag--;
		if(P[i]==2)flag++;
		if(!flag)break;
	}
	return i;
}
void Shift(int x,int y){
	int indep=0;
	t1=P[y];p1=a[y-1];
	t2=P[y+1];p2=a[y];
	for(int i=1;i<=m+1;i++){
		if(P[i]==3)indep++;
	}
	if(t1==0&&t2==0){//1.1
		if(x<n&&y<m)Update(s1+p1+2*p2);
		if(x<n&&indep<2)Update(s1+3*p1);
		if(y<m&&indep<2)Update(s1+3*p2);
	}
	if(t1==3&&t2==3&&x==n&&y==m){//2.1
		Update(s1-p1*t1-p2*t2);
	}
	if((t1==3&&t2==1)||(t1==1&&t2==3)){//2.2.1
		int i=Get_I1(y);
		Update(s1-t1*p1-t2*p2+a[i-1]);
	}
	if((t1==3&&t2==2)||(t1==2&&t2==3)){//2.2.2
		int i=Get_I2(y);
		Update(s1-t1*p1-t2*p2+2*a[i-1]);
	}
	if(t1==2&&t2==1){//)( => ##
		Update(s1-t1*p1-t2*p2);
	}
	if(t1==1&&t2==1){//(( => ##
		int i=Get_I1(y);
		Update(s1-p1*t1-p2*t2-a[i-1]);
	}
	if(t1==2&&t2==2){//)) => ##
		int i=Get_I2(y);
		Update(s1-t1*p1-t2*p2+a[i-1]);
	}
	if(t1>0&&t2==0){//3.1
		if(x<n)Update(s1);
		if(y<m)Update(s1-p1*t1+p2*t1);
		if(t1==1&&indep<2){//3.1.1
			int i=Get_I1(y);
			Update(s1-t1*p1+a[i-1]);
		}
		if(t1==2&&indep<2){//3.1.2
			int i=Get_I2(y);
			Update(s1-t1*p1+2*a[i-1]);
		}
		if(t1==3&&x==n&&y==m){//3.1.3
			Update(s1-t1*p1);
		}
	}
	if(t1==0&&t2>0){//3.2
		if(y<m)Update(s1);
		if(x<n)Update(s1-t2*p2+t2*p1);
		if(t2==1&&indep<2){//3.2.1
			int i=Get_I1(y);
			Update(s1-t2*p2+a[i-1]);
		}
		if(t2==2&&indep<2){//3.2.2
			int i=Get_I2(y);
			Update(s1-t2*p2+2*a[i-1]);
		}
		if(t2==3&&x==n&&y==m){//3.2.3
			Update(s1-t2*p2);
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	a[0]=1;
	for(int i=1;i<=12;i++){
		a[i]=a[i-1]*4;
	}
	n=read();m=read();
	num[0]=f[0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			k2=k1^1;num[k2]=0;
			memset(Hash,0,sizeof(Hash));
			for(lst=1;lst<=num[k1];lst++){
				s1=data[k1][lst];
				Change(P,s1);
				Shift(i,j);
			}
			k1=k2;
		}
		for(int j=1;j<=num[k2];j++){
			data[k2][j]*=4;
		}
	}
	ll ans=0;
	for(int i=1;i<=num[k2];i++){
		ans+=f[k2][i];
	}
	printf("%lld",ans);
	return 0;
}