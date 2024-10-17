#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int p[50005],r[50005],n;
int f1(int x){  
	if(x!=p[x]){  
		int fx=f1(p[x]);
		r[x]=(r[x]+r[p[x]])%3;
		p[x]=fx;//路径压缩 
	}
	return p[x];
}
bool dzh(int d,int x,int y){
	int fx=f1(x),fy=f1(y);
	if(fx==fy){
		if((r[y]-r[x]+3)%3!=d)return 1;
		else return 0;
	}
	p[fy]=fx;//路径压缩 
	r[fy]=(r[x]-r[y]+d+3)%3;
	return 0;
}
main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	int d,x,y,ans=0;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)p[i]=i,r[i]=0;
	while(k--){
		scanf("%d%d%d",&d,&x,&y);
		if(x>n||y>n||(x==y&&d==2)){
			ans++;
			continue;
		}
		if(dzh(d-1,x,y))ans++;
	}
	printf("%d",ans);
	return 0;
}
/*
1.p[x]表示x根结点。r[x]表示p[x]与x关系。r[x]=0 表示p[x]与x同类；1表示p[x]吃x；2表示x吃p[x]。
2.怎样划分一个集合呢？
  注意，这里不是根据x与p[x]是否是同类来划分。而是根据“x与p[x]能否确定两者之间关系”来划分，若能确定x与p[x]关系，则它们同属一个集合
3.怎样判断一句话是不是假话？
  假设已读入D ,X ,Y ,先利用f1()函数得到X,Y所在集合代表元素fx,fy,若它们在同一集合（即fx==fy）则可以判断这句话真伪：
        若 D==1 而 r[X]!=r[Y] 则此话为假.（D==1 表示X与Y为同类，而从r[X]!=r[Y]可以推出 X 与 Y 不同类.矛盾.）
        若 D==2 而 r[X]==r[Y]（X与Y为同类）或者r[X]==(r[Y]+1)%3（Y吃X）则此话为假。
4.上个问题中r[X]==(r[Y]+1)%3这个式子怎样推来？
      假设有Y吃X，那么r[X]和r[Y]值是怎样？
　       我们来列举一下: 
		           r[X]=0&&r[Y]=2 
                           r[X]=1&&r[Y]=0
                           r[X]=2&&r[Y]=1
          稍微观察一下就知道r[X]=(r[Y]+1)%3;
      事实上，对于上个问题有更一般判断方法：
           若(r[Y]-r[X]+3)%3!=D-1 ,则此话为假.
5.其他注意事项:
       dzh(d,x,y)过程中若将S(fy)合并到S(fx)上，则相应r[fy]必须更新为fy相对于fx关系。怎样得到更新关系式？
       r[fy]=(r[x]-r[y]+d+3)%3;
*/