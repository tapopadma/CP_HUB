#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<char> vc;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const double EPS = 1e-9;
const int INF = 1 << 29;
#define mp make_pair
#define el putchar('\n')
#define sp putchar(' ')
#define Fill(a,val) memset(a,val,sizeof a)
#define all(a) a.begin(),a.end()
#ifdef ONLINE_JUDGE
#define tr(a, it) for (decltype(a.begin()) it = a.begin(); it != a.end(); ++it)
#else
#define tr(a, it) for (typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#endif
#define in(n) scanf("%d",&n)
#define inl(n) scanf("%I64d",&n)
#define out(n) printf("%d",n);
#define outl(n) printf("%I64d",n);

int const NN = 1e6 + 6;

vector<pi> g[NN];
int disc[NN], low[NN];
bool stackMember[NN];
stack<int> st;
int timer = 0;

void trajan(int node){
  disc[node] = ++timer;
  low[node] = timer;
  st.push(node);
  stackMember[node] = true;
  tr(g[node], it){
    int adj = (*it).first;
    if(disc[adj] == -1){
      trajan(adj);
      low[node] = min(low[node], low[adj]);
    }
    else if(stackMember[adj]){
      low[node] = min(low[node], disc[adj]);
    }
  }
  if(low[node] == disc[node]){//root of SCC
    while(st.top() != node){
      int cur = st.top();st.pop();
      stackMember[cur] = false;
      cout<<cur<<" ";
    }
    cout<<node;el;st.pop();stackMember[node] = false;
  }
}

int main(){
  int n, m;
  in(n);in(m);
  for(int i=1;i<=m;++i){
    int x, y, w;
    in(x);in(y);in(w);
    g[x].push_back(mp(y, w));
  }
  for(int i=1;i<=n;++i){
    disc[i] = low[i] = -1;
    stackMember[i] = false;
  }
  for(int i=1;i<=n;++i){
    if(disc[i] == -1){//not visited
      trajan(i);
    }
  }
  return 0;
}
