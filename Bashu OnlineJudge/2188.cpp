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
using namespace std;
//struct _{};
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
double k[40005];
int n,x[205],y[205],k1;
int main(){
//	freopen("game.in","r",stdin);
//	freopen("game.out","w",stdout);
	int i,j,l,fl;
	cin>>n;
	double f;
	for(i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	for(i=1;i<=n;i++){
		for(j=i+1;j<=n;j++){
			if(x[j]==x[i])f=0;
			else if(y[j]==y[i])f=0xffff;
			else f=double(y[j]-y[i])/(x[j]-x[i]);
			fl=1;
			for(l=1;l<=k1;l++){
				if(k[l]==f){
					fl=0;break;
				}
			}
			if(fl==1){
				k1++;
				k[k1]=f;
			}
		}
	}
	cout<<k1<<endl;
	return 0;
}
