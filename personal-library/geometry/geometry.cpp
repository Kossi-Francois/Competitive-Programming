

struct Rect {
	int x1, y1, x2, y2;
	int area() { return (y2 - y1) * (x2 - x1); }
};

int intersect(Rect p, Rect q) {
	int xOverlap = max(0, min(p.x2, q.x2) - max(p.x1, q.x1));
	int yOverlap = max(0, min(p.y2, q.y2) - max(p.y1, q.y1));
	return xOverlap * yOverlap;
}

struct Point {
	int x, y;
	Point(int _x, int _y){
		x = _x;
		y = _y;
	}
};


struct Line {
	ld a, b;
	Line(ld _a, ld _b){
		a = _a;
		b = _b;
	}


	Line(Point p1, Point p2){
		a =  (ld) (p2.y - p1.y)/ (ld) (p2.x - p1.x);
		b = (ld) p2.y - a * p2.x;
	}


};


ld norm(Point p1, Point p2){
	return sqrt( (ld) pow( p1.x - p2.x, 2  ) +  (ld) pow( p1.y - p2.y, 2  )   );
}

ld norm(pll p1, pll p2){
	return sqrt( (ld) pow( p1.f - p2.s, 2  ) +  (ld) pow( p1.f - p2.s, 2  )   );
}








////---------------------Convex Hull-----------------------
// https://cp-algorithms.com/geometry/convex_hull_trick.html#li-chao-tree
// https://cp-algorithms.com/data_structures/segment_tree.html#dynamic-segment-tree
// https://codeforces.com/blog/entry/86731
// https://codeforces.com/blog/entry/63823
// https://robert1003.github.io/2020/02/06/li-chao-segment-tree.html


#pragma once

template<typename LT>
struct Line {
  LT m, b;
  // Line() : m(0), b( -inf) {}
  Line(LT m, LT b) : m(m), b(b) {}
  LT operator()(LT x) { return m * x + b; }

  static bool fx_lesser_gx ( Line& fx, Line& gx, LT x ){ return fx(x) < gx(x); }
  static bool fx_greater_gx( Line& fx, Line& gx, LT x ){ return fx(x) > gx(x); }
};

template<typename LT>
struct Node {
  static const bool minmax = false; // true == min, false == max
  // static const ll   inf    = maxintll;
  static const ll   default_yIntercept =(minmax ? numeric_limits<LT>::max() : numeric_limits<LT>::min());

  Line<LT> seg;
  Node *lson, *rson;

  Node():lson(0), rson(0), seg(0, default_yIntercept ){}
  Node(Line<LT> _seg): seg(_seg), lson(0), rson(0) {} 

  Node(Node *lson, Node *rson, Line<LT> _seg) : lson(lson), rson(rson), seg(0, default_yIntercept ){
    seg.m = _seg.m; seg.b = _seg.b; 
  }


  bool compare(Line<LT>& other, LT x ){ // compare two functions val at x
    if (minmax){   return Line<LT>::fx_greater_gx(seg, other, x); }
    else{          return Line<LT>::fx_lesser_gx (seg, other, x); }
  }

  bool compare(Line<LT>& other){   return minmax ? seg.m > other.m : seg.m < other.m;} // compare line slope
  static LT compare(ll y1, ll y2){ return minmax ? min(y1, y2)     : max(y1, y2);} // compare integer

};



template<typename LT>
class LiChaoTree{ 

  public:
    // static const ll LL  = -((ll)1e10 + 5);
    static const ll LL  =            0ll;
    static const ll RR  =   (ll)1e9 + 100;
    

    VT<Node<LT>*> versions; // V[0] == empty node
    Node<LT>* root;
    bool keepVersion;

    LiChaoTree(bool _keepVersion = true){
      root  = new Node<LT>();
      keepVersion = _keepVersion;

      if( keepVersion  ){ versions.push_back(root); }
    }

    void insert( Line<LT> line, int _version = -1 ){
      root = insert(LL, RR, line, _version == -1 ? root : versions[_version]);
      if( keepVersion  ){ versions.push_back(root); }
    }

    ll query( ll x, int _version = -1 ){
      return query(LL, RR, x, _version == -1 ? root : versions[_version]);
    }

    Node<LT>* rollBack(){
      Node<LT>* res = versions.back(); 
      versions.pop_back(); root = versions.back();
      return res;
    }


    Node<LT>* insert(ll l, ll r, Line<LT> seg, Node<LT>* old) {
      if(l + 1 == r) {
        if( old->compare(seg, l ) ){
          return new Node(seg);
        } 
        return old;
      }

      ll mid = (l + r) >> 1;
      Node<LT>* o = new Node<LT>(  old->lson, old->rson, old->seg  );
      if( o->compare(seg) ){ swap(seg, o->seg); } 

      if(o->compare(seg, mid)  ) {
        swap(seg, o->seg);
        if(o->rson){ o->rson = insert(mid, r, seg, o->rson);   } 
        else o->rson = new Node<LT>(seg);
      }
      else {
        if(o->lson){ o->lson = insert(l, mid, seg, o->lson); } 
        else o->lson = new Node<LT>(seg);
      }
      return o;
    }

    LT query(ll l, ll r, LT x, Node<LT>* o) {
      if(l + 1 == r) return o->seg(x);
      ll mid = (l + r) >> 1;
      if(x < mid && o->lson) return Node<LT>::compare(o->seg(x), query(l,  mid, x, o->lson));
      else if(o->rson)       return Node<LT>::compare(o->seg(x), query(mid,  r, x, o->rson));
      return o->seg(x);
    }


    void del(Node<LT>* o) {
      if(o->lson) del(o->lson);
      if(o->rson) del(o->rson);
      delete o;
    }
    void merge(Node<LT>* dest, Node<LT>* o) {
      if(o->seg.m != 0 || o->seg.b != Node<LT>::default_yIntercept) insert(LL, RR, o->seg, dest);
      if(o->lson) merge(dest, o->lson);
      if(o->rson) merge(dest, o->rson);
    }

};



