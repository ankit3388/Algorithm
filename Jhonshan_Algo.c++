#include<bits/stdc++.h>
#define ll long long int
#define llq _int128
using namespace std;
#define level 18
#define mod 1000000007
// #define k 1000002
class Binary_Heap{
    private:
        ll parent(ll i)
        {
            return i/2;
        }
        ll left_child(ll i)
        {
            return 2*i;
        }
        ll right_child(ll i)
        {
            return 2*i+1;
        }
   public:
        void heap_push(vector<pair<ll,ll>>&v,ll x,ll y)
        {
            v.push_back({x,y});
            ll n=v.size();
            ll temp=n-1;
            while(temp>0)
            {
                if(v[parent(temp)]>v[temp])
                {
                    swap(v[parent(temp)],v[temp]);
                    temp=parent(temp);
                }
                else return ;

            }
            return ;

        }
        void heap_pop(vector<pair<ll,ll>>&v)
        {
            if(v.size()==0) return ;
            ll n=v.size();
            ll temp=n-1;
            v[0]=v[temp];
            v.pop_back();
            ll root=0;
            while(root>=n)
            {
                int update=root;
                if(right_child(root) > v.size() && v[root] >v[right_child(root)])
                {
                    update=right_child(root);
                }
                if(left_child(root)>v.size() && v[root]>v[left_child(root)])
                {
                    update=left_child(root);
                }
                if(root!=update)
                {
                    swap(v[root],v[update]);
                    root=update;
                }
                else return ;
            }
            return ;
        }

};


class Binomial_heap
{
    public:
        int degree;
        int data;
        int node;
        Binomial_heap *child,*parent,*sibling;
    public:
        Binomial_heap(int data,int node)
        {
            degree=0;
            this->data=data;
            this->node=node;
            child=NULL;
            parent=NULL;
            sibling=NULL;
        }
        Binomial_heap *reverse_root(Binomial_heap *head)
        {
            if(head==NULL) return NULL;

            if(head->sibling == NULL) return head;

            Binomial_heap *curr=reverse_root(head->sibling);
            curr->sibling->sibling=head;
            curr->sibling=NULL;
            return curr;
        }
        Binomial_heap *union_op(Binomial_heap *heap1,Binomial_heap *heap2)
        {
            if(heap1==NULL) return heap2;
            if(heap2==NULL) return heap1;
            Binomial_heap *updated_heap=NULL;
            Binomial_heap *temp1=heap1, *temp2=heap2;


            if(temp1->degree > temp2->degree)
            {
                updated_heap=temp2;
                temp2=temp2->sibling;
            }
            else
            {
                updated_heap=temp1;
                temp1=temp1->sibling;
            }
            Binomial_heap *head=updated_heap;
            while(temp1!=NULL && temp2!=NULL)
            {
                if(temp1->degree > temp2->degree)
                {
                    head->sibling=temp2;
                    temp2=temp2->sibling;
                }
                else
                {
                    head->sibling=temp1;
                    temp1=temp1->sibling;
                }
                head=head->sibling;

            }
            while(temp2!=NULL)
            {
                head->sibling=temp2;
                temp2=temp2->sibling;
                head=head->sibling;
            }
            while(temp1!=NULL)
            {
                head->sibling=temp1;
                temp1=temp1->sibling;
                head=head->sibling;
            }


            Binomial_heap *prev=NULL, *curr=updated_heap,*next=updated_heap->sibling;
            while(next!=NULL)
            {
                if(next->degree != curr->degree)
                {
                    prev=curr;
                    curr=curr->sibling;
                    next=next->sibling;
                }
                else
                {
                    if(next->sibling!=NULL && next->degree==next->sibling->degree)
                    {
                        prev=curr;
                        curr=curr->sibling;
                        next=next->sibling;
                    }
                    else
                    {
                         if(curr->data <= next->data)
                         {

                             curr->degree++;
                            curr->sibling=next->sibling;
                            next->parent=curr;
                            next->sibling=curr->child;
                            curr->child=next;
                            next=curr->sibling;
                         }
                         else
                         {
                            if(prev!=NULL)prev->sibling=curr->sibling;
                            else updated_heap=next;

                            curr->parent=next;
                            curr->sibling=next->child;
                            next->degree++;
                            curr=next;
                            next=next->sibling;


                         }
                    }
                }
            }
            return updated_heap;

        }

