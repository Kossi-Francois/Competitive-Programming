


///////////////////------------------Standard Prefix string Tree ------------------------------///////////////////////////////////
// https://www.geeksforgeeks.org/trie-insert-and-search/

const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode{
	struct TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
};

struct TrieNode *getTrieNode(void){
	struct TrieNode *pNode = new TrieNode;
	pNode->isEndOfWord = false;
	for(int i = 0; i < ALPHABET_SIZE; i++){
		pNode->children[i] = NULL;
	}
	return pNode;
}

void insertTrieNode(struct TrieNode *root, string key){
	if(!root){ return;}

	struct TrieNode *pCrawl = root;
	for(int i=0; i < key.size(); i++){
		int idx = key[i] - 'a';
		if(!pCrawl->children[idx]){
			pCrawl->children[idx] = getTrieNode();
		}
		pCrawl = pCrawl->children[idx];
	}

	pCrawl->isEndOfWord = true;
}


bool searchTrieNode(struct TrieNode *root, string key){
	if(!root){ return false;}

	struct TrieNode *pCrawl = root ;
	for(int i =0; i< key.size(); i++){
		int idx = key[i] - 'a';
		if(!pCrawl->children[idx]){
			return false;
		}
		pCrawl = pCrawl->children[idx];
	}

	return pCrawl ? pCrawl->isEndOfWord : false;
}


bool searchTrieNode(struct TrieNode *root, string& key, int pos, int len ){
	if(!root){ return false;}

	int keysize = sz(key);
	if(  (pos < 0) ||  (len < 1) || (pos + len > keysize)  ){return false;}

	struct TrieNode *pCrawl = root ;
	for(int i = pos; i < pos + len; i++){
		int idx = key[i] - 'a';
		if(!pCrawl->children[idx]){
			return false;
		}
		pCrawl = pCrawl->children[idx];
	}

	return pCrawl ? pCrawl->isEndOfWord : false;
}


bool isEmptyTrieNode(TrieNode* root){
	if(!root){ return false;}

	for(int i=0; i< ALPHABET_SIZE; i++ ){
		if(root->children[i]){
			return false;
		}
	}
	return true;
}


TrieNode* removeTrieNide(TrieNode* root, string key, int depth = 0){
	//if tree is empty
	if(!root){
		return NULL;
	}

	//if last char of keey is being processed
	if(depth == key.size()){
		//this node is  no longer  EO word after removal of given key
		if(root-> isEndOfWord){
			root->isEndOfWord = false;
		}

		//If given node is not prefix of any other word
		if (isEmptyTrieNode(root)){
			delete (root);
			root = NULL;
		}
		
		return root;
	}

	//if depth != size(key) ==> not last char
	int idx = key[depth] - 'a';
	root->children[idx] = removeTrieNide(root->children[idx], key, depth+1);

	//if root does not hvae any child (its only xhild got deleted) , ans it is not the EO another word
	if(isEmptyTrieNode(root) && root->isEndOfWord == false){
		delete(root);
		root = NULL;
	}

	return root;
}






////////////////////////////////////////////////////////////////////////////////





/////////////////////////// Tree (Diameter - ) ///////////////////////////////////
class Tree{

	int n; 
	vvi adj;
	vl c_dist;

	vi path;
	vi c_path;


	public: void dfs_dist (int u, int p, ll d)  {
		c_dist[u] = d;
		trav(x, adj[u]) if(x != p){
			dfs_dist(x, u, d+1ll);
		}
	};
	

	public: void dfs_path(int u, int p, int dest){
		c_path.push_back(u);
		if(u == dest){
			path = c_path;
		}
		trav(x, adj[u])if(x != p){
			dfs_path(x, u, dest);
		}
		c_path.pop_back();
	};



	public:void computeDiam(){
		adj = vvi(n);
		FOR(i, 0, n-1){
			int u, v;  cin >> u >>v; u--; v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}



		c_dist = vl(n, 0ll);

		// tree diameter and its ends and the path between them
		dfs_dist(0, -1, 0);
		int end_a = argmax( c_dist );
		fill(all(c_dist), 0ll);
		dfs_dist(end_a, -1, 0);
		int end_b = argmax( c_dist );
		ll diam = c_dist[end_b] + 1;

			
		c_path = vi();
		dfs_path(end_a,  -1, end_b  );


	}

}

