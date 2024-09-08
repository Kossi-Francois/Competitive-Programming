 
 
void resolve(){
	int n, q; cin >> n >> q;
 	vl xi(n); cin >> xi;
 
	SegTree seg(xi);
	
 
 
 
 	vpi qi(q); cin >> qi;
	trav(x, qi){
		cout <<   seg.query(0, 0, n-1, x.f-1, x.s-1).elt   << endl;
	}
	return;
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