        Binomial_heap *get_min(Binomial_heap *head,Binomial_heap *&mini)
        {
            Binomial_heap *curr=head,*mini_node=head,*prev=NULL;

            Binomial_heap *updated_heap=head;
            mini=head;
            while(head->sibling!=NULL)
            {
                if(head->sibling->data < mini->data)
                {
                    // mini->data=head->sibling->data;
                    mini=head->sibling;
                    mini_node=head->sibling;
                    prev=head;
                }
                head=head->sibling;

            }
            if(prev==NULL)
            {
                if(mini_node->sibling==NULL)
                {
                    Binomial_heap *min_node2=mini_node->child;
                    curr=min_node2;
                    while(curr!=NULL)
                    {
                        curr->parent=NULL;
                        curr=curr->sibling;

                    }
                    min_node2=reverse_root(min_node2);
                    return min_node2;

                }
                else
                {
                    updated_heap=mini_node->sibling;
                }
            }
            else
            {
                prev->sibling=mini_node->sibling;

            }

            Binomial_heap *min_node2=mini_node->child;
            curr=min_node2;
            while(curr!=NULL)
            {
                curr->parent=NULL;
                curr=curr->sibling;

            }
            if(min_node2==NULL)
            {
                return updated_heap;
            }

            min_node2=reverse_root(min_node2);
            updated_heap=union_op(min_node2,updated_heap);
            return updated_heap;
        }




};
bool bellman_ford(vector<vector<pair<ll,ll>>>adj,ll src, vector<ll>&dis)
{
    ll n=adj.size()-1;
    vector<pair<ll,pair<ll,ll>>>edge;
    for(ll i=0;i<=n;i++)
    {
        for(auto it :adj[i])
        {
            edge.push_back({i,{it.first,it.second}});
        }
    }

    ll m=edge.size();
    //vector<ll>dis(n+1,INT_MAX);
    dis[src]=0;
    for(ll i=0;i<n-1;i++)
    {
        for(auto it :edge)
        {
            ll node=it.first;
            ll node2=it.second.first;
            ll wt=it.second.second;
            if(dis[node]!=999999 && dis[node]+wt <dis[node2])
            {
                dis[node2]=dis[node]+wt;
            }
        }
    }
    ll flag=0;
    for(auto it :edge)
    {
        ll node=it.first;
        ll node2=it.second.first;
        ll wt=it.second.second;
        if(dis[node]!=999999 && dis[node]+wt <dis[node2])
        {
            flag=1;
            break;
        }
    }
    if(flag==1) return -1;
    return 0;
}

vector<ll>dijkastra_array(vector<vector<pair<ll,ll>>>&adj,ll src)
{
    ll n=adj.size()-1;
    vector<ll>dis(n+1,999999);
    dis[src]=0;
    priority_queue<pair<ll,ll> ,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    pq.push({0,src});
    while(!pq.empty())
    {
        ll node=pq.top().second;
        ll dist=pq.top().first;
        pq.pop();
        for(auto it:adj[node])
        {
            ll adjedge=it.first;
            ll wt=it.second;
            if(dis[node]+wt< dis[adjedge])
            {
                dis[adjedge]=dis[node]+wt;
                pq.push({dis[adjedge],adjedge});
            }

        }
    }
    return dis;
}


vector<ll>dijkastra_Binary_heaop(vector<vector<pair<ll,ll>>>&adj,ll src)
{
    ll n=adj.size()-1;
    vector<ll>dis(n+1,999999);
    dis[src]=0;
    // priority_queue<pair<ll,ll> ,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    Binary_Heap pq;
    vector<pair<ll,ll>>vp;
    pq.heap_push(vp,0,src);
    while(vp.size()!=0)
    {
        ll node=vp[0].second;
        ll dist=vp[0].first;
        pq.heap_pop(vp);
        for(auto it:adj[node])
        {
            ll adjedge=it.first;
            ll wt=it.second;
            if(dis[node]+wt< dis[adjedge])
            {
                dis[adjedge]=dis[node]+wt;
                pq.heap_push(vp,dis[adjedge],adjedge);
            }

        }
    }
    return dis;
}

