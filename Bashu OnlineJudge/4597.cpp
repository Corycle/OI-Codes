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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[2],p[2005],root[2005],tot;
int point[2],score[2];
struct tree{
	int l,r;
	int dis,data;
}t[N];
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].data<t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	if(!t[x].r)t[x].dis=0;
	else t[x].dis=t[t[x].r].dis+1;
	return x;
}
int main(){
//	freopen("duliu.in","r",stdin);
//	freopen("duliu.out","w",stdout);
	int T;
	while(scanf("%d",&T)!=EOF){
		score[0]=score[1]=0;
		while(T--){
			n=read();m=read();
			a[0]=a[1]=tot=0;
			point[0]=point[1]=0;
			memset(t,0,sizeof(t));
			memset(p,0,sizeof(p));
			memset(root,0,sizeof(root));
			for(int i=1;i<=m;i++)p[i]=read();
			for(int i=1;i<=m;i++){
				for(int j=1;j<=p[i];j++){
					t[++tot].data=read();
					root[i]=Merge(root[i],tot);
				}
			}
			//0 Wolf , 1 Sheep
			int d=1;
			while(n--){
				char s[2];
				scanf("%s",s);
				d=d^1;
				if(s[0]=='T'){
					int x=read();
					a[d]=Merge(a[d],root[x]);
					point[d]+=p[x];
				}
				if(s[0]=='C'){
					if(t[a[0]].data==t[a[1]].data)continue;
					int k=(t[a[1]].data>t[a[0]].data);//大的那个
					a[k]=Merge(a[k],a[k^1]);
					point[k]+=point[k^1];
					point[k^1]=a[k^1]=0;
				}
				if(s[0]=='L'){
					a[d]=Merge(t[a[d]].l,t[a[d]].r);
					point[d]--;
//					if(point[d]==0)a[d]=0;
				}
				if(s[0]=='A'){
					int x=read();
					t[a[d]].data+=x;
				}
				if(s[0]=='E'){
					int x=read();
					t[++tot].data=x;
					a[d]=Merge(t[a[d]].l,t[a[d]].r);
					a[d]=Merge(a[d],tot);
				}
			}
			printf("%d:%d\n",point[0],point[1]);
			if(point[0]<point[1])score[1]++;
			else score[0]++;
		}
		if(score[0]<=score[1])printf("I will be back!!\n");
		else printf("Hahaha...I win!!\n");
	}
	return 0;
}