////////////////////////////////////////////////////////////////////////////






/////////////////// Binary lifting && LCA ////////////////////////////////////
// https://cp-algorithms.com/graph/lca_binary_lifting.html
class BinaryLifting { // Binary Lifting for tree and LCA
	const int NO_PARENT = -1;
    public:
        int _log2N;
        int n;
        vvl lift;
		vi depth;

    public:
		BinaryLifting(vi& _next){
			_init_(  _next );
		}

		BinaryLifting(vvi& _adj, int root = 0){

			int  n = sz(_adj);
			vi _next(n); _next[root] = NO_PARENT;

			depth = vi(n); depth[root] = 0;

			auto dfs = [&](auto&& self, int _root, int _parent ) -> void{
				trav(x, _adj[_root]) if(x != _parent)  {
					_next[x] = _root;
					depth[x] = depth[_root] + 1;
					self(self, x, _root);
				}
			};

			dfs(dfs, root, -1);
			_init_(  _next );
		}

		BinaryLifting(){
		}

		void _init_(  vi& _next ){    // O(N.log2(N))

			n = sz(_next);
			_log2N = ceil(log2(n)) + 1;

			lift = vvl(_log2N, vl(n));
			FOR(i, 0, n){
				lift[0][i] = _next[i];
			}

			FOR(j, 1, _log2N) FOR(i, 0, n){
				lift[j][i] =  ( lift[j-1][i] == NO_PARENT)  ?  NO_PARENT :   lift[ j-1][  lift[j-1][i]   ];
			}
		}

		int jump(int root, int k_jumps){ // O(log2(N))
			FOR(j, 0, _log2N) if(  (k_jumps >> j) & 1  )  {
				root = lift[j][root];
				if(root == NO_PARENT ){break;}
			}
			return root;
		}

		int lca(int u, int v){  if(depth[u] < depth[v]){  return lca(v, u); }
			//now depth[u] >= depth[v]

			//now lift u to the same heigth of v
			u = jump(u, depth[u] - depth[v]);

			if(u == v){return v;} //v is a direct ancestor of u

			// jump upward (with a decreasing step i) 
			ROF(i, _log2N, 0){
				if(lift[i][u] != lift[i][v]){
					u = lift[i][u];
					v = lift[i][v];
				}
			}

			// now lca is the direct parent of u (or v)
			return lift[0][u];
		}
};




//////////////////////////////////////////////////////////////////////




//https://www.youtube.com/watch?v=1PvT2d9lgqY&ab_channel=GauravSen
// https://cp-algorithms.com/graph/hld.html
// https://codeforces.com/blog/entry/22072

class TreeQuery { // Binary Lifting -- LCA -- Euler Tour -- HLD -- Centroid Decomposition
	
  public:
    const int NO_PARENT = -1;
    int _log2N;
    int n, rootT;
    vvl lift;
    vi parent, depth, sizeSubT;
    vi tin, tout, flatten;


    vi heavy, head, hld_pos;
    SegTree hld_segTree;

    int centroid;
    

  public:
  TreeQuery(int _n, int _root){
    n = _n;
    _log2N = ceil(log2(n)) + 1;
    rootT = _root;
  }

  TreeQuery(vi& _next, int _root): TreeQuery(sz(_next), _root) {
    parent = _next;
    _init_lifting(  _next );
  }

  TreeQuery(vvi& _adj, int _root = 0): TreeQuery(sz(_adj), _root) {

    run_dfs(_adj); //initialization, has to be always ran


    _init_lifting(  parent );
    hld_decomposition(_adj);
    find_centroid(_adj);
  }

  TreeQuery(vvi& _adj, vl& _arr, int _root = 0): TreeQuery(_adj, _root) {
    _init_segTree( _arr);
  }