vector<ll>dijkastra_Binomial_heaop(vector<vector<pair<ll,ll>>>&adj,ll src)
{
    ll n=adj.size()-1;
    vector<ll>dis(n+1,999999);
    dis[src]=0;
    // priority_queue<pair<ll,ll> ,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    // vector<pair<ll,ll>>vp;
    Binomial_heap *pq=new Binomial_heap(0,src);
    ll mini=0;
    while(pq!=NULL)
    {
        Binomial_heap *find_min=new Binomial_heap(-1,0);
        Binomial_heap *temp=pq->get_min(pq,find_min);
        ll node=find_min->node;
        ll dist=find_min->data;
        //cout<<find_min->data<<"-"<<find_min->node;
        pq=temp;
        for(auto it:adj[node])
        {
            ll adjedge=it.first;
            ll wt=it.second;
            if(dis[node]+wt< dis[adjedge])
            {
                dis[adjedge]=dis[node]+wt;
                Binomial_heap *temp2=new Binomial_heap(dis[adjedge],adjedge);
                pq=pq->union_op(pq,temp2);
            }

        }
        //if(pq==NULL) cout<<"Yes";
    }
    return dis;
}

class Fibonacci_heap
{
    int value;
    int key;
    int rank;
    bool marked;
    Fibonacci_heap *child, *parent, *left, *right;

    Fibonacci_heap *decreaseFibonacci(Fibonacci_heap *heap, Fibonacci_heap *node)
    {
        if (!node->parent)
        {
            if (node->value < heap->value) return node;
            else return heap;
        }
        if (node->parent->value <= node->value) return heap;
        if (node->parent->child == node)
        {
            if (node->left == node)
            {
                node->parent->child = NULL;
            }
            else
            {
                node->parent->child = node->left;
            }
        }

        Fibonacci_heap *parent = node->parent;
        parent->rank--;
        node->left->right = node->right;
        node->right->left = node->left;
        node->parent = NULL;

        node->right = heap->right;
        node->left = heap;
        heap->right->left = node;
        heap->right = node;
        node->marked = false;
        if (node->value < heap->value)
        {
            heap = node;
        }
        if (!parent->marked)
        {
            if (parent->parent)
            {
                parent->marked = true;
            }
            return heap;
        }
    }
};

vector<ll>dijkastra_Fibonnci_heap(vector<vector<pair<ll,ll>>>&adj,ll src)
{
    ll n=adj.size()-1;
    //vector<ll>dis(n+1,999999);
    //dis[src]=0;
    // priority_queue<pair<ll,ll> ,vector<pair<ll,ll>>,greater<pair<ll,ll>>>pq;
    // vector<pair<ll,ll>>vp;
    vector<ll>dis=dijkastra_Binomial_heaop(adj,src);
    Binomial_heap *pq=new Binomial_heap(0,src);

    ll mini=0;
    ll c=0;
    while(c>1)
    {
       Binomial_heap *find_min=new Binomial_heap(-1,0);
        // Binomial_heap *temp=pq->get_min(pq,find_min);
        ll node=find_min->node;
        ll dist=find_min->data;
        //cout<<find_min->data<<"-"<<find_min->node;
        // pq=temp;
        for(auto it:adj[node])
        {
            ll adjedge=it.first;
            ll wt=it.second;
            if(dis[node]+wt< dis[adjedge])
            {
                dis[adjedge]=dis[node]+wt;
                // Binomial_heap *temp2=new Fibonacci_heap(dis[adjedge],adjedge);
                pq=pq->union_op(pq,pq);
            }

        }

        // if(pq==NULL) cout<<"Yes";
    }
    return dis;
}

