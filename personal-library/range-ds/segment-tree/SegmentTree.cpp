




class  SegNode
{
  public:
  
    static const int vroot = 0;
    ll val;
    int idx;



    SegNode(ll _val, int _idx){ // ---> to check 1
      val = _val; 
      idx = _idx;
    }

    SegNode(){  // return identity element or neutral element for merge ops ----> to check 2
      // default constructor
      // if sum tree || xor tree  ==> 0;
      // if max tree ==> min integer
      // if min tree ==> max integer

      val = minint;
      idx = -1;
    }



    public: static SegNode merge( const SegNode& vl, const SegNode& vr){
      ll _newval = max(vl.val, vr.val);
      int _idx;
      if( _newval == vr.val ){ _idx = vr.idx;}
      if( _newval == vl.val ){ _idx = vl.idx;}
      return SegNode(_newval, _idx  );
    }


    public: static pii children (int v){ return  { (v << 1) + 1,  (v << 1) + 2  }; } // 0 - indexed
    public: static int middle(int tl, int tr){ return (tl + tr) >> 1; }

};


typedef SegNode snode;


//https://cp-algorithms.com/data_structures/segment_tree.html#implementation
class SegTree{
  // start node V == 0 ==> left == 2*v + 1 &&  right == 2*v + 2

  private: vl arr;
  public: vector<snode> tree;
  private: int N;

  public: SegTree(){}

  public: SegTree(vl& arr_){
    arr = arr_;
    N = arr_.size();
    tree = vector<snode> (4*N);

    buildTree(0, 0, N-1);
  }

  public: snode merge_children(const snode& v, const snode& w){  //----> to change 
    return snode::merge(v, w);
  }

  public: void buildTree(int v, int tl, int tr){
    if(tl == tr){ if(  v < 4*N  &&  tl < N ) {  
      tree[v] =  snode(arr[tl], tl); //----> to check 1
    }}

    else{
      
      int mid         = snode::middle(tl, tr);
      auto [vlc, vrc] = snode::children(v);

      buildTree(vlc, tl, mid); buildTree(vrc, mid+1, tr);
      tree[v] = merge_children(tree[vlc], tree[vrc]);
    }
  }

  public: void updateRec(int v, int tl, int tr, int pos){

    if(tl == tr){
      tree[v] = snode(arr[pos], pos); //----> to check 1
    }else{

      int mid         = snode::middle(tl, tr);
      auto [vlc, vrc] = snode::children(v);

      if(pos <= mid ){
        updateRec( vlc,     tl,  mid,  pos );
      }else{
        updateRec( vrc,  mid+1,  tr,   pos );
      }
      tree[v] = merge_children(tree[vlc], tree[vrc]);

    }
  }

  public: void update( int pos, ll newval, bool acc = false){
      
    int v = snode::vroot, tl = 0,  tr = N-1; 

    if(pos < tl || tr < pos){
      return;
    }else{
      arr[pos] = acc ? arr[pos] + newval : newval;
      updateRec( v,  tl,  tr,  pos);
    }
  }

  public: snode query(int v, int tl, int tr, int ql, int qr){ 
			//(root node v = 0; {tl = 0, tr = n-1} tree search space range; {ql = query left, qr = qquery right} query range)

    if(qr < ql){ //qery on empty range
      return snode();  //----> to check 2
    }

    if( tl == ql && tr == qr){
      return tree[v];
    }else{

      int mid         = snode::middle(tl, tr);
      auto [vlc, vrc] = snode::children(v);

      return merge_children(  query(vlc,     tl,  mid,              ql,   min(qr, mid) ) ,
                              query(vrc,  mid+1,   tr,  max(mid+1, ql),   qr )
      );
    }
  }
  
};

///////////////================ ********************* =================//////////////////////





///////////////================ ----------- seg with lazy prop  -------------------------   =============================//////////////////////


class  SegNode
{
  public:
    ll val;
    ll lazyAcc = 0ll;
    ll lazySet = 0ll;

    int idx; // val idx

  SegNode(pli _val_idx){ // ---> to check 0
    val = _val_idx.f; 
    idx = _val_idx.s;

    lazyAcc = 0ll;
    lazySet = 0ll;
  }

  SegNode(pair<ll, pii> _val_idx) : SegNode({_val_idx.f, _val_idx.s.f})   { // 2D constructor

  }


  SegNode(){  // return identity element or neutral element for merge ops ----> to check 2
    // default constructor
    // if sum tree || xor tree  ==> 0;
    // if max tree ==> min integer
    // if min tree ==> max integer

    val = 0ll;
    lazyAcc = 0ll;
    lazySet = 0ll;
  }




