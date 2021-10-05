#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;
int hi(int p){
	return p<<1;
}
int hd(int p){
	return (p<<1)+1;
}
void f(int n,vector<int>&a){
a[n]=a[hi(n)]+a[hd(n)];
}
void build(vector<int>&l,vector<int>&a,int n,int L,int R){
	if(L<R){
    int mid=L+(R-L)/2;
		build(l,a,hi(n),L,mid);
		build(l,a,hd(n),mid+1,R);
		f(n,a);
	}
	else{
		a[n]=l[L];
	}
}
void pop(vector<int>&a,vector<int>&v,int n,int L,int R){
	if(L!=R){
		a[hd(n)]+=v[n];
		v[hd(n)]+=v[n];
		a[hi(n)]+=v[n];
		v[hi(n)]+=v[n];
		v[n]=0;
	}
	else{
		v[n]=0;
	}
}
void change(vector<int>&a,int n,int L,int R,int su,int st,int fi,vector<int>&v){
	if(L>fi ||R<st)return;
	if(L>=st && R<=fi){
		a[n]+=su;
		v[n]+=su;
	}
	else{
		pop(a,v,n,L,R);
		int mid=L+(R-L)/2;
		change(a,hi(n),L,mid,su,st,fi,v);
		change(a,hd(n),mid+1,R,su,st,fi,v);
		f(n,a);
	}
}
int valor(vector<int>&a,int n,int L,int R,int st,int fi,vector<int>&v){
	if(L>=st && R<=fi){
		pop(a,v,n,L,R);
		return a[n];
	}
	else if(fi<L||R<st)return 0;
	else{
		pop(a,v,n,L,R);
		int mid=L+(R-L)/2;
		int v1=valor(a,hi(n),L,mid,st,fi,v);
		int v2=valor(a,hd(n),mid+1,R,st,fi,v);
    return v1+v2;
	}
}
long long count_swaps(vector<int> S){
int n=0;
for(int i=0;i<S.size();i++)n=max(S[i],n);
n++;
vector<queue<int> >neg(n);
vector<queue<int> >p(n);
vector<int>l(S.size());
for(int i=0;i<S.size();i++){
l[i]=i;
if(S[i]<0){
    neg[-1*S[i]].push(i);
}
else{
    p[S[i]].push(i);
}
}
int m=S.size();
vector<int>a(4*m,0);
vector<int>va(4*m,0);
build(l,a,1,0,m-1);
vector<bool>v(m,false);
long long ans=0;
for(int i=0;i<m;i++){
   //cout<<ans<<"\n";
    if(!v[i]){
        v[i]=true;
        int x=valor(a,1,0,m-1,i,i,va);
        int y;
        if(S[i]>0){
            ans++;
            y=neg[S[i]].front();
            neg[S[i]].pop();
            p[S[i]].pop();
        }
        else{
            y=p[-1*S[i]].front();
            p[-1*S[i]].pop();
            neg[-1*S[i]].pop();
        }
        int x2=valor(a,1,0,m-1,y,y,va);
        x2=min(m-1,x2);
        x=min(m-1,x);
        ans+=x2-x-1;
        change(a,1,0,m-1,1,i,y,va);
        //cout<<x<<" "<<x2<<"\n";
        v[y]=true;
    }
}
return ans;
}

int main(){
    int n;
    cin>>n;
    vector<int>s(2*n);
    for(int i=0;i<2*n;i++)cin>>s[i];
    cout<<count_swaps(s);
}