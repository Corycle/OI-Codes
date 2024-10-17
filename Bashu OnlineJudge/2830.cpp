#include<iostream>
#include<cstring>
using namespace std;
const int mod=7;
int a[3][3],b[3][3],w[3][3],n,A,B;
void gtz(int a[][3],int b[][3]){
	int i,j,k;
	memset(w,0,sizeof(w));
	for(i=1;i<=2;i++)
		for(j=1;j<=2;j++)
			for(k=1;k<=2;k++)
				w[i][j]=(w[i][j]+a[i][k]*b[k][j])%mod;
	memcpy(a,w,sizeof(w));
}
int main(){
	int i;
	cin>>A>>B>>n;
	if(n<3){
		cout<<1<<endl;
		return 0;
	}
	n-=2;
	a[1][1]=0,a[1][2]=B,a[2][1]=1,a[2][2]=A;
	b[1][1]=1,b[1][2]=0,b[2][1]=0,b[2][2]=1;
	while(n){
	    if(n%2)gtz(b,a);
		gtz(a,a);
		n/=2;	
	}
	cout<<(b[1][2]+b[2][2])%mod;
	return 0;
}