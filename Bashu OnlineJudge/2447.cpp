#include<iostream>
using namespace std;
string s;
int i,j,len,k;
long long ans;
long long C(int n,int r)
{  int i;long long cc=1;
   for(i=1;i<=r;i++)cc=cc*(n+1-i)/i;
   return cc;
}
int main()
{  cin>>s;
   len=s.length(); //求长度
   ans=1;
   for(i=1;i<len;i++)ans+=C(26,i);//加上长为1-(len-1)所有串后编码
   for(i=0;i<len;i++) //计算零头
   {  if(i>0&&s[i]<=s[i-1]){ans=0;break;}//特殊情况，即不在字母表中
      for(j=k;j<s[i]-'a';j++)ans+=C(26-j-1,len-i-1);
      k=s[i]-'a'+1;
   }
   cout<<ans<<endl;
}
