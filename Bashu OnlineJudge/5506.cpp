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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=200005;
const int M=20;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,K;
int low(int x){
	while(x%K==0)x/=K;
	return x%K;
}
int lowbit(int x){
	int tmp=0;
	while(x%K==0){x/=K;tmp++;}x%=K;
	while(tmp--)x*=K;
	return x;
}

/*========Segment Tree========*/
//Point:²»ÔÚÁ´ÉÏµÄµã 
//Chain:Á´ÉÏµÄµãµÄ¸üÐÂ£¨ÒÔÁ´Í·µÄµãÖµÎª¸ù£©
int root;
map<int,int>Root;
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*60];
	void Update(int x,int y,int z,int &p,int l,int r){
		if(!p)p=++tot;
		if(x<=l&&r<=y){t[p].sum^=z;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Update(x,y,z,lson);
		if(y>mid) Update(x,y,z,rson);
	}
	int Query(int x,int p,int l,int r){
		if(x<l||x>r||!p)return 0;
		if(l==r)return t[p].sum;
		int mid=(l+r)>>1;
		return t[p].sum^Query(x,lson)^Query(x,rson);
	}
}Point,Chain;

/*========Operation========*/
//p[i]:iÖÐ2µÄÃÝ´Î 
//num[i]:iËùÔÚÁ´µÄÑ­»·³¤¶È 
//tim[i]:iËùÔÚÁ´ÉÏµÄ½øÎ»´ÎÊý 
//to[i][j]:iÏòÇ°Ìøj²½Ìøµ½µÄµã 
//go[i][j]:iÏòÇ°Ìøj²½µÄ½øÎ»´ÎÊý 
//k½øÖÆÏÂ£¬µ±ÇÒ½öµ±low(x)ÖÐº¬µÄ2µÄÃÝ´Î´óÓÚµÈÓÚkÖÐ°üº¬µÄ2µÄÃÝ´Î£¬xÔÚÕýÍ³Á´ÉÏ¡£
bool vis[N];
int fst,dis;
int a[N],p[N],num[N],tim[N],go[N][M],to[N][M];
void Prepare(){
	for(int i=1;i<=K;i++){
		int j=i;
		while(!(j&1)){j/=2;p[i]++;}
	}
	for(int i=1;i<K;i++){
		if(vis[i]||p[i]<p[K])continue;
		int cnt=0,w=0;
		int x=i*2%K;a[++cnt]=i;vis[i]=1;
		while(x!=i){a[++cnt]=x;vis[x]=1;x=x*2%K;}
		for(int j=1;j<=cnt;j++)w+=(a[j]*2>=K);
		for(int j=1;j<=cnt;j++){
			num[a[j]]=cnt;tim[a[j]]=w;
			if(j==1)x=cnt;else x=j-1;
			to[a[j]][0]=a[x];
			go[a[j]][0]=(a[x]*2>=K);
		}
		for(int j=1;j<M;j++){
			for(int k=1;k<=cnt;k++){
				to[a[k]][j]=to[to[a[k]][j-1]][j-1];
				go[a[k]][j]=go[to[a[k]][j-1]][j-1]+go[a[k]][j-1];
			}
		}
	}
}
void Find(int x){//ÇóÁ´Í· 
	int tmp=0,t=0;
	while(x%K==0){x/=K;tmp++;}
	fst=low(x);dis=1;t=(x-fst)/K;//t:xµÄ½øÎ»´ÎÊý 
	dis+=t/tim[fst]*num[fst];t%=tim[fst];
	//dis=ÌøÍêµÄ»·Êý*»·µÄ³¤¶È+Ã»ÌøÍêµÄ³¤¶È£¨Ã»ÌøÍêÕû¸ö»·£© 
	for(int i=M-1;i>=0;i--){
		if(go[fst][i]<=t){
			dis+=(1<<i);
			t-=go[fst][i];
			fst=to[fst][i];
		}
	}
	while(tmp--)fst*=K;
	//ÓÉlow(x)µÄÁ´Í·»¹Ô­»ØÈ¥xµÄÁ´Í· 
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();Prepare();
	while(m--){
		int op=read(),x=read();
		if(op==1){
			int v=read();
			while(p[low(x)]<p[K]&&x<=n){
				Point.Update(x,x,v,root,1,n);
				x+=lowbit(x);//Ã»ÔÚÕýÍ³Á´ÉÏ£¬±©Á¦Ìø 
			}
			if(x<=n){//´¦ÀíÕýÍ³Á´ÉÏµÄÇé¿ö 
				Find(x);
				Chain.Update(dis,n,v,Root[fst],1,n);
			}
		}
		if(op==2){
			int Ans=0;
			while(x){
				if(p[low(x)]<p[K])Ans^=Point.Query(x,root,1,n);
				else{//´¦ÀíÕýÍ³Á´ÉÏµÄÇé¿ö 
					Find(x);
					Ans^=Chain.Query(dis,Root[fst],1,n);
				}
				x-=lowbit(x);
			}
			printf("%d\n",Ans);
		}
	}
	return 0;
}