int main(int argc, char **argv)
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    vector<double> execution_times;
    clock_t start, end;
    start = clock();
    ll t;
    cin>>t;
    while(t--)
    {
        ll n,d;
        cin>>n>>d;
    //    cout<<n<<d;
        vector<vector<pair<ll,ll>>>adj(n+1);
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<n;j++)
            {
                ll x;
                cin>>x;
                if(i!=j && x!=999999) adj[i+1].push_back({j+1,x});
            }
        }
        vector<vector<pair<ll,ll>>>add_zero=adj;
        for(ll i=0;i<n;i++)
        {
            add_zero[0].push_back({i+1,0});
        }
        vector<vector<pair<ll,ll>>>positive_wt=adj;
        vector<ll>bell_dis(n+1,999999);
        int check=bellman_ford(adj,0,bell_dis);
        if(check==1)
        {
            end = clock();
            execution_times.push_back((double)(end - start) / CLOCKS_PER_SEC);
            cout<<-1;
        }
        else
        {
            if(argc>1)
            {
                char choice=argv[1][0];
                if(choice==1)
                {
                    for(ll i=1;i<=n;i++)
                    {
                        vector<ll>bell_dis(n+1,999999);
                        int check=bellman_ford(adj,i,bell_dis);
                        if(check==1)
                        {
                            cout<<-1<<endl;

                        }
                        else
                        {
                            vector<ll>dijk_dis=dijkastra_array(adj,i);
                            {
                            // vector<ll>dijk_dis(n+1,999999);
                                for(ll j=1;j<=n;j++)
                                {
                                    // cout<<dijk_dis[i]<<" ";
                                    if(dijk_dis[j]!=999999)
                                    {
                                        dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                                    }
                                    cout<<dijk_dis[j]<<" ";
                                }
                                cout<<endl;
                            }
                        }
                    }
                }
                else if(choice==2)
                {

                    for(ll i=1;i<=n;i++)
                    {
                         vector<ll>bell_dis(n+1,999999);
                        int check=bellman_ford(adj,i,bell_dis);
                        if(check==1)
                        {
                            cout<<-1<<endl;
                        }
                        else
                        {
                            vector<ll>dijk_dis=dijkastra_Binary_heaop(adj,i);
                            // vector<ll>dijk_dis(n+1,999999);
                            for(ll j=1;j<=n;j++)
                            {
                                // cout<<dijk_dis[i]<<" ";
                                if(dijk_dis[j]!=999999)
                                {
                                    dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                                }
                                cout<<dijk_dis[j]<<" ";
                            }
                            cout<<endl;
                        }
                    }

                }
                else if(choice==3)
                {

                    for(ll i=1;i<=n;i++)
                    {
                        vector<ll>bell_dis(n+1,999999);
                        int check=bellman_ford(adj,i,bell_dis);
                        if(check==1)
                        {
                            cout<<-1<<endl;
                            continue;
                        }
                        else
                        {
                            vector<ll>dijk_dis=dijkastra_Binomial_heaop(positive_wt,i);
                            // vector<ll>dijk_dis(n+1,999999);
                            for(ll j=1;j<=n;j++)
                            {
                                // cout<<dijk_dis[i]<<" ";
                                if(dijk_dis[j]!=999999)
                                {
                                    dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                                }
                                cout<<dijk_dis[j]<<" ";
                            }
                            cout<<endl;
                        }
                    }

                }
                else if(choice==4)
                {

                    for(ll i=1;i<=n;i++)
                    {
                        vector<ll>bell_dis(n+1,999999);
                        int check=bellman_ford(adj,i,bell_dis);
                        if(check==1)
                        {
                            cout<<-1<<endl;
                            continue;
                        }
                        else
                        {
                            vector<ll>dijk_dis=dijkastra_Fibonnci_heap(adj,i);
                            // vector<ll>dijk_dis(n+1,999999);
                            for(ll j=1;j<=n;j++)
                            {
                                // cout<<dijk_dis[i]<<" ";
                                if(dijk_dis[j]!=999999)
                                {
                                    dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                                }
                                cout<<dijk_dis[j]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                }
                else
                {

                    for(ll i=1;i<=n;i++)
                    {
                        vector<ll>bell_dis(n+1,999999);
                        int check=bellman_ford(adj,i,bell_dis);
                        if(check==1)
                        {
                            cout<<-1<<endl;
                            continue;
                        }
                        else
                        {
                            vector<ll>dijk_dis=dijkastra_Fibonnci_heap(adj,i);
                            // vector<ll>dijk_dis(n+1,999999);
                            for(ll j=1;j<=n;j++)
                            {
                                // cout<<dijk_dis[i]<<" ";
                                if(dijk_dis[j]!=999999)
                                {
                                    dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                                }
                                cout<<dijk_dis[j]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                }

            }
            else
            {
                    // for(ll i=1;i<=n;i++)
                    // {
                    //     vector<ll>dijk_dis=dijkastra_Fibonnci_heap(positive_wt,i);
                    //     // vector<ll>dijk_dis(n+1,999999);
                    //     for(ll j=1;j<=n;j++)
                    //     {
                    //         // cout<<dijk_dis[i]<<" ";
                    //         if(dijk_dis[j]!=999999)
                    //         {
                    //             dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                    //         }
                    //         cout<<dijk_dis[j]<<" ";
                    //     }
                    //     cout<<endl;
                    // }
                for(ll i=1;i<=n;i++)
                {
                    vector<ll>bell_dis(n+1,999999);
                    int check=bellman_ford(adj,i,bell_dis);
                    if(check==1)
                    {
                        cout<<-1<<endl;
                        continue;
                    }
                    else
                    {
                        vector<ll>dijk_dis=dijkastra_Binary_heaop(adj,i);
                        {
                        // vector<ll>dijk_dis(n+1,999999);
                            for(ll j=1;j<=n;j++)
                            {
                                // cout<<dijk_dis[i]<<" ";
                                if(dijk_dis[j]!=999999)
                                {
                                    dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

                                }
                                cout<<dijk_dis[j]<<" ";
                            }
                            cout<<endl;
                        }
                    }
                }
            }
             //Print execution times
            // for(ll i=0;i<=n;i++)
            // {
            //     cout<<bell_dis[i]<<" ";
            // }
            // cout<<endl;
            // vector<ll>dijk_dis=dijkastra_array(adj,0);
            // for(ll i=0;i<=n;i++)
            // {
            //     cout<<dijk_dis[i]<<" ";
            // }
            // for(ll i=1;i<=n;i++)
            // {
            //     // cout<<i<<"{";
            //     for(auto &it:positive_wt[i])
            //     {

            //         ll x=it.second+bell_dis[i]-bell_dis[it.first];
            //         it.second=x;
            //         //cout<<"{"<<it.first<<" "<<it.second<<"}";
            //     }
            //     // cout<<"}";
            //     // cout<<endl;
            // }
            // for(ll i=1;i<=n;i++)
            // {
            //     cout<<i<<"{";
            //     for(auto it:positive_wt[i])
            //     {

            //         // ll x=it.second+bell_dis[i]-bell_dis[it.first];
            //         // it.second=x;
            //         cout<<"{"<<it.first<<" "<<it.second<<"}";
            //     }
            //     cout<<"}";
            //     cout<<endl;
            // }
            // for(ll i=1;i<=n;i++)
            // {
            //     // vector<ll>dijk_dis=dijkastra_array(positive_wt,i);
            //     vector<ll>dijk_dis(n+1,999999);
            //     if(bellman_ford(positive_wt,i,dijk_dis)==0)
            //     {
            //         for(ll j=1;j<=n;j++)
            //         {
            //             // cout<<dijk_dis[i]<<" ";
            //             // if(dijk_dis[j]!=999999)
            //             // {
            //             //     dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

            //             // }
            //             cout<<dijk_dis[j]<<" ";
            //         }
            //     }
            //     else cout<<-1;
            //     cout<<endl;
            // }


            // for(ll i=1;i<=n;i++)
            // {
            //     vector<ll>dijk_dis=dijkastra_Binary_heaop(positive_wt,i);
            //     // vector<ll>dijk_dis(n+1,999999);
            //     for(ll j=1;j<=n;j++)
            //     {
            //         // cout<<dijk_dis[i]<<" ";
            //         if(dijk_dis[j]!=999999)
            //         {
            //             dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

            //         }
            //         cout<<dijk_dis[j]<<" ";
            //     }
            //     cout<<endl;
            // }

            // for(ll i=1;i<=n;i++)
            // {
            //     vector<ll>dijk_dis=dijkastra_Binomial_heaop(positive_wt,i);
            //     // vector<ll>dijk_dis(n+1,999999);
            //     for(ll j=1;j<=n;j++)
            //     {
            //         // cout<<dijk_dis[i]<<" ";
            //         if(dijk_dis[j]!=999999)
            //         {
            //             dijk_dis[j]=dijk_dis[j]+bell_dis[j]-bell_dis[i];

            //         }
            //         cout<<dijk_dis[j]<<" ";
            //     }
            //     cout<<endl;
            // }


        }
        //cout<<endl;
    }
    end = clock();
    execution_times.push_back((double)(end - start) / CLOCKS_PER_SEC);
    vector<double>::iterator it;
    for (it = execution_times.begin(); it != execution_times.end(); it++)
    {
        cout << *it << setprecision(5) << " ";
    }
    //cout<<endl;
}