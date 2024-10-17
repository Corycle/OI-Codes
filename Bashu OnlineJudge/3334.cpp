#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int M=2000005;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,ans,head,Min,Max;
int st[N],vis[N],pre[N],nxt[N],sum[M];
struct Triangle{int x,y,d,l,r;}a[N];
bool cmp(Triangle A,Triangle B){
	if(A.y!=B.y)return A.y<B.y;
	return A.l<=B.l&&B.r<=A.r;//前面的三角形完全包含后面的三角形 
}
bool Compare(Triangle A,Triangle B){
	return A.l<=B.l&&B.r<=A.r;//前面的三角形完全包含后面的三角形 
}
void Delete(int x){
	vis[x]=0;
	if(head==x)head=nxt[x];
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();a[i].y=read();a[i].d=read();
		a[i].l=a[i].x;a[i].r=a[i].x+a[i].d;//底面长度 
		vis[i]=1;nxt[i]=i+1;pre[i]=i-1;//链表 
		Max=max(Max,a[i].y+a[i].d);
		Min=min(Min,a[i].y);
	}
	sort(a+1,a+n+1,cmp);
	int len=0,k=0;head=1;
	for(int i=head;i<=n&&a[i].y==Min;i=nxt[i]){
		for(int j=a[i].l;j<a[i].r;j++){
			if(!sum[j])len++;sum[j]++;
		}
	}
	for(int i=Min+1;i<=Max;i++){
		int lst=len,top=0;
		for(int j=head;j<=n&&a[j].y<i;j=nxt[j]){
			a[j].r--;//因为向上挪了一层，就相当于宽度减小了1 
			if(a[j].r<a[j].l)Delete(j);
			else{
				if(sum[a[j].r]==1)len--;
				sum[a[j].r]--;
				st[++top]=j;
			}
		}
		ans+=lst+len;
		for(int j=head;j<=n&&a[j].y<=i;j=nxt[j]){
			if(a[j].y==i){
				for(k=1;k<=top;k++){
					if(vis[st[k]]==0)continue;
					if(Compare(a[st[k]],a[j])){Delete(j);break;}
					if(Compare(a[j],a[st[k]])){
						Delete(st[k]);
						for(int l=a[st[k]].l;l<a[st[k]].r;l++){
							if(sum[l]==1)len--;sum[l]--;
						}
					}
				}
				if(k==top+1){
					for(int l=a[j].l;l<a[j].r;l++){
						if(!sum[l])len++;sum[l]++;
					}
				}
			}
		}
	}
	printf("%.1lf",ans/2.0);
	return 0;
}