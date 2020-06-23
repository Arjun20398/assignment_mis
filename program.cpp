/*
cost = 106966.05, closelimit = 3
cost = 92866.56, closelimit = 4
cost = 88859.70, closelimit = 5
cost = 85690.97, closelimit = 6
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(a) memset(a,0,sizeof(a))
#define N 257
#define M 257
#define MAXCOST 1000000000
struct Path{
    double cost,perEmpCost;
    vector<int> path;
    Path():cost(0),perEmpCost(MAXCOST),path({}){}
};

double arr[N][M],fixedPrice=300,perKM=50,startKM=fixedPrice/perKM,limit=3,sum=0,closelimit=6;
vector<pair<double,int>> closest[N];
vector<vector<int>> ans;
int vis[N],counter[N];

double authenticate(vector<int> &path){
    double cost=fixedPrice;
    int last = 0;
    for(int num:path){
        cost+=(arr[last][num]*perKM);
        last=num;
    }
    return cost;
}

void findClose(int emp,int limit,vector<int>& emps){
    int ind=0;
    while(ind<closest[emp].size() && emps.size()<closelimit){
        if(vis[closest[emp][ind].second]==0){
            emps.push_back(closest[emp][ind].second);
        }
        ind++;
    }
}

void calculate(int last,int mask,int masksize,int size,vector<int> &emp,Path& tempans,double cost,vector<int> path){
    if(masksize == limit)
        return ;
    for(int ind=0;ind<size;ind++)
        if((mask & 1<<ind) == 0){
            mask|=(1<<ind);
            cost+=perKM*arr[last][emp[ind]];
            path.push_back(emp[ind]);
            if((mask & 1) && tempans.perEmpCost>cost/path.size()){
                tempans.cost = cost;
                tempans.perEmpCost = cost/path.size();
                tempans.path = path;
            }
            calculate(emp[ind],mask,masksize+1,size,emp,tempans,cost,path);
            mask-=(1<<ind);
            cost-=perKM*arr[last][emp[ind]];
            path.pop_back();
    }
}

void findpath(vector<int>& emp){
    int size=emp.size(),mask=0;
    Path tempPath = Path();
    calculate(0,mask,0,size,emp,tempPath,fixedPrice,vector<int>());
    sum+=tempPath.cost;
    cout<<tempPath.cost<<" : ";
    //cout<<authenticate(tempPath.path)<<"-> : ";
    for(int num:tempPath.path)
        vis[num]=1,cout<<num<<" ";
    cout<<"\n";
}

void showClosest(){
    for(int i=1;i<N;i++){
        for(auto it:closest[i])
            cout<<it.second<<" ";
        cout<<"\n";
    }
}

string allConsidered(){
    for(int i=1;i<N;i++)
        if(vis[i]==0)
            return "NO";
    return "YES";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cout<<fixed<<setprecision(2);
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++){
            cin>>arr[i][j];
            if(j!=0 && i!=j && arr[i][j]<arr[0][j]+startKM){
                closest[i].push_back({arr[i][j],j});
            }
        }
    mem(vis);
    mem(counter);
    for(int i=1;i<N;i++)
        if(vis[i]==0){
        vector<int> emps(1,i);
        findClose(i,limit,emps);
        findpath(emps);      
    } 
    cout<<"final cost  : "<<sum<<"\n";
    cout<<"All employees considered : "<<allConsidered()<<"\n";
    return 0;
}