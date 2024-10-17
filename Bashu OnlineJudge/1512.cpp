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
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
using namespace std; 
int x[62],x1[62],x2[62],y[62],y3[62],y2[62],f[32010],n,m,a,b,q;
int main(){
	int i,j,k;
    cin>>n>>m;
    n/=10;
    for(int i=1;i<=m;i++){
        cin>>a>>b>>q;
        a/=10;
        if(q!=0){
            if(x1[q]==0){
				x1[q]=a;
				y3[q]=b;
			}
            else{
				x2[q]=a;
				y2[q]=b;
			}
        }
		else{
			x[i]=a;
			y[i]=b;
		}
    }
    for(i=1;i<=m;i++){
    	for(j=n;j>=x[i];j--){
            f[j]=max(f[j],f[j-x[i]]+x[i]*y[i]);
            if(j-x[i]-x1[i]>=0)
				f[j]=max(f[j],f[j-x[i]-x1[i]]+x[i]*y[i]+x1[i]*y3[i]);
            if(j-x[i]-x2[i]>=0)
				f[j]=max(f[j],f[j-x[i]-x2[i]]+x[i]*y[i]+x2[i]*y2[i]);
            if(j-x[i]-x1[i]-x2[i]>=0)
				f[j]=max(f[j],f[j-x[i]-x1[i]-x2[i]]+x[i]*y[i]+x1[i]*y3[i]+x2[i]*y2[i]);
        }
	}
    cout<<f[n]*10; 
    return 0;
}