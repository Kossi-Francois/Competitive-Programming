

////////// ----- [Mo's algo] --------------///////
// ( https://cp-algorithms.com/data_structures/sqrt_decomposition.html )

class MoAlgo{

  public: static const int blockSize = 600; // n ~ 1e6


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



  public: MoAlgo(vl& _arr, vpi& _vqu){

    n = sz(_arr);
    q = sz(_vqu);

    arr = VT<pli>(n);
    FOR(i, 0, n){ arr[i] = {_arr[i], i}; }

    vqu = VT<Query>(q);
    FOR(i,0, q){   vqu[i] = Query( _vqu[i].f, _vqu[i].s,  i );  }
    sort(all(vqu));

    compressIdx();
  }


  void compressIdx(){
    // map n (eg, 1e5) values with arbitrary range(eg [1, 1e9]) to the range [0, n]; ordered

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

