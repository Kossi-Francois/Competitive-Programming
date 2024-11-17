


/////////---- template Header ----------////
 
 
const char FLOOR = '.', WALL = '#';
int R, C;
 
vvi nbh(int x, int y){
  vvi vans;
 
  if(x - 1 >= 0){  vans.push_back( {x - 1, y, 0 } ); } // north || up
  if(x + 1 <  R){  vans.push_back( {x + 1, y, 1 } ); } // south || down
 
  if(y - 1 >= 0){  vans.push_back(  {x, y-1, 2 } );  } // west  || left
  if(y + 1 <  C){  vans.push_back(  {x, y+1, 3 } );  } // east  || right
  return vans;
}
 
pii prevStep(pii pos, int step){
	if( step == 0){ // from north || up
		pos.f++;
		return pos;
	}
 
	if( step == 1){ // from south || down
		pos.f--;
		return pos;
	}
 
	if( step == 2){ // from south || down
		pos.s++;
		return pos;
	}
 
	if( step == 3){ // from south || down
		pos.s--;
		return pos;
	}
}
 
 
 
int resolve(){
	int n, m; cin >> n >>m;
	R = n; C  = m;
 
	pii src, dest;
 
	vpi start;
	vvc grid(n, vc(m)); 
	FOR(i, 0, n){
		FOR(j, 0, m){
			cin >> grid[i][j];
			if(grid[i][j] == 'A'){
				src = {i, j};
			}
 
			if(grid[i][j] == 'B'){
				dest = {i, j};
			}
		}
	}
	
 
	vc dir = {'U', 'D', 'L', 'R'};
 
	vvb visited(n, vb(m,false));
	vvi prev(n, vi(m, -1));
 
	
	function<void(pii )> bfs = [&](pii root ) -> void{
 
 
 
		queue<pii > qu; qu.push(root);
		visited[root.f][root.s] = true;
 
 
		while (!qu.empty())
		{
			pii node = qu.front(); qu.pop();
 
 
			trav(x, nbh(node.f, node.s)) if( grid[x[0]][x[1]] != WALL  && !visited[x[0]][x[1]] ){
 
				pii next = {x[0], x[1]}  ; 
 
				visited[next.f][next.s] = true;
 
				prev[next.f][next.s] = x[2];
				qu.push(next);
				
			}
		}
		return;
	};
 
 
 
 
 
	bfs(src );
	bool flag = false;
	string shortestPath  = "";
 
	if(visited[dest.f][dest.s]){
		flag = true;
		while (dest != src)
		{
			shortestPath += dir[prev[dest.f][dest.s]];
			dest = prevStep(dest, prev[dest.f][dest.s]);
		}
		reverse(all(shortestPath));
	}
 
	if(flag){
		YES();
		cout << sz(shortestPath) << endl;
		cout << shortestPath << endl;
 
	}else{
		NO();
	}
 
 
    return 0;
}
 
 
 
 
 
int main() {
	
	
    fast();
 
    int TT = 1;  // cin>>TT;
	for (int tt = 1; tt <= TT; tt++) 
	{
 
        //cout << "Case #" << tt << ": ";
        
        resolve();
        //cout << "Case #" << tt << ": " << resolve() << endl;
        //cout << (ans ? "YES" : "NO") << endl;
    
	}
 
 
	return 0;
}
