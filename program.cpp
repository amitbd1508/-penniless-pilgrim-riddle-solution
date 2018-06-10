
#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > g;

void printpath(vector<pair<int,int>>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i].second << " ";
    cout << endl;
}
double getTax(double currentTax,int start,int end){

    if(start-1==end) return currentTax-2;
    if(start+1==end) return currentTax+2;
    if(start-5==end) return currentTax/2.0;
    if(start+5==end) return currentTax*2.0;


    return currentTax;

}

bool hasZeroCost(vector<pair<int,int>>& path)
{

    int size = path.size();
    double tax=4;
    //cout<<"path size "<<size<<"=> ";
    for (int i = 0; i < size-1; i++)
    {
        tax=getTax(tax,path[i].second,path[i+1].second);
        //cout<<path[i]<<"-"<<path[i+1]<<":"<<tax<<endl;
    }
    //cout<<endl<<endl;
    if(tax==0) return true;
    return false;
}

int isNotVisited(int x,int y, vector<pair<int,int>>& path)
{
    pair<int,int> p;
    p=make_pair(x,y);
    vector<pair<int,int> >::iterator it;
    for ( it = path.begin(); it != path.end(); ++it)
        if (*it == p)
            return 0;
    return 1;
}


void findpaths(vector<vector<int> >&g, int src,int dst, int v)
{
    queue<vector<pair<int,int>>> q;
    vector<pair<int,int>> path;
    path.push_back(make_pair(1,src));
    q.push(path);
    while (!q.empty()) {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1].second;

        if (last == dst && hasZeroCost(path))
            printpath(path);

        for (int i = 0; i < g[last].size(); i++) {
            if (isNotVisited(last,g[last][i], path)) {
                vector<pair<int,int>> newpath(path);
                newpath.push_back(make_pair(last,g[last][i]));
                q.push(newpath);
            }
        }
    }
}

void addEdge(int u,int  v)
{
    g[u].push_back(v);
}

void create_graph()
{
    for(int j=0;j<5;j++)
    {
        for(int i=j*5;i<((j+1)*5)-1;i++)
        {
            if(i!=0&&i!=1)
            {
                addEdge(i,i+1);
                addEdge(i+1,i);
            }

        }
    }

    for(int j=0;j<20;j+=5)
    {
        for(int i=j;i<j+5;i++)
        {
            addEdge(i,i+5);
            addEdge(i+5,i);
        }
    }

}
void printGraph()
{
    for(int i=0;i<25;i++)
    {
        cout<<i<<" => ";
        for(int j=0;j<g[i].size();j++)
        {
            cout<<g[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{

    int v = 25;
    g.resize(25);

    create_graph();
    printGraph();

    int src = 2, dst = 24;
    cout << "path from " << src
         << " to  " << dst << ": "<<endl;

    findpaths(g, src, dst, v);

    return 0;
}
