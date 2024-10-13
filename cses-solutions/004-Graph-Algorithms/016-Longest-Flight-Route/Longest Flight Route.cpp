



 
typedef pair<ll, int> pli;
 
 
 
 
 
int resolvexx(){
	int n, m; cin >> n >>m;
	vvi adj(n);
	// vector<tuple<int, int, ll>> edges(m);
	int a, b;  
 
	FOR(i, 0, m){
		cin >> a >> b; a--; b--;
		adj[a].push_back( b);
	}
 
 
	vi visited(n, false);
	vi path;
	vi prev(n, -1);
	int src = 0, dest  = n-1;
	vl dist(n, minint); dist[dest] = 0;
 
	function<ll(int )> dfs = [&](int root ) -> ll{
		
		if( root == dest || visited[root]  ){	
			return dist[root];
		}
 
		visited[root] = true;
		trav(x, adj[root]) if( chkmax(dist[root], dfs(x) + 1) ) {
 
			prev[root] = x;
		}
 
		return dist[root];
	};
 
	dfs(src);
 
	if(dist[src] > 0 ){
 
		int lst = src;
		while ( lst != dest )
		{
			path.push_back(lst);
			lst = prev[lst];
		}
		path.push_back(lst);
 
		cout << sz(path) << endl;
		trav(x, path){  cout << x + 1 << " ";
		}
 
		cout << endl;
 
	}else{
		cout << "IMPOSSIBLE" << endl;
	}
    return 0;
}
 
 
 
int resolve(){
	int n, m; cin >> n >>m;
	vvi adj(n), adj_rev(n);
	int a, b;  
	vi indegree(n, 0);
 
	FOR(i, 0, m){
		cin >> a >> b; a--; b--;
		adj[a].push_back( b);
		adj_rev[b].push_back(a);
		indegree[b]++;
	}
 
	int src = 0, dest  = n-1;
	vl dist(n, minint); dist[src] = 0ll;
	vi prev(n, -1);
 
 
	queue<int> qu;
	FOR(i, 0,n)if(indegree[i]==0){qu.push(i);}
 
 
	function<void()> kanh = [&]() -> void {
 
		while (!qu.empty())
		{
			//kanh
			int root = qu.front(); qu.pop();
			trav(x, adj[root]){
				if(--indegree[x] == 0){qu.push(x);}
			}
 
			//update dist
			//in topo sort, already process root parents (from adj_rev)
			//so update dist[root] with dist[parent]
			trav(parent, adj_rev[root])if(  chkmax(dist[root], dist[parent] + 1ll) ){
				prev[root] = parent;
			}
 
			if(  root == src  ){dist[root] = 0;}
		}
	};
 
 
	kanh();
 
	bool flag = dest == src;
	vi path;
 
	int lst = dest;
	while (lst != src && dist[lst] > 0  )
	{
		/* code */
		path.push_back(lst);
		lst = prev[lst];
		if(lst == src){flag = true;}
	}
	path.push_back(src);
	
 
	if(flag ){
		reverse(all(path));
 
		cout << sz(path) << endl;
		trav(x, path){  cout << x + 1 << " ";
		}
		cout << endl;
 
	}else{
		cout << "IMPOSSIBLE" << endl;
	}
    return 0;
}
 
 
 
int main() {
	
	
    fast();
 
    int TT = 1;   //cin>>TT;
	for (int tt = 1; tt <= TT; tt++) 
	{
 
        //cout << "Case #" << tt << ": ";
        
        resolve();
        //cout << "Case #" << tt << ": " << resolve() << endl;
        //cout << (ans ? "YES" : "NO") << endl;
    
	}
 
 
	return 0;
}
