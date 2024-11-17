
// -------- template Header ----------------//

 
const char FLOOR = '.', WALL = '#';
int R, C;
 
vpi nbh(int x, int y){
  vpi vans;
 
  if(x + 1 <  R){  vans.push_back( {x + 1, y } ); } // south
  if(x - 1 >= 0){  vans.push_back( {x - 1, y } ); } // north
 
  if(y + 1 <  C){  vans.push_back(  {x, y+1 } );  } // east
  if(y - 1 >= 0){  vans.push_back(  {x, y-1 } );  } // west
  return vans;
} 
 
 
 
int resolve(){
	int n, m; cin >> n >>m;
	R = n; C  = m;
 
	vpi start;
	vvc grid(n, vc(m)); 
	FOR(i, 0, n){
		FOR(j, 0, m){
			cin >> grid[i][j];
			if(grid[i][j] == FLOOR){
				start.push_back({i, j});
			}
		}
	}
	
 
	vvb visited(n, vb(m,false));
 
	auto bfs = [&](pii root) -> void{
 
		visited[root.f][root.s] = true;
		queue<pii> qu; qu.push(root);
 
		while (!qu.empty())
		{
			pii pos = qu.front(); qu.pop();
			trav(x, nbh(pos.f, pos.s)) if( grid[x.f][x.s] != WALL  && !visited[x.f][x.s] ){
				visited[x.f][x.s] = true;
				qu.push(x);
			}
		}
	};
 
	int room = 0;
	trav(strIdx, start) if( !visited[strIdx.f][strIdx.s] ){
		room++;
		bfs(strIdx);
	}
 
	cout << room << endl;
 
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
