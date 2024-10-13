


//////////////Graph Matrix/////////
int R, C;

bool inBound(pii xy){
	if(  ( xy.f < 0 )  ||  (xy.f >= R)  ||  (xy.s < 0 ) || ( xy.s >= C )  ){return false;}
	return true;
}

vpi nbh(pii xy)  {
   vpi vans;
   ///     -----> second
   ///		|
   ///		v
   ///    first


   // 					  north	   south	  west	   east
   vpi fourCardinal = { {-1, 0},  {+1, 0},  {0, -1},  {0, +1} };


   // 					  	 north-east	    north-west     south-east	  south-west	   
   const vpi mixCardinal = { {-1, +1},      {-1, -1},      {+1, +1},      {+1, -1},   };


   //															
   const vpi knightMoves = {  {+1, +2},  {+1, -2}, {+2, +1}, {+2, -1}, {-1, +2}, {-1, -2}, {-2, +1}, {-2, -1} };



	int dirX = 1, dirY = 1;
	trav(elt, fourCardinal) {
		pii _next = {xy.f + dirX *  elt.f ,   xy.s + dirY * elt.s };
		if(inBound(_next)){vans.push_back(_next);};
	}	


   return vans;
};


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

	//error when no step
}


vector<pair<ld,  pii>> nbh(int x, int y){
  vector<pair<ld,  pii>> vans;
  
  int xx, yy;
  
    xx = x-2; yy = y-1;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

    xx = x-1; yy = y-2;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

    xx = x+1; yy = y-2;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

    xx = x+2; yy = y-1;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 


    xx = x-2; yy = y+1;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

    xx = x-1; yy = y+2;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

    xx = x+1; yy = y+2;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

    xx = x+2; yy = y+1;
    vans.push_back( { xx >= 0 && xx < R && yy >= 0 &&  yy < C ? 1.0 : 0.0,  {xx, yy} } ); 

  

  return vans;
} 



bool checkBorder (pii x){
	int ans = 0;
	if(x.f == 0   && x.s == 0  ){ans = 1;} // top    - left
	if(x.f == 0   && x.s == C-1){ans = 2;} // top    - right
	if(x.f == R-1 && x.s == C-1){ans = 3;} // bottom - right
	if(x.f == R-1 && x.s == 0  ){ans = 4;} // bottom - left


	if(x.f == 0   ){ans = 5;}   // top
	if(x.f == R-1 ){ans = 6;}  // bottom

	if(x.s == 0   ){ans = 7;}   // left
	if(x.s == C-1 ){ans = 8;}  // right

	return (ans > 0);
}




///////////----------------------------/////////////////////






///////////Mother vertex /////////////////
//DFS -> last finished vertx -> check all v reachability
class Graph{
   int V;
   vvi adj;

   public: Graph(int v){
      this->V = v;
      adj.assign(V, vi(0));
   }

   void addEdge(int v, int w){
      adj[v].push_back(w);
   }

   void DFSUtil(int v, vector<bool>& visited){

      visited[v] = true;

      trav(elt, adj[v]){
         if(! visited[elt]){
            DFSUtil(elt, visited);
         }
      }

   }

   public: void BFS(int s){
      vb visited(V, false);
   
      queue<int> qu;
   
      cout << s << " ";
      visited[s] = true;
      qu.push(s);
   
      while (!qu.empty()) {

         s = qu.front();
         qu.pop();
   
         trav(adjacent, adj[s]) {
               if (!visited[adjacent]) {
                  visited[adjacent] = true;
                  qu.push(adjacent);
                  cout << adjacent << " ";
               }
         }
      }
   }


   int findMother(){

      int v = 0;
      vector<bool> visited(V, false);

      FOR(i, 0, V){
         if(!visited[i]){
            DFSUtil(i, visited);
            v = i;
         }
      }

      fill(all(visited), false);

      DFSUtil(v, visited);

      F0R(k,V){
         if (!visited[k]) return -1;
      }

      return v;

   }



