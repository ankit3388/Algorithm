#include<bits/stdc++.h>
#define ll long long int
#define llq _int128
using namespace std;
#define level 18
#define mod 100000000


void bfs_1(ll src,vector<vector<ll>>&adj, vector<ll>&parent, vector<ll>&distance,ll &tre,ll &back,ll &forw,ll &cross)
{
    queue<int> q;
    q.push(src);
    while (!q.empty())
    {
        ll u=q.front();
        q.pop();
        for (int v:adj[u])
        {
            if(distance[v]==-1)
            {
                distance[v]=distance[u] + 1;
                parent[v]=u;
                tre++;
                q.push(v);
            }
            else
            {
                if(parent[u] != v)
                {
                    if(distance[v]<distance[u]) back++;
                    else if(distance[v]>distance[u]) forw++;
                    else cross++;
                }
            }
        }
    }
}

void edg_diff(vector<vector<ll>>&adj,ll src)
{
        // Initialize all edges as tree edges.
    ll tre=0,forw=0,bac=0,cross=0;
    ll n=adj.size();
    vector<ll>parent(n, -1);
    vector<ll>distance(n, -1);
    distance[src]=0;
    bfs_1(src,adj,parent,distance,tre,bac,forw,cross);
    // cout<<endl;
    // for(ll i=1;i<n;i++) cout<<distance[i]<<" ";
    // cout<<endl;
    // cout<<tre<<" "<<bac<<" "<<forw<<" "<<cross;
    // cout<<endl;
    tre=0,forw=0,bac=0,cross=0;
    for (ll i=1;i<n;i++)
    {
        if(distance[i]==-1)
        {
            bfs_1(i,adj,parent, distance,tre,bac,forw,cross);
        }
    }
    for (ll i=1;i<n;i++)
    {
        for (auto v :adj[i])
        {
            int j = v;
            if (distance[j] < distance[i]) bac++;
            else if (distance[j] > distance[i]) forw++;
            else cross++;
        }
    }
    cout<<bac<<" "<<forw<<" "<<cross;
}
void print_bfs(vector<vector<ll>>&adj,ll src,ll total,ll qe)
{
    queue<ll>q;
    q.push(src);
    vector<ll>vis(adj.size(),0);
    vis[src]=1;
    ll n=adj.size();
    vector<ll>dis(n,0);
    dis[src]=0;
    ll tr_edge=0;
    ll total_edge=0;
    ll flag=0;
    while(!q.empty())
    {
        ll siz=q.size();
        if(flag==1)
        {
            cout<<siz<<" ";
        }
        for(ll i=0;i<siz;i++)
        {
             flag=1;
             ll node=q.front();
             q.pop();
            for(auto it:adj[node])
            {
                if(vis[it]!=1)
                {
                    tr_edge++;
                    dis[it]=dis[node]+1;
                    vis[it]=1;
                    q.push(it);
                }
            }
        }
        // cout<<endl;

    }
    if(qe==0) cout<<q.size()<<" "<<tr_edge<<" "<<total-tr_edge;
    else cout<<q.size()<<" "<<tr_edge<<" ";
    return ;

}

void print_dfs(vector<vector<ll>>&adj,int i,vector<ll>&vis,vector<ll>&st,vector<ll>&end,ll &count)
{
    vis[i]=1;
    //cout<<i<<" ";
    st[i]=count;
    count++;
    for(auto it:adj[i])
    {
        if(vis[it]!=1) print_dfs(adj,it,vis,st,end,count);
    }
    end[i]=count;
    count++;
}

void count_edge(vector<vector<ll>>&adj,int i,vector<ll>&vis,vector<ll>&st,vector<ll>&end,ll &tree,ll &forward,ll &backward,ll &cross)
{
    vis[i]=1;
    //cout<<i<<" "
    for(auto it:adj[i])
    {
        if(vis[it]!=1)
        {
            tree++;
            count_edge(adj,it,vis,st,end,tree,forward,backward,cross);
        }
        else
        {
            if(st[i] < st[it] && end[i] > end[it]) forward++;
            else if(st[i] > st[it] && end[i] > end[it]) cross++;
            else if(st[i] > st[it] && end[i] < end[it]) backward++;
        }
    }
}
void backedge(vector<vector<ll>>&adj,ll &count,vector<ll>&vis,ll i,ll parent,ll &forw,ll &tm)
{
    vis[i]=1;
    tm++;
    for(auto it:adj[i])
    {
        if(vis[it]==0)
        {
            forw++;
            backedge(adj,count,vis,it,i,forw,tm);
        }
        else if(it!=parent) count++;
    }
    tm++;
}
void topological_sorting(vector<vector<ll>>&adj)
{
    ll n=adj.size();
    // cout<<n;
    vector<ll>indegree(n,0);
    for(ll i=1;i<n;i++)
    {
        for(auto it:adj[i])
        {
            indegree[it]++;
        }
    }
    //for(ll i=1;i<n;i++) cout<<indegree[i]<<" ";
    priority_queue<ll,vector<ll>,greater<ll>>pq;
    for(ll i=1;i<n;i++)
    {
        if(indegree[i]==0)
        {
            pq.push(i);
        }
    }
    vector<ll>topo;
    while(!pq.empty())
    {
        ll node=pq.top();
        pq.pop();
        topo.push_back(node);
        for(auto it:adj[node])
        {
            indegree[it]--;
            if(indegree[it]==0)
            {
                pq.push(it);
            }
        }
    }
    if(topo.size()==n-1)
    {
        for(ll i=0;i<n-1;i++) cout<<topo[i]<<" ";
    }
    else cout<<-1;

    return;
}

