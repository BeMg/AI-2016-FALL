#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

const int MAX_TABLE_SIZE = 50;

struct table_for_dfs {
    int size;
    int table[MAX_TABLE_SIZE][MAX_TABLE_SIZE];
};

map<vector<int>, int> mp;

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

    if(mp[curr] !=0) {
	if(mp[curr] == -1) {
	    return 0;
	} else {
	    return mp[curr];
	}
    }

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

    if(cnt == 0) {
	mp[curr] = -1;
    }else {
	mp[curr] = cnt;
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

vector<int> hc(int size) {

    mp.clear();
    vector<int> curr = random_generate(size);

    while(1) {

	int curr_value = attack_of_number(curr);

	vector<int> next;

	int next_value = INT_MAX;

	for(int i=0; i<size; i++) {

	    for(int j=1; j<=size/2; j++) {
		vector<int> tmp = curr;
		swap(tmp[i],tmp[(i+j)%size]);
		if(next_value > attack_of_number(tmp)) {
		    next_value = attack_of_number(tmp);
		    next.clear();
		    next = tmp;
		}
	    }

	}

	if(next_value < curr_value) {
	    curr_value = next_value;
	    curr = next;
	}else {
	    return curr;
	}

    }

}

int solve_by_hc(int size, int times, int &atk) {
    int cnt = 0;

    for(int i=0; i<times; i++) {
	int atk_tmp = attack_of_number(hc(size));
	atk+=atk_tmp;
	if(atk_tmp == 0) {
	    cnt++;
	    cout << "YES" << endl;
	}else {
	    cout << "NO" << endl;
	}
	
    }

    return cnt;
}

vector<int> mutation(vector<int> curr) {

    int size = curr.size();

    int s = rand()%size;
    int e = rand()%size;

    swap(curr[s], curr[e]);

    return curr;

}

vector<int> crossover(const vector<int> &a, const vector<int> &b) {
    int size = a.size();

    int start = rand()%size;

    vector<int> c(size);
    fill(c.begin(), c.end(), -1);
    int used[size];
    fill(used, used+size, 0);


    for(int i=0; i<size/2; i++) {
	int idx = (start+i)%size;
	c[idx] = a[idx];
	used[c[idx]] = 1;
    }


    int cnt_b, cnt_c;
    cnt_b = cnt_c = 0;

    while(cnt_b<size && cnt_c<size) {
	if(c[cnt_c] != -1) {
	    cnt_c++;
	}
	else if(used[b[cnt_b]] == 1) {
	    cnt_b++;
	}else {
	    c[cnt_c] = b[cnt_b];
	    cnt_c++;
	    cnt_b++;
	}
    }

    return c;

}

bool cmp(const vector<int> a, const vector<int> b) {
    return attack_of_number(a)<attack_of_number(b);
}

vector<int> GA(int size, int group, int round) {
    vector< vector<int> > G;


    for(int i=0; i<group; i++) {
	G.push_back(random_generate(size));
    }

    sort(G.begin(), G.end(), cmp);

    while(round--) {

	vector< vector<int> > NEW_G = G;
	G.clear();	

	for(int i=0; i<size; i++) {
	    for(int j=0; j<size; j++) {
		if(i==j) continue;

		vector<int> NEW = crossover(NEW_G[i],NEW_G[j]);

		NEW = mutation(NEW);

		NEW_G.push_back(NEW);

	    }
	}


	sort(NEW_G.begin(), NEW_G.end(), cmp);

	if(attack_of_number(NEW_G[0]) == 0) {
	    return NEW_G[0];
	}

	for(int i=0; i<group; i++) {
	    G.push_back(NEW_G[i]);
	}

    }

    return G[0];

}

int solve_by_GA(int size, int times, int &atk, int group = 50, int round = 100) {
    int cnt = 0;


    for(int i=0; i<times; i++) {
	vector<int> v = GA(size, group, round);
	atk+=attack_of_number(v);
	if(attack_of_number(v) == 0) {
	    cnt++;
	    cout << "YES\n";
	}else {
	    cout << "NO\n";
	}
    }

    return cnt;
}



int main() {

    srand(time(NULL));

    int n;
    cin >> n;

    int mode;
    cin >> mode;

    int times = 30;

    int cnt = 0;
    int atk = 0;

    while(times--) {
	if(mode == 1) {
	    vector<int> ret = solve_by_dfs(n);
	    atk += attack_of_number(ret);
	    if(attack_of_number(ret) == 0) cnt++;
	} else if(mode == 2) {
	    cnt+=solve_by_hc(n, 1, atk);
	} else {
	    cnt+=solve_by_GA(n, 1, atk);
	}
    }

    cout << "In mode " << mode << endl;
    cout << "Success rate: " << ((double)cnt/30)*100 << "%" << endl;
    cout << "Averge attack number " << (double)atk/30 << endl;

    


    return 0;
}