  ll computeLazySegVal(ll _val, int tl, int tr ){ // ----> to check 3
    return (tr - tl + 1) *  _val; // if sum seg: new delta val == (nbr element in seg)  x  (lazy val)
    // return _val; // if max, min seg : new deta val  = max( elt for elt in seg) = lazy val
  }


  void update(int tl, int tr, ll _val){
    val +=   computeLazySegVal(_val, tl,  tr );

    if(lazySet == 0 ){   lazyAcc += _val;  } //if nothing to set, accumulate acc
    else{ //otherwise, accumulate value to set
      lazySet += _val; 
      lazyAcc = 0;
    } 
  }

  void set(int tl, int tr, ll _val){
    lazySet = _val;
    val =  computeLazySegVal(_val, tl,  tr );
    lazyAcc = 0;
  }



  void static pushdown(vector<SegNode>&  tree, int v, int tl, int tr){

    int       mid =  middle(tl, tr);
    auto [lc, rc] =  children(v);

    if(tree[v].lazySet != 0){ // lazy set

      tree[lc].set( tl,    mid,  tree[v].lazySet  );
      tree[rc].set( mid+1,  tr,  tree[v].lazySet  );

      tree[v].lazySet  = 0;
    }

    else if( tree[v].lazyAcc != 0){ // lazy update

      tree[lc].update(    tl,  mid, tree[v].lazyAcc );
      tree[rc].update( mid+1,   tr, tree[v].lazyAcc );

      tree[v].lazyAcc = 0;
    }
  }




  public: static SegNode merge( const SegNode& lc, const SegNode& rc){
    // int idx = lc.val > rc.val ? lc.idx : rc.idx;
    return SegNode( {lc.val + rc.val, -1   }  );
  }

  public: static SegNode merge( const SegNode& v, const SegNode& lc, const SegNode& rc){
    SegNode temp = merge(lc, rc );
    return temp;
  }




  public: static pii children (int v){ return  { (v << 1) + 1,  (v << 1) + 2  }; } // 0 - indexed
  public: static int middle(int tl, int tr){ return (tl + tr) >> 1; }

};



// typedef SegNode snode;

//https://cp-algorithms.com/data_structures/segment_tree.html#implementation
//https://usaco.guide/plat/RURQ?lang=cpp

template<typename Tnode>
class SegTree{
  // start node V == 0 ==> left == 2*v + 1 &&  right == 2*v + 2

  private: vl& arr;
  private: vector<Tnode> tree;
  private: int N;
  private: const int rootV = 0;

  // public: SegTree(){}

  public: SegTree(vl& arr_): arr(arr_) {
    N = arr_.size();
    tree = vector<Tnode> (4*N);

    buildTree(0, 0, N-1);
  }

  Tnode merge_children(int v){ 
    auto [lc, rc] =  Tnode::children(v); 
    return Tnode::merge(tree[v], tree[lc], tree[rc]); 
  }

  Tnode merge_children(int v, const Tnode& u, const Tnode& w){ 
    return Tnode::merge(tree[v], u, w);
  }


  public: void buildTree(int v, int tl, int tr){
    if(tl == tr){ if(  v < 4*N  &&  tl < N ) {  
      tree[v] =  Tnode( {arr[tl], tl} ); //----> to check 1
    }}

    else{
      int mid       = Tnode::middle(tl, tr);
      auto [lc, rc] = Tnode::children(v);

      buildTree(lc, tl, mid); buildTree(rc, mid+1, tr);
      tree[v] = merge_children(v);
    }
  }

  public: void updateRec(int v, int tl, int tr, int pos){

    if(tl == tr){
      tree[v] = Tnode( {arr[pos], pos } ); //----> to check 1
    }else{
      
      int mid       = Tnode::middle(tl, tr);
      auto [lc, rc] = Tnode::children(v);

      if(pos <= mid ){
        updateRec( lc,    tl,  mid,  pos );
      }else{
        updateRec( rc,  mid+1,  tr,  pos );
      }
      tree[v] = merge_children(v);
    }
  }

  public: inline void update( int pos, ll newval, bool accumulate = false){
      
    int v = 0, tl = 0,  tr = N-1; 

    if(pos < tl || tr < pos){
      return;
    }else{
      arr[pos] = accumulate ? arr[pos] +  newval : newval;
      updateRec( v,  tl,  tr,  pos);
    }
  }



  public: void updateRange(int v, int tl, int tr, int upd_rl, int upd_rr, ll val){
    if(upd_rl > tr || tl > upd_rr ){return;}

    if( upd_rl <= tl && tr <= upd_rr){
      tree[v].update(tl, tr, val  );
      return;
    }

    int mid       = Tnode::middle(tl, tr);
    auto [lc, rc] = Tnode::children(v);

    Tnode::pushdown(tree, v, tl, tr);
    updateRange(lc,    tl,  mid, upd_rl, upd_rr, val);
    updateRange(rc, mid+1,   tr, upd_rl, upd_rr, val);

    tree[v] = merge_children(v);
    return;
  }