bool detect_negative_wT_cycle(vector<vector<pair<ll,ll>>>&adj,ll src,ll n)
{
    vector<vector<ll>>edg;
    for(ll i=1;i<n;i++)
    {
        for(auto it:adj[i])
        {
            vector<ll>temp;
            temp.push_back(i);
            temp.push_back(it.first);
            temp.push_back(it.second);
            edg.push_back(temp);
        }
    }
    ll m=edg.size();
    vector<ll>dis(n,INT_MAX);
    dis[src]=0;
    for(ll i=1;i<n-1;i++)
    {
        for(ll j=0;j<m;j++)
        {
            ll wt=edg[j][2];
            if(dis[edg[j][0]]+wt < dis[edg[j][1]])
            {
                dis[edg[j][1]]=dis[edg[j][0]]+wt;
            }
        }
    }

    for(ll j=0;j<m;j++)
    {
        ll wt=edg[j][2];
        if(dis[edg[j][0]]+wt < dis[edg[j][1]])
        {
            dis[edg[j][1]]=dis[edg[j][0]]+wt;
            return true;
        }
    }
    return false;

}
void Dijkstra(vector<vector<pair<ll,ll>>>&adj,int src)
{

    int n=adj.size();
    vector<ll>dis(n,INT_MAX);
    if(detect_negative_wT_cycle(adj,src,n)==true)
    {
        cout<<-1;
        return ;
    }
    dis[src]=0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    pq.push({0,src});
    while(!pq.empty())
    {
        ll dist=pq.top().first;
        ll node=pq.top().second;
        pq.pop();
        for(auto it:adj[node])
        {
            ll wt=it.second;
            ll adjnode=it.first;
            if(dist+wt < dis[adjnode])
            {
                dis[adjnode]=dist+wt;
                pq.push({dis[adjnode],adjnode});
            }
        }
    }
    for(ll i=1;i<n;i++)
    {
        if(dis[i]==INT_MAX) cout<<999999<<" ";
        else cout<<dis[i]<<" ";
    }


}
void Bellman_ford(vector<vector<ll>>&edg,ll n,ll src)
{
    // for(ll i=0;i<edg.size();i++)
    // {
    //     cout<<edg[i][0]<<" "<<edg[i][1]<<" "<<edg[i][2]<<endl;
    // }
    ll m=edg.size();
    vector<ll>dis(n+1,INT_MAX);
    dis[src]=0;
    ll relax=0,realx_mod=0;
    //cout<<n<<"i";
    for(ll i=0;i<n-1;i++)
    {
        for(ll j=0;j<m;j++)
        {
            relax++;
            ll wt=edg[j][2];
            if(dis[edg[j][0]]!=INT_MAX && dis[edg[j][0]]+wt < dis[edg[j][1]])
            {
                dis[edg[j][1]]=dis[edg[j][0]]+wt;
                realx_mod++;
            }
        }
    }
    //for(ll i=1;i<=n;i++) cout<<dis[i]<<" ";
    ll flag=0;
    for(ll j=0;j<m;j++)
    {
        ll wt=edg[j][2];
        if(dis[edg[j][0]]!=INT_MAX && dis[edg[j][0]]+wt < dis[edg[j][1]])
        {
            dis[edg[j][1]]=dis[edg[j][0]]+wt;
            cout<<-1<<" ";
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        for(ll i=1;i<=n;i++)
        {
            if(dis[i]==INT_MAX) cout<<999999<<" ";
            else cout<<dis[i]<<" ";
        }
        cout<<relax<<" "<<realx_mod;
    }
    return ;


}
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ll t;
    cin>>t;
    while(t--)
    {
        ll q;
        cin>>q;
        if(q==1 || q==2)
        {
            ll n,D,src;
            cin>>n>>D>>src;
            vector<vector<ll>>matrix(n,vector<ll>(n,0));
            vector<vector<ll>>adj(n+1);
            ll total=0;
            for(ll i=0;i<n;i++)
            {
                for(ll j=0;j<n;j++)
                {
                    cin>>matrix[i][j];
                    if(matrix[i][j]==1)
                    {
                       adj[i+1].push_back(j+1);
                       total++;
                    }
                }
            }
            //cout<<n<<D<<src;
            // if(D==0)
            // {
            //     for(ll i=1;i<=n;i++)
            //     {
            //         sort(adj[i].begin(),adj[i].end());
            //     }
            // }

            if(D==1)
            {
                if(q==1)
                {
                    print_bfs(adj,src,total,D);
                    edg_diff(adj,src);
                }
                else
                {
                    // for(ll i=1;i<=n;i++)
                    // {
                    //     cout<<i<<"-{";
                    //     for(auto it:adj[i])
                    //     {
                    //         cout<<it<<" ";
                    //     }
                    //     cout<<"}"<<endl;
                    // }
                    vector<ll>st(n+1,0);
                    vector<ll>end(n+1,0);
                    ll count=1,tree=0,forward=0,backward=0,cross=0;
                    vector<ll>vis(n+1,0);
                    print_dfs(adj,src,vis,st,end,count);
                    // cout<<count<<" ";
                // cout<<count<<" ";
                    // count--;
                    cout<<--count<<" ";
                    vector<ll>vis1(n+1,0);
                    for(ll i=1;i<=n;i++)
                    {
                        if(vis[i]==0)
                        {
                            cout<<i<<" ";
                            print_dfs(adj,i,vis,st,end,count);
                        }
                    }
                    // vector<ll>vis1(n+1,0);
                    // for(ll i=1;i<=n;i++) cout<<st[i]<<" ";
                    // cout<<endl;
                    // for(ll i=1;i<=n;i++) cout<<end[i]<<" ";
                    // cout<<endl;
                    for(ll i=1;i<=n;i++) if(vis1[i]==0) count_edge(adj,i,vis1,st,end,tree,forward,backward,cross);
                    //cout<<endl;
                    cout<<tree<<" "<<backward<<" "<<forward<<" "<<cross;

                }
            }
            else
            {
                if(q==1)
                {
                    print_bfs(adj,src,total/2,D);
                }
                else
                {
                    vector<ll>vis(n+1,0);
                    ll count=0,forw=0,tm=1;
                    backedge(adj,count,vis,src,-1,forw,tm);
                    for(ll i=1;i<n;i++)
                    {
                        if(vis[i]==0) backedge(adj,count,vis,i,-1,forw,tm);
                    }
                    cout<<--tm<<" "<<forw<<" "<<count/2;
                }
            }

        }
        else if(q==3)
        {
            ll n;
            cin>>n;
            vector<vector<ll>>matrix(n,vector<ll>(n,0));
            vector<vector<ll>>adj(n+1);
            for(ll i=0;i<n;i++)
            {
                for(ll j=0;j<n;j++)
                {
                    cin>>matrix[i][j];
                    if(matrix[i][j]==1)
                    {
                        adj[i+1].push_back(j+1);
                    }
                }
            }
            //  cout<<adj.size();
           topological_sorting(adj);
        }
        else if(q==4)
        {
            ll n,D,src;
            cin>>n>>D>>src;
            vector<vector<ll>>matrix(n,vector<ll>(n,0));
            vector<vector<pair<ll,ll>>>adj(n+1);
            for(ll i=0;i<n;i++)
            {
                for(ll j=0;j<n;j++)
                {
                    cin>>matrix[i][j];
                    if(i!=j && matrix[i][j]!=999999)
                    {
                        if(D==1)
                        {
                            adj[i+1].push_back({j+1,matrix[i][j]});
                        }
                        else
                        {
                            adj[i+1].push_back({j+1,matrix[i][j]});
                            adj[j+1].push_back({i+1,matrix[i][j]});
                        }
                    }
                }
            }
           //cout<<q<<" ";
           //cout<<adj.size()<<" "<<src;
            Dijkstra(adj,src);
        }
        else if(q==5)
        {
            ll n,D,src;
            cin>>n>>D>>src;
            vector<vector<ll>>matrix(n,vector<ll>(n,0));
            vector<vector<ll>>edge;
            for(ll i=0;i<n;i++)
            {
                for(ll j=0;j<n;j++)
                {
                    cin>>matrix[i][j];
                    if(i!=j && matrix[i][j]!=999999)
                    {
                        if(D==1)
                        {
                            vector<ll>temp;
                            temp.push_back(i+1);
                            temp.push_back(j+1);
                            temp.push_back(matrix[i][j]);
                            edge.push_back(temp);
                        }
                        else
                        {
                            vector<ll>temp1;
                            temp1.push_back(i+1);
                            temp1.push_back(j+1);
                            temp1.push_back(matrix[i][j]);
                            edge.push_back(temp1);

                            vector<ll>temp2;
                            temp2.push_back(i+1);
                            temp2.push_back(j+1);
                            temp2.push_back(matrix[i][j]);
                            edge.push_back(temp2);

                        }
                    }
                }
            }
           Bellman_ford(edge,n,src);

        }
        cout<<endl;

    }
}