  void run_dfs(vvi& _adj){ // O(N)

    parent = vi(n, NO_PARENT); 
    depth  = vi(n); depth[rootT] = 0;
    sizeSubT = vi(n, 1);

    int timer = 0;
    tin  = vi(n);
    tout = vi(n); 
    flatten = vi(2*n);


    heavy = vi(n, NO_PARENT);

    auto dfs = [&](auto&& self, int _node, int _parent ) -> void{

      tin[_node]= timer;
      flatten[timer] = _node;
      timer++;

      int maxChildSize = 0;

      trav(x, _adj[_node]) if(x != _parent)  {
        parent[x] = _node; // set chld parent
        depth[x]  = depth[_node] + 1; // set child depth
        self(self, x, _node); // call dfs on child
        sizeSubT[_node] += sizeSubT[x]; // accumulate child subtree size

        if(chkmax(maxChildSize,  sizeSubT[x]  )){  heavy[_node] = x;   } //set heavy child
      }

      tout[_node] = timer;
      flatten[timer] = _node;
		  timer++;
    };

    dfs(dfs, rootT, NO_PARENT);
  }

		

  void _init_lifting(  vi& _next ){    // O(N.log(N))

    lift = vvl(_log2N, vl(n));
    FOR(i, 0, n){
      lift[0][i] = _next[i];
    }

    FOR(j, 1, _log2N) FOR(i, 0, n){
      lift[j][i] =  ( lift[j-1][i] == NO_PARENT)  ?  NO_PARENT :   lift[ j-1][  lift[j-1][i]   ];
    }
  }



  void hld_decomposition(vvi& _adj){ // O(N)

    head    = vi(n);
    hld_pos = vi(n);
    int curr_pos = 0;

    auto dfs = [&](auto&& self, int _node, int _head) -> void {
      head[_node]    = _head;
      hld_pos[_node] = curr_pos++;

      if(heavy[_node] != NO_PARENT){ self(self, heavy[_node], _head); } // continue decompostion on heavy edge with same head

      trav(x, _adj[_node])if( x != parent[_node] && x != heavy[_node]  ){ // call decompositon on light edges with new head
        self(self, x, x);
      } 
    };

    dfs(dfs, rootT, rootT);
  }


  void find_centroid(vvi& _adj){ // O(n)

    auto dfs = [&](auto&& self, int _node, int _parent) -> int {
      trav(x, _adj[_node]) if(x != _parent && 2 * sizeSubT[x] > n){return self(self, x, _node);}
      return _node;
    };

    centroid = dfs(dfs, rootT, NO_PARENT);
  }




  int jump(int root, int k_jumps){ // O(log(N))
    FOR(j, 0, _log2N) if(  (k_jumps >> j) & 1  )  {
      root = lift[j][root];
      if(root == NO_PARENT ){break;}
    }
    return root;
  }

  int lca(int u, int v){  if(depth[u] < depth[v]){  return lca(v, u); } // O(log(N))
    //now depth[u] >= depth[v]

    //now lift u to the same heigth of v
    u = jump(u, depth[u] - depth[v]);

    if(u == v){return v;} //v is a direct ancestor of u

    // jump upward (with a decreasing step i) 
    ROF(i, _log2N, 0){
      if(lift[i][u] != lift[i][v]){
        u = lift[i][u];
        v = lift[i][v];
      }
    }

    // now lca is the direct parent of u (or v)
    return lift[0][u];
  }




  void _init_segTree(vl& _arr){

    vl arr(n);
    FOR(i, 0, n){
      arr[hld_pos[i] ] = _arr[i];
    }
    hld_segTree = SegTree(arr);
  }


  SegNode query(int a, int b){

    auto _query = [&](int u, int v) -> SegNode{ //  O( log(N) ^ 2 )
      SegNode res = SegNode();

      for(; head[u] != head[v];  v = parent[head[v]]){
        if(  depth[head[u]] > depth[head[v]]  ){swap(u, v);}

        res =  SegNode::merge(res,  hld_segTree.query( hld_pos[head[v]], hld_pos[v] )   );
      }

      if(depth[u] > depth[v]){swap(u, v);}
      res = SegNode::merge(res, hld_segTree.query( hld_pos[u], hld_pos[v] ) );
      return res;
    };

    return _query(a, b);;
  }



  public: void update( int pos, ll newval, bool acc = false){  
    hld_segTree.update( hld_pos[pos] , newval, acc );
  }

};