  void setRange(int v, int tl, int tr, int ql, int qr, ll val) {
    if (ql > tr || qr < tl) return;
    if (ql <= tl && tr <= qr) {
      tree[v].set(tl, tr, val);
      return;
    }

    int mid       = Tnode::middle(tl, tr);
    auto [lc, rc] = Tnode::children(v);

    Tnode::pushdown(tree, v, tl,  tr);
    setRange(lc,      tl,  mid,  ql, qr, val);
    setRange(rc, mid + 1,   tr,  ql, qr, val);

    tree[v] = merge_children(v);
    return;
  }

  public:inline void updateRange(int ql, int qr, ll val, bool accumulate = false){ 
    accumulate ? updateRange(rootV, 0, N-1, ql, qr, val) :  setRange(rootV, 0, N-1, ql, qr,  val);  
  }


  public: Tnode query(int v, int tl, int tr, int ql, int qr){ 
		//(root node v = 0; {tl = 0, tr = n-1} tree search space range; {ql = query left, qr = qquery right} query range)

    if(qr < ql ||  ql > tr || qr < tl){ //qery on empty range
      return Tnode();  //----> to check 2
    }

    if( tl == ql && tr == qr){
      return tree[v];
    }else{

      int mid       = Tnode::middle(tl, tr);
      auto [lc, rc] = Tnode::children(v);

      Tnode::pushdown(tree, v, tl, tr);

      return merge_children( 
        v,
        query(lc,    tl, mid,             ql,  min(qr, mid) ) ,
        query(rc,  mid+1, tr,  max(mid+1, ql),  qr )
      );
    }
  }

  public: Tnode query(int ql, int qr){ return query(rootV, 0, N-1,  ql,  qr);  }
  
};





///////////////================ ********************* =================//////////////////////













typedef SegNode snode;

//https://cp-algorithms.com/data_structures/segment_tree.html#implementation
//https://usaco.guide/plat/RURQ?lang=cpp

class SegTree2D{
  // start node V == 0 ==> left == 2*v + 1 &&  right == 2*v + 2

  private: vvl& arr;
  private: vector< vector<snode>> tree;
  private: int N, M;
  public: static const int rootX = 0, rootY = 0;

  // public: SegTree2D(){}

  public: SegTree2D(vvl& arr_) : arr(arr_) {
    // arr = arr_;
    N = sz(arr);
    M  = sz(arr[0]);
    tree = vector< vector<snode>> (4*N, vector<snode>(4 * M));

    build_x(rootX, 0, N-1);
  }



  snode merge_children(const snode& treeV, const snode& treeW){ 
    return snode::merge(treeV, treeW);
  }




  void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {

    auto [vlcx, vrcx] =  snode::children(vx); 
    auto [vlcy, vrcy] =  snode::children(vy); 

    if (ly == ry) {
      if (lx == rx)
        tree[vx][vy] = snode( {arr[lx][ly], {lx, ly}} );
      else
        tree[vx][vy] = merge_children(tree[vlcx][vy], tree[vrcx][vy]);
    } else {

      int midY = snode::middle(ly, ry);

      build_y(vx, lx, rx, vlcy,      ly,  midY);
      build_y(vx, lx, rx, vrcy,  midY+1,    ry);
      tree[vx][vy] = merge_children(tree[vx][vlcy] , tree[vx][vrcy]);
    }
  }

  void build_x(int vx, int lx, int rx) {

    auto [vlcx, vrcx] =  snode::children(vx); 

    if (lx != rx) {

      int midX = snode::middle(lx, rx);
      build_x(vlcx,     lx,  midX);
      build_x(vrcx, midX+1,    rx);
    }
    build_y(vx, lx, rx, rootY, 0, M-1);
  }




  snode query_y(int vx, int vy, int tly, int try_, int qly, int qry) {
    if (qly > qry){  return snode();  }
      
    if (qly == tly && try_ == qry){  return tree[vx][vy];  }
      
    int midY      = snode::middle(tly, try_);
    auto [vlcy, vrcy] =  snode::children(vy); 


    return merge_children(query_y(vx, vlcy,    tly,   midY,        qly,         min(qry, midY)),
                          query_y(vx, vrcy, midY+1,   try_,  max(qly, midY+1),         qry  ) );
  }


