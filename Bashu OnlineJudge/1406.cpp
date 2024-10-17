#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
#include<algorithm>  
#include<iostream>  
using namespace std;  
struct EDGE{int f,t,v;}a[100001];  
int ans=0,tot=0,N,M,fa[301]; 
bool cmp(EDGE X,EDGE Y){return X.v<Y.v;}  
int get(int x)
{
	if(fa[x]==x)return fa[x];
	else fa[x]=get(fa[x]);
	return fa[x];
}
int main()  
{  
      scanf("%d%d",&N,&M);  
      for(int i=1;i<=M;i++)  
            scanf("%d%d%d",&a[i].f,&a[i].t,&a[i].v);  
      sort(a+1,a+1+M,cmp);  
      for(int i=1;i<=N;i++)fa[i]=i;//初始化  
      for(int i=1;i<=M;i++)//选分值小的改造 
      {  
            int fx=get(fa[a[i].f]); //爸爸 
            int fy=get(fa[a[i].t]);  
            if(fx!=fy)  //不构成回路 
            {  
                  fa[fy]=fx;  //归 
                  ans=max(ans,a[i].v);  
                  tot++;  
            }  
            if(tot==N-1)break;//构成最小生成树  
      }
      printf("%d %d",tot,ans);
      return 0;  
}  