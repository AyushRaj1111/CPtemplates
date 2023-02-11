#include <bits/stdc++.h>
using namespace std;

class SGTree {
public:
    
	vector<int> seg;
	SGTree(int n) {
		seg.resize(4 * n + 1);
	}
 
	void build(int ind, int low, int high, int arr[],int level) {
		if (low == high) {
			seg[ind] = arr[low];
			return;
		}
 
		int mid = (low + high) / 2;
		build(2 * ind + 1, low, mid, arr,level-1);
		build(2 * ind + 2, mid + 1, high, arr,level-1);
        if(level%2 == 0){
		    seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
        }
        else{
            seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
        }
        
		// seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
	}
 
	int query(int ind, int low, int high, int l, int r) {
		// no overlap
		// l r low high or low high l r
		if (r < low || high < l) return INT_MAX;
 
		// complete overlap
		// [l low high r]
		if (low >= l && high <= r) return seg[ind];
 
		int mid = (low + high) >> 1;
		int left = query(2 * ind + 1, low, mid, l, r);
		int right = query(2 * ind + 2, mid + 1, high, l, r);
		return min(left, right);
	}
	void update(int ind, int low, int high, int i, int val,int level) {
		if (low == high) {
			seg[ind] = val;
			return;
		}
 
		int mid = (low + high) >> 1;
		if (i <= mid) update(2 * ind + 1, low, mid, i, val,level-1);
		else update(2 * ind + 2, mid + 1, high, i, val,level-1);
        if(level%2 == 0){
		    seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
        }
        else{
            seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
        }
		// seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
	}
};
// ***********************************************************************************************
 
void solve(int t){          
    int n,m;
    cin>>n>>m;
    int level = n;
    n = pow(2,n);
    int arr[n];
    SGTree stree(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    stree.build(0,0,n-1,arr,level);
    // for(int i=0;i<7;i++){
    //     cout<<stree.seg[i]<<endl;
    // }
    while(m--){
        int a,b;
        cin>>a>>b;
        stree.update(0,0,n-1,a-1,b,level);
        cout<<stree.seg[0]<<endl;
    }
}
int32_t main(){
    solve(1);
    return 0;
}