   void computeLevel(int x){
        
      vi  level(V);
      vb  visited(V, false);
   
      queue<int> que;
      que.push(x);
   
      // initialize level of source node to 0
      level[x] = 0;
   
      // marked it as visited
      visited[x] = true;
   
      // do until queue is empty
      while (!que.empty()) {
   
         x = que.front();    que.pop();
   
         trav(adjacent, adj[x])  {
   
               if (!visited[adjacent]) {
   
                  que.push(adjacent);
   
                  level[adjacent] = level[x] + 1;
   
                  visited[adjacent] = true;
               }
         }
      }
   

      for (int i = 0; i < V; i++)
         cout << " " << i << "   -->   " << level[i] << endl;
   }




   void dag_cycle(){
      vi cycle;
      vi visited(n, false);
      vi recStack(n, false);

      function<bool(int)> dfs = [&](int root) -> bool {

         visited[root] = recStack[root] = true;
         cycle.push_back(root);

         trav(x, adj[root]){
            if(!visited[x] && dfs(x)){ return true; }//include into cycle

            else if(  recStack[x] ){ // is a back edge
               cycle.push_back(x);  return true;
            }
         }

         recStack[root] = false;
         cycle.pop_back();
         return false;
      };

      vi vans;
      FOR(i, 0, n)if(!visited[i]  && dfs(i) ){

         int lst = cycle.back(); cycle.pop_back();
         vans.push_back(lst+1);
         
         while (!cycle.empty() && cycle.back() != lst)
         {
            vans.push_back(cycle.back()+1);
            cycle.pop_back();
         }
         vans.push_back(lst+1);
         reverse(all(vans));
         break;
      }
   }
 

};

////////////-----------------------------------------////////////






////////// shortestPath ///////////////////

//Dijkstra shortest path algorithm using Prim’s Algorithm (greedy)


class Graph{

   int V;
   vector<vpi> adj;
   const int INF = 1e3;

   public: Graph(int v){
      adj.resize(v);
      V = v;
   }

   public: void addEdge(int u, int v, int w){
      adj[u].push_back({w, v});
      adj[v].push_back({w, u});
   }

   public: void dijksShortPathPrimGreedy(int source){ //  O [ (E + V) log(V) ]

		minpq<pli> qu; qu.push({0ll, root}); // {w, v}
		vl dist(n, maxint); dist[root] = 0ll;

		while (!qu.empty())
		{
			pli node = qu.top(); qu.pop();
			if(dist[node.s] < node.f){continue;} //avoid TLE

			trav(x, adj[node.s]) if( chkmin(dist[x.s],  dist[node.s] + x.f  ) ){
				qu.push( {dist[x.s], x.s} );
			}
		}

      cout << dist << endl;
	};

   public: void bellman_ford(){
      dfs(n-1);
      vl dist(n, maxint); dist[0] = 0ll;
      bool flag = false;
      //bellman-ford
      FOR(i, 0, n){
         trav(x, edges){
            tie(a, b, c) = x;
            if( (dist[a] != maxint ) &&   chkmin(dist[b], dist[a] + c  )  ){
               if( (i == n-1) && visited[b]   ){//last loop, cycle detection
                  flag = true;
               }
            }
         }

      }
   }

};

///////----------------------------------------------///////////






////////////// DSU /////////////////////////

class DSU {  // DSU with  {path compression +  union by rank}
  vi parent;
  vi rank;
  int numSets;
  vi setSize;

  multiset<int> mxSet;

  public:  DSU(int n)
  {
      parent = vi(n);    iota(all(parent), 0); // each node it is its own parent
      rank   = vi(n, 1); //each node has a rank of one
      numSets = n;      // number of sets, num connected component
      setSize = vi(n, 1); // size of each set 
      mxSet = multiset<int>(all(setSize)); // ordered value of set size
  }
 
  // Find function
  int find(int x)
  {
      int root_parent = x;
      //find x parent, while root_parent not its own parent
      while(root_parent != parent[root_parent]) {  root_parent = parent[root_parent];  }

      //compress path, set root_parent as parent of all intermediate parents
      int x_parent;
      while (x != root_parent)
      {
         x_parent  = parent[x];
         parent[x] = root_parent;
                x  = x_parent;
      }
      
      return root_parent;
  }
 
  // Union function
  bool unite(int x, int y)
  {
      int s1 = find(x);
      int s2 = find(y);

      bool isUnited = (s1 == s2) ;

      if ( !isUnited ) { //union by max rank
         if (rank[s1] > rank[s2])  { swap(s1, s2); } // keep rank[s1] <= rank[s2]
		   if (rank[s1] == rank[s2]) { rank[s2]++ ;  }

         parent[s1] = s2;

		   mxSet.erase( mxSet.find( setSize[s2] ) );

         setSize[s2] += setSize[s1];

         mxSet.insert( setSize[s2] );

         numSets--;
      }

      return isUnited;
  }


};


