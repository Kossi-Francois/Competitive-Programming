

 
//   --------------------------------------------------------------------------------------------------
 
 
   // [Range Updates and Sums](https://cses.fi/problemset/task/1735/)
 
   //	- [Segment Tree  ] (https://cp-algorithms.com/data_structures/segment_tree.html#implementation) 
   //   - [ Range Query and Update]
   //   - [Lazy Segment Tree]
 
 
 
 
	// Solution I : [Segment Tree  ] :  O ( log(N) )
    //            - juste use Lazy Segment Tree (  [template here]()  )
 
 



void resolveI(){  
  int n, q; cin >> n >> q;
  vl arr(n); cin >> arr;
 
  SegTree<SegNode> seg(arr);
 
  int qT, a, b, x;
  FOR(_, 0, q){
    cin >> qT >> a >> b; a--; b--;
 
    if(qT == 1){
      cin >> x;
      seg.updateRange( a, b, x, true);
 
    }else if(qT == 2){
      cin >> x;
      seg.updateRange(a, b, x, false);
    }else{
      cout << seg.query( a, b).val << endl;;
    }
  }
 
	return;
}
 
 
 
 
 
 
int main() {
	
	
    fast();
 
    int TT = 1;   //cin>>TT;
	for (int tt = 1; tt <= TT; tt++) 
	{
 
        //cout << "Case #" << tt << ": ";
        
        resolveI();
        //cout << "Case #" << tt << ": " << resolve() << endl;
        //cout << (ans ? "YES" : "NO") << endl;
    
	}
 
 
	return 0;
}

 
 
