ll parent[200005][33];
ll level[200005];
void binaryLifting(ll node,ll par,vector<ll>adj[]){
    for(auto child : adj[node]){
        if(child!=par){
            parent[child][0]=node;
            rep(k,1,31){
                parent[child][k]=parent[parent[child][k-1]][k-1];
                if(parent[child][k]==-1)break;
            }
            binaryLifting(child,node,adj);
        }
    }
}
ll findKthParent(ll node,ll k){
    rep(i,0,31){
        ll bit=(k>>i)&1;
        if(bit)node=parent[node][i];
    }
    return node;
}
void findLevel(ll node,ll par,vector<ll>adj[]){
    for(auto child : adj[node]){
        if(child!=par){
            level[child]=level[node]+1;
            findLevel(child,node,adj);
        }
    }
}
ll findLca(ll u,ll v){
    if(level[u]>level[v])swap(u,v);
    ll diff=level[v]-level[u];
    v=findKthParent(v,diff);
    if(u==v)return u;
    repr(limit,31,0){
        if(parent[u][limit]!=-1 && parent[u][limit]!=parent[v][limit]){
            u=parent[u][limit];
            v=parent[v][limit];
        }
    }
    return parent[u][0];
}