/////////////-------------------------------------------------------------------------/////////////////////





//////////////////////// Connected Component //////////////////////////////////



class SCCGraph{ 
    /**
     * SCC and Graph Condensation(each node is a scc), with Kosaraju algo
     * https://cp-algorithms.com/graph/strongly-connected-components.html
     * Strongly connected component --> Kosaraju algo:
            1. build graph and transposed graph
            2. topo sort graph, and reverse toposort
            3. traverse transposed graph with reversed topo sort
    */
    

    int n;
    vvi adj;
    vvi adjT;
    vb visited;
    vi topo_sort;
    public: vi sccg_roots; // roots of each SCC 
    public: vi sccg_component; // sccg_component[i] = u means node i belong to scc u, where u is scc root
    public: vvi condensed_graph; // condensed scc graph
    public: unordered_map<int, int> sccg_roots_order; // index of each scc root in O(1)
    public: vb sat2_assignment; // assignmemnt of 2-sat solution

    public: SCCGraph(int _n){
        __init_Graph(_n);
    }

    public: SCCGraph(){}

    public: void __init_Graph(int _n){
        n = _n;
        adj  = vvi(n);
        adjT = vvi(n);
        sccg_component   = vi(n);
        condensed_graph  = vvi(n);
        sccg_roots_order = unordered_map<int, int>();
    }


    void build_sccg(){
        //topo sort
        visited = vb(n, false);
        FOR(i, 0, n) if(!visited[i]){dfs_topo(i);}

        //fill scc
        int sccIdx = 0;
        fill(all(visited), false);    reverse(all(topo_sort));
        trav(root, topo_sort) if(!visited[root]){
            sccg_roots.push_back(root);
            sccg_roots_order[root] = sccIdx++;
            dfs_scc(root, root);
        }

        // build scc condensed graph
        FOR(u, 0, n){
            trav(v, adj[u]){
                int root_u = sccg_component[u];
                int root_v = sccg_component[v];

                if(root_u != root_v){ //if there is an edge u -> v but scc[u] != scc[v] ==> add an edge scc[u] ---> scc[v]
                    condensed_graph[root_u].push_back(root_v);
                }
            }
        }
    }



    bool sat2(){
        // 2-satisfiability algo:
        //      1: add all OR closes
        //      2: build SCC
        //      3: check feasability ==> component[x] != component[~x]
        //      4: assignment

        build_sccg();
        int offset = n/2;
        sat2_assignment = vb(offset);

        bool isSatifeasable = true;
        FOR(i, 0, offset){
            if(sccg_component[i] == sccg_component[i+offset]){
                isSatifeasable = false; break;
            }
            sat2_assignment[i] = sccg_roots_order[ sccg_component[i]   ] > sccg_roots_order[ sccg_component[i+offset]  ] ;
        }

        return isSatifeasable;
    }


    void addEdge(int u, int v){
        // with u -> v
        adj[u].push_back(v);
        adjT[v].push_back(u);
    }

    void dfs_topo(int u){
        visited[u] = true;
        trav(v, adj[u]) if(!visited[v]){dfs_topo(v);}
        topo_sort.push_back(u);
    }

    void dfs_scc(int u, int scc_root){ //traverse the reverse graph : Kosaraju algo
        sccg_component[u] = scc_root;
        visited[u] = true;
        trav(v, adjT[u]) if(!visited[v]){dfs_scc(v, scc_root);}
    }

    //------------ adding close into graph ------------//
    //---- https://codeforces.com/blog/entry/92977 ----------//

    // At least one of them is true
    void add_clause_or(int i, bool f, int j, bool g) {
        // (x ∨ y) ⟺ ( (¬x ⇒ y) ∧ (¬y ⇒ x) )
        // true € [0, N-1]  --> ~true == false € [N, 2*N-1]
        int offset = n/2;
        addEdge(i + (f ? offset : 0), j + (g ? 0 : offset));
        addEdge(j + (g ? offset : 0), i + (f ? 0 : offset));
    }

