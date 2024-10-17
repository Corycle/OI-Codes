#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<stack>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
string a[5555];
int dzh(int x,int y){
	int i,j=0,k,s=0;
	for(i=0;i<=a[x].length()-1;i++){
		if(a[x][i]==a[y][j]){
			s++;j++;
		}
		else break;
	}
	return s;
}
	
int main(){
//	freopen("dzh.in","r",stdin);
//	freopen("dzh.out","w",stdout);
	int s=1,n=0;
	while(cin>>a[++n]);
	sort(a+1,a+n+1);
	s+=a[1].length();
	int i,j,k;
//	for(i=1;i<=n;i++)cout<<a[i]<<endl;
	for(i=2;i<=n;i++)
		s+=a[i].length()-dzh(i,i-1);
	cout<<s;
	return 0;
}