  snode query_x(int vx, int tlx, int trx, int qlx, int qrx, int qly, int qry) {
    if (qlx > qrx){  return snode();  }
        
    if (qlx == tlx && trx == qrx){ return query_y(vx, rootY, 0, M-1, qly, qry);    }
        

    int midX  = snode::middle(tlx, trx);
    auto [vlcx, vrcx] =  snode::children(vx); 


    return merge_children(  query_x(vlcx,    tlx,   midX,       qlx,         min(qrx, midX),  qly,  qry),
                            query_x(vrcx,  midX+1,   trx,  max(qlx, midX+1),        qrx,      qly,  qry) 
          );
  }

  snode query( int qlx, int qrx, int qly, int qry) {
    return  query_x(rootX, 0, N-1,  qlx,  qrx,  qly,  qry);
  }


  void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y) {

    auto [vlcx, vrcx] =  snode::children(vx); 
    auto [vlcy, vrcy] =  snode::children(vy); 

    if (ly == ry) {
      if (lx == rx)
        tree[vx][vy] =   snode( {arr[x][y], {x, y}} );
      else
        tree[vx][vy] = merge_children(tree[vlcx][vy] ,  tree[vrcx][vy] );
    } else {

      int midY = snode::middle(ly, ry);

      if (y <= midY){  update_y(vx, lx, rx, vlcy,    ly,  midY,  x, y);  }
          
      else{            update_y(vx, lx, rx, vrcy, midY+1,  ry,   x, y);  }
          
      tree[vx][vy] = merge_children(tree[vx][vlcy] , tree[vx][vrcy]);
    }
  }

  void update_x(int vx, int lx, int rx, int x, int y) {
    if (lx != rx) {
      int midX  = snode::middle(lx, rx);
      auto [vlcx, vrcx] =  snode::children(vx); 

      if (x <= midX)
        update_x(vlcx,   lx,    midX, x, y);
      else
        update_x(vrcx, midX+1,   rx,  x, y);
    }

    update_y(vx, lx, rx, rootY, 0, M-1, x, y);
  }


  public: void update(int x, int y, ll new_val, bool acc = false){
    
    int lx = 0,  rx = N-1; 
    int ly = 0,  ry = M-1;

    if(x < lx || rx < x  || y < ly || ry < y ){
      return;
    }else{
      arr[x][y] = acc ? arr[x][y] + new_val :  new_val;
      update_x( rootX,  lx,  rx,  x,  y);
    }
  }

};

////////////////////////-------------------------------------////////////////////









////////// ----- [Mo's algo] --------------///////
// ( https://cp-algorithms.com/data_structures/sqrt_decomposition.html )

class MoAlgo{


  public: static const int blockSize = 600;


  public: struct Query{
    int l, r, idx; //{query left, query right, query index}
    public: Query(int l, int r, int idx){
      this->l = l;
      this->r = r;
      this->idx = idx;
    }

    public: Query(){}

    bool operator <(const Query &other){
      return make_pair(this->l/blockSize, this->r ) < make_pair(other.l/blockSize, other.r);
    }
  };


  public: 
    vector<Query> vqu;
    vector<pair<ll, int>> arr; // {value, index}
    
    int n, q;
    int cur_l = 0, cur_r = -1;


   int cnt;
   vi freq;



  public: MoAlgo(vector<pair<ll, int>>& _arr, vector<Query>& _vqu){
    arr =_arr;
    vqu = _vqu;  sort(all(vqu));

    n = sz(arr);
    q = sz(vqu);

    compressIdx();
  }

  void compressIdx(){
    map<ll, int> compressedIdx;
    trav(x, arr){ compressedIdx[x.f] = 0; } //sort values
    int idx = 0;
    trav(x, compressedIdx){ x.s = idx++; } // add idx to sorted values

    trav(x, arr){ x.s = compressedIdx[x.f]; } // add compressed idx to original arr
  }


  void add(int idx){
    if(  ++freq[ arr[idx].s ] == 1 ){
      cnt++;
    }
  }


  void erase(int idx){
    if(  --freq[ arr[idx].s ] == 0 ){
      cnt--;
    }
  }

  int get_answer(){
    return cnt;
  };

  void move(Query curr_q){

    while (cur_l > curr_q.l)
    {
      add(--cur_l);
    }

    while (cur_r < curr_q.r)
    {
      add(++cur_r);
    }

    while (cur_l < curr_q.l)
    {
      erase(cur_l++);
    }

    while (cur_r > curr_q.r)
    {
      erase(cur_r--);
    }
  }


  public: vl compute_queries(){

    cnt = 0;
    freq = vi(n, 0);

    vl vans(q);
    cur_l = 0, cur_r = -1;

    trav(curr_q, vqu){

      move(curr_q);

      vans[curr_q.idx] = get_answer();
      
    }

    return vans;
  }

};