    // Only one of them is true
    void add_clause_xor(int i, bool f, int j, bool g) {
        add_clause_or(i, f, j, g);
        add_clause_or(i, !f, j, !g);
    }

    // Both of them have the same value
    void add_clause_and(int i, bool f, int j, bool g) {
        add_clause_xor(i, !f, j, g);
    }
    //--------------------------------------------------//



};


////////////////////////////////------------------------------------------------------------------------////////////////////////////////





/////////////////////// Max Flow - Min Cut/////////////////
// Edmonds-Karp algorithm, an implementation of the Ford-Fulkerson method using BFS
// O(VE²)
// [USACO](https://usaco.guide/adv/max-flow?lang=cpp)
class MAX_FLOW{ 
	public:
		int n;
		vvi adj;
		vvl capacity;
		vi parent;
		unordered_set<int> bipartieS, bipartieT;

		// ans
		ll max_flow;
		vpi min_cut;
		vpi max_bipartite;

		MAX_FLOW(int _n){
			n = _n;
			adj = vvi(n);
			capacity = vvl(n, vl(n, 0ll));
			parent = vi(n);

			max_flow = 0ll;
		}

		MAX_FLOW(vvi& _adj, vvl _capacity ){
			n = sz(adj);
			adj = adj;
			capacity = _capacity;
			parent = vi(n);

			max_flow = 0ll;
		}


		void addEdge(int u, int v, ll c, bool isDirected = true){
			capacity[u][v] += c;
			adj[u].push_back(v);
			adj[v].push_back(u);

			if(!isDirected){
				capacity[v][u] += c;
			}
		};

		void addEdge_bipartite( int u, int v, ll c ){
			bipartieS.insert(u);
			bipartieT.insert(v);

			addEdge(u, v, 1);
		}




		ll augment_path(int source, int sink){

			fill(all(parent), -1); parent[source] = -2;
			queue<int> qu; qu.push(source);

			ll mini_capacity = maxint;

			while (!qu.empty())
			{
				int curr = qu.front(); qu.pop();
				trav(_next, adj[curr]) if(  parent[_next] == -1 &&  capacity[curr][_next] > 0ll ){
					parent[_next] = curr;
					chkmin(mini_capacity, capacity[curr][_next]);

					if(_next == sink){
						return mini_capacity;
					}

					qu.push(_next);
				}
			}
			return 0ll;
		};

		ll compute_maxFlow(int source, int sink){
			max_flow = 0ll;
			ll delta_flow = 0ll;
			while (delta_flow = augment_path(source, sink))
			{
				max_flow += delta_flow;
				int curr = sink;
				while (curr != source)
				{
					int prev = parent[curr];
					capacity[prev][curr] -= delta_flow;
					capacity[curr][prev] += delta_flow;
					curr = prev;
				}		
			}

			return max_flow;
		};


		void compute_minCut(int source, int sink){
			min_cut = vpi();

			compute_maxFlow(source, sink);
			augment_path(source, sink);

			set<int> set_s;
			FOR(i, 0, n) if( parent[i] != -1){set_s.insert(i);}
			
			trav(x, set_s){
				trav(y, adj[x]) if( not_in(set_s, y) ){
					min_cut.push_back({x, y});
				}
			}
		};


		void compute_maxBipartite( int source, int sink ){// Maximum Bipartite Matching

			max_bipartite = vpi();
			
			{ //preprocess edges: 

				// add virtual source and sink
				trav(v, bipartieS){ //source == u -> v with v € bipartieS
					int u = source;
					addEdge(u, v, 1);
				}
				trav(u, bipartieT){ //u -> v == sink sink with u € bipartieT
					int v = sink;
					addEdge(u, v, 1);
				}

			
				//should have only 1 edge u->v with capacity 1 at most(no accumulation)
				FOR(i, 0, n) if(!adj[i].empty() ){
					unique(adj[i]);
					trav(j, adj[i]){
						chkmin(capacity[i][j], 1ll);
					}
				}

			};

			compute_maxFlow(source, sink);

			trav(u, bipartieS){
				trav(v, adj[u]) if( is_in(bipartieT, v) &&  capacity[u][v] == 0) {
					max_bipartite.push_back({u, v});
				}
			}
		}
};



////////////////////////////////------------------------------------------------------------------------////////////////////////////////

