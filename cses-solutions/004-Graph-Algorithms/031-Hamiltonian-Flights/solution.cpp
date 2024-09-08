//   --------------------------------------------------------------------------------------------------
 
 
   // [Hamiltonian Flights](https://cses.fi/problemset/task/1690)
   //	  - Hamiltonian Path
   //	  - Directed graph
   //	  - [Algorithm of Bellman, Held, and Karp] (https://en.wikipedia.org/wiki/Hamiltonian_path_problem ) ==> [DP + Bit masking] (https://codeforces.com/blog/entry/337)
   //           . define  dp[mask][i] as the number of Hamiltonian Paths, of the subset graph encoded as mask, and ending at vertex i;
   //		    . dp[mask][i] = sum for each vertex k in mask, dp[{mask}-i][k] * number_path(k to i)
 
      // Solution: ( Implementation: Bellman, Held, and Karp algo )
      //    -Count the number of edge between each pair of vertice
      //    -Init dp[mask == 1][source == 0] = 1 : only one Hamiltonian path in subgraph{0==source} ending at 0 == source
	  //    - Compute dp[mask][i]
	  //    - return dp[full_mask][dest]
	   
 
 
////////////////////////////////////////
 
 
int resolve(){
	int n, m; cin >> n >>m;
	vvi adj(n, vi(n, 0));
	FOR(i, 0, m){
		int a, b; cin >> a >> b; a--; b--;
		adj[a][b]++; // count number of path from a to b
	}
	
	int source = 0, dest = n-1;
	vvl dp( 1ll<<n , vl(n, 0)); // dp[mask][i] store the number of Hamiltonian Path, of the subset graph encoded in mask, and ending at vertex i;
 
	dp[1 << 0][source] = 1; // the number of Hamiltonian Path in subgraph {source} == {mask == 1 == 1 << 0} end ending in source is 1
 
	FOR(mask, 1, 1 << n){
		if(mask != ((1<<n)-1) && ( (mask>>(n-1) ) & 1) )continue; // if (mask != full_mask ) && (  last vertex is in current mask  ) ==> skip iteration: this line is not really necessary as it does not change the time complexity of the algorithm(2^n * n^2 ), this is an optimization because the CSES constraints are quite tight
		FOR(i, 0, n) if(mask & 1<< i) { // check i is set in the current mask
			FOR(k, 0, n) if( i != k && adj[k][i] && (mask & 1<<k) ){ // there is a path from k -> i, and k is in the current subgraph(mask)
				dp[mask][i] += (dp[mask ^ (1<<i)][k] * adj[k][i])%MOD; // for each subgraph excluding i and with Hamiltonian path ending at k, adding the number path to k combine with number from k to i
				dp[mask][i] %= MOD;
			}
		}
	}
 
	cout << dp[(1<<n) - 1][dest] << endl;
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
