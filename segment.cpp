#include<bits/stdc++.h>
using namespace std;

vector<int>A;
vector<int>T;

void create(int node,int start,int end)
{
	if(start==end)
	{
		T[node]=A[start];
		return;
	}
	else
	{
		int mid=(end+start)/2;
		create(2*node,start,mid);
		create(2*node+1,mid+1,end);
	}
	T[node]=min(T[2*node],T[2*node+1]);
}
void update(int node,int start,int end,int targetIndex,int val)
{
	if(start==end)
	{
		A[targetIndex]=val;
		T[node]=val;
		return;
	}
	else
	{
		int mid=(end+start)/2;
		if(start<=targetIndex&&targetIndex<=mid)
		{
			update(2*node,start,mid,targetIndex,val);
		}
		else
		{
			update(2*node+1,mid+1,end,targetIndex,val);
		}
	}
	T[node]=min(T[2*node],T[2*node+1]);
}
int ask(int node,int start,int end,int L,int R)
{
	if(R<start||L>end)
	return INT_MAX;
	if(L<=start&&end<=R)
	{
		return T[node];
	}
	int mid=(end+start)/2;
	int p1=ask(2*node,start,mid,L,R);
	int p2=ask(2*node+1,mid+1,end,L,R);
	return min(p1,p2);
}
int main()
{
	//code
	A.clear();
	T.clear();
	int N,Q;
	cin>>N>>Q;
	A.resize(N,0);
	for(int i=0;i<N;i++)
	{
		cin>>A[i];
	}
	T.resize(4*N,INT_MAX);
	create(1,0,N-1);
	vector<vector<int>>query(Q,vector<int>(3,0));
	for(int i=0;i<Q;i++)
	{
	    string q,l,r;
	    cin>>q>>l>>r;
	    if(q=="q")
	    {
    	    query[i][0]=0;
    		query[i][1]=stoi(l);
    		query[i][2]=stoi(r);
	    }
	    else
	    {
	        query[i][0]=1;
    		query[i][1]=stoi(l);
    		query[i][2]=stoi(r);
	    }
		//cout<<query[i][0]<<query[i][1]<<query[i][2]<<endl;
	}
	for(int i=0;i<Q;i++)
	{
	    if(query[i][0]==0)
	    {
	        int L=query[i][1];
	        int R=query[i][2];
	        int rslt=ask(1,0,N-1,L-1,R-1);
	        cout<<rslt<<endl;
	    }
	    else
	    {
	        update(1,0,N-1,query[i][1]-1,query[i][2]);
	    }
	}

	//code
	return 0;
}
