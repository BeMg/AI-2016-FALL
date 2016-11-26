#include <bits/stdc++.h>
using namespace std;

const int MAX_TABLE_SIZE = 50;

struct table_for_dfs {
    int size;
    int table[MAX_TABLE_SIZE][MAX_TABLE_SIZE];
};

table_for_dfs mark_fail(table_for_dfs curr, int x, int y) {
    int size = curr.size;

    for(int i=0; i<size; i++) {
	curr.table[i][y] = -1;
	curr.table[x][i] = -1;
	if((x+i)<size && (y+i)<size)
	    curr.table[x+i][y+i] = -1;
	if((x-i)>=0 && (y-i)>=0)
	    curr.table[x-i][y-i] = -1;
	if((x+i)<size && (y-i)>=0)
	    curr.table[x+i][y-i] = -1;
	if((x-i)>=0 && (y+i)<size)
	    curr.table[x-i][y+i] = -1;
    }
    curr.table[x][y] = 1;

    return curr;

}

vector<int> tabletostring(table_for_dfs curr) {
    vector<int> result;
    int size = curr.size;
    for(int i=0; i<size; i++) {
	for(int j=0; j<size; j++) {
	    if(curr.table[i][j] == 1) {
		result.push_back(j);
		break;
	    }
	}
    }
    return result;
}

vector<int> DFS(table_for_dfs curr, int now_row) {
    int size = curr.size;

    if(now_row == size) {
	return tabletostring(curr);
    }

    for(int i=0; i<size; i++) {

	if(curr.table[now_row][i] == 0) {
	    table_for_dfs tmp = mark_fail(curr, now_row, i);
	    vector<int> ret = DFS(tmp, now_row+1);
	    if(!ret.empty()) return ret;
	}

    }
    vector<int> emp;
    return emp;
}

vector<int> solve_by_dfs(int size) {
    if(size>MAX_TABLE_SIZE) {
	cout << "Size MUST less than" << MAX_TABLE_SIZE << endl;
	cout << "DFS solve fail." << endl;
	vector<int> emp;
	return emp;
    }

    table_for_dfs s;

    s.size = size;
    memset(s.table, 0, sizeof(s.table));

    vector<int> result = DFS(s,0);

    return result;
}

int attack_of_number(vector<int> curr) {

    int size = curr.size();
    int table[size][size];
    memset(table, 0, sizeof(table));

    for(int i=0; i<size; i++) {
	table[i][curr[i]] = 1;
    }

    int cnt = 0;

    for(int i=0; i<size; i++) {
	int x = i;
	int y = curr[i];
	for(int j=1; j<size; j++) {
	    if(x+j<size && y+j<size && table[x+j][y+j]) {
		cnt++;
	    }
	    if(x-j>=0 && y-j>=0 && table[x-j][y-j]) {
		cnt++;
	    }
	    if(x+j<size && y-j>=0 && table[x+j][y-j]) {
		cnt++;
	    }
	    if(x-j>=0 && y+j<size && table[x-j][y+j]) {
		cnt++;
	    }
	}
	for(int j=0; j<size; j++) {
	    if(table[x][j] && j!=y)
		cnt++;
	    if(table[j][y] && j!=x)
		cnt++;
	}
    }

    return cnt;

}

vector<int> random_generate(int size) {
    
    vector<int> v;

    for(int i=0; i<size; i++) {
	v.push_back(i);
    }
    
    for(int i=0; i<size; i++) {
	int j = i+rand()%(size-i);
	swap(v[i],v[j]);
    }
    
    return v;
}

vector<int> hc(vector<int> curr) {

    int size = curr.size();

    while(1) {
	
	int curr_value = attack_of_number(curr);
	
	vector<int> next;

	int next_value = INT_MAX;

	for(int i=1; i<size; i++) {
	    
	    vector<int> tmp = curr;
	    swap(tmp[i],tmp[i-1]);
	    if(next_value > attack_of_number(tmp)) {
		next_value = attack_of_number(tmp);
		next.clear();
		next = tmp;
	    }
	
	}
    
	if(next_value <= curr_value) {
	    curr_value = next_value;
	    curr = next;
	}else {
	    return curr;
	}
	 
    }

}

int solve_by_hc(int size, int times) {
    
}


int main() {

    srand(time(NULL));

    int n;
    cin >> n;

    vector<int> ans = random_generate(n);

    for(auto i: ans)
	cout << i << " ";
    cout << endl;

    cout << attack_of_number(ans) << endl;

    return 0;
}