////////////////////////////// ----Double Linked List---- /////////////
template<typename TC>
class DoubleLinkedList{
	//https://www.geeksforgeeks.org/doubly-linked-list/
	public:


	struct Node{
		TC val;
		Node* _prev;
		Node* _next;
		Node() {  }
		Node(TC _val) {  val = _val;}
	};

	static void detach(Node* _node, bool keepLink = true){
		/**
		 * detach node from its current DLL
		 * 
		 * 												            		 / curr_node \
		 * 																	V             V
		 * X <-----> A <-----> curr_node <----> B <----->Y ::===> X <-----> A <---------> B <-----> Y 
		 * 
		*/

		if(  _node->_prev && _node->_next  ){
			_node->_prev->_next = _node->_next;
			_node->_next->_prev = _node->_prev;
		}

		else if( _node->_prev){ _node->_prev->_next = NULL;   }
		else if( _node->_next){ _node->_next->_prev = NULL;   }

		if(!keepLink){
			_node->_prev = NULL;
			_node->_next = NULL;
		}
	}


	static Node* insertLeft(Node* curr_node, TC data) {
		// Create a new node
		Node* new_node = new Node(data);
		insertLeft(curr_node, new_node,  true);
		// Return new node as new head
		return new_node;
	}

	
	static void insertLeft(Node* curr_node, Node* new_node, bool merge = true) {
		/**
		 * insert new_node to the left of curr_node
		 * if merge ::  A <-----> curr_node <----> B  ::===> A <-----> new_node <-----> curr_node <-----> B
		 * 
		 * 													X <---->new_node \
		 *                                                                    v
		 * if not merge:: A -----> curr_node ---> B  ::===>  A <-----> curr_node <-----> B 
		 * this will break Double Link
		 */
		
		// Make next of it as curr_node
		new_node->_next = curr_node;
		
		// Set previous of curr_node as new node
		if (curr_node != NULL) {
			if(merge){new_node->_prev  = curr_node->_prev; }
			curr_node->_prev = new_node; 
		}
	}


	static Node* insertRight(Node* curr_node, TC data) {
		// Create a new node
		Node* new_node = new Node(data);
		insertRight(curr_node, new_node, true);
		return new_node;
	}


	static void insertRight(Node* curr_node, Node* new_node, bool merge = true) {
		/**
		 * insert new_node to the left of curr_node
		 * if merge ::  A <-----> curr_node <----> B  ::===> A <-----> curr_node <-----> new_node <-----> B
		 * 
		 * 													                   / new_node <----> X 
		 *                                                                    v
		 * if not merge:: A -----> curr_node ---> B  ::===>  A <-----> curr_node <-----> B 
		 * this will break Double Link
		 */
		
		// Make prev of it as curr_node
		new_node->_prev = curr_node;
		
		// Set previous of curr_node as new node
		if (curr_node != NULL ) {
			if( merge ){ new_node->_next  = curr_node->_next;}
			curr_node->_next = new_node; 
		}
	}


	template<typename U>
	static void forwardTrav(Node* head, U fx) {
		Node * curr = head;
		unordered_set<Node*> visited;//avoid re-trav circular DLL
		while (curr != nullptr && not_in(visited, curr)) {
			fx(curr);
			curr = curr -> _next;
		}
	}

	template<typename U>
	static void backwardTrav(Node* tail, U fx) {
		Node * curr = tail;
		unordered_set<Node*> visited;//avoid re-trav circular DLL
		while (curr != nullptr && not_in(visited, curr)) {
			fx(curr);
			curr = curr -> _prev;
		}
	}

	// Function to print the doubly linked list
	static void print(Node* head) {
		auto fun = [](Node * _curr) -> void{  cout << _curr->val << " "; };
		forwardTrav(head, fun);
		cout << endl;
	}

	static Node* pop_back(Node* tail){
		Node * new_tail = tail->_prev;
		// Deallocate memory for the deleted node
    	delete tail;
		return new_tail;
	}

	static Node* pop_front(Node* head){
		Node * new_head = head->_next;
		// Deallocate memory for the deleted node
    	delete head;
		return new_head;
	}
};
////////////////////////////////////////////////////////////////////////

