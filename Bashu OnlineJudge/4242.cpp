#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod1=39989;
const int Mod2=1e9;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans;
double k[N],b[N],Max;
struct Tree{int num;}t[N*4];
double GetY(int x,int num){return k[num]*x+b[num];}
void Update(int x,int y,int num,int p,int l,int r){
	if(y<l||x>r)return;
	int mid=(l+r)>>1;
	if(x<=l&&r<=y){
		if(GetY(l,num)<=GetY(l,t[p].num)&&GetY(r,num)<=GetY(r,t[p].num))return;
		if(GetY(l,num)>=GetY(l,t[p].num)&&GetY(r,num)>=GetY(r,t[p].num)){t[p].num=num;return;}
		if(k[num]>k[t[p].num]){
			if(GetY(mid,num)>GetY(mid,t[p].num)){
				Update(x,y,t[p].num,lson);
				t[p].num=num;
			}
			else Update(x,y,num,rson);
		}
		else{
			if(GetY(mid,num)>GetY(mid,t[p].num)){
				Update(x,y,t[p].num,rson);
				t[p].num=num;
			}
			else Update(x,y,num,lson);
		}
		return;
	}
	Update(x,y,num,lson);
	Update(x,y,num,rson);
}
void Ask(int x,int p,int l,int r){
	if(x<l||x>r)return;
	double dlt=GetY(x,t[p].num);
	if(Max<dlt){Max=dlt;ans=t[p].num;}
	if(Max==dlt)ans=min(ans,t[p].num);
	if(l==r)return;
	int mid=(l+r)>>1;
	Ask(x,lson);
	Ask(x,rson);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();
	while(m--){
		int op=read();
		if(op==0){
			int x=(read()+ans-1)%Mod1+1;
			ans=0;Max=-inf;
			Ask(x,1,1,1e5);
			printf("%d\n",ans);
		}
		if(op==1){
			n++;
			int X1=(read()+ans-1)%Mod1+1,Y1=(read()+ans-1)%Mod2+1;
			int X2=(read()+ans-1)%Mod1+1,Y2=(read()+ans-1)%Mod2+1;
			if(X1>X2){swap(X1,X2);swap(Y1,Y2);}
			if(X1==X2){k[n]=0;b[n]=max(Y1,Y2);}
			else{
				k[n]=(double)(Y1-Y2)/(X1-X2);
				b[n]=(double)Y1-X1*k[n];
			}
			Update(X1,X2,n,1,1,1e5);
		}
	}
	return 0;
}