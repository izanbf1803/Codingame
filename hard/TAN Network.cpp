#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_map>

using namespace std;

const double RADIANS = M_PI / 180;

typedef pair<double, int> p_di;

typedef struct {
    string sid, name;
    double lat, lon;
    vector<int> adj;
} Stop;

struct cmp {
    bool operator()(p_di a, p_di b) {
        return not (a.first < b.first); // Invert because priority_queue in c++ is max-heap
    }
};

double distance(const Stop& a, const Stop& b)
{
    double x = (b.lon - a.lon) * cos((a.lat + b.lat) / 2 * RADIANS);
    double y = (b.lat - a.lat);
    return sqrt(x*x + y*y) * 6371;
}

vector<string> string_split(const string& s, const char delimiter) 
{
    vector<string> output;
    size_t start = 0;
    size_t end = s.find(delimiter);
    
    while (end <= string::npos) {
	    output.push_back(s.substr(start, end - start));
	    if (end == string::npos) break;
    	start = end + 1;
    	end = s.find(delimiter, start);
    }
    
    return output;
}

Stop stop_from_input(const string& in)
{
    Stop s;
    vector<string> fields = string_split(in, ',');
    
    s.sid = fields[0];
    s.name = fields[1];
    s.lat = stod(fields[3]);
    s.lon = stod(fields[4]);
    
    return s;
}

vector<int> reconstruct_path(const vector<int>& from, int end)
{
    vector<int> path;
    path.push_back(end);
    int current = end;
    
    while (from[current] != -1) {
        current = from[current];
        path.push_back(current);
    }
    
    return path;
}

vector<int> Dijkstra(const vector<Stop>& g, int start, int end)
{
    priority_queue<p_di, vector<p_di>, cmp> q;
    vector<int> from(g.size(), -1);
    vector<bool> visited(g.size(), false);
    vector<int> dist(g.size(), 2147483647);
    
    dist[start] = 0;
    q.push(p_di(0, start));

    while (not q.empty()) {
        int c = q.top().second;
        q.pop();
        visited[c] = true;  
        
        if (c == end) return reconstruct_path(from, end);
            
        for (int v : g[c].adj) {
            double d = distance(g[c], g[v]);
            if (not visited[v] and dist[v] > dist[c] + d) {
                dist[v] = dist[c] + d;
                from[v] = c;
                q.push(p_di(dist[v], v));
            }
        }
    }
    
    return vector<int>();
}

int main()
{   
    string start, end; // start and end (id)
    int N, M;
    
    getline(cin, start);
    getline(cin, end);
    cin >> N; cin.ignore();
    
    vector<Stop> g(N);
    unordered_map<string, int> sid_to_id;

    for (int i = 0; i < N; ++i) {
        string in;
        Stop s;
        
        getline(cin, in);
        
        s = stop_from_input(in);
        g[i] = s;
        sid_to_id[s.sid] = i;
    }
    
    cin >> M; cin.ignore();
    
    for (int i = 0; i < M; ++i) {
        string a, b;
        cin >> a >> b;
        int aid = sid_to_id[a];
        int bid = sid_to_id[b];
        g[aid].adj.push_back(bid);
    }
    
    vector<int> path = Dijkstra(g, sid_to_id[start], sid_to_id[end]);
    
    if (path.size() > 0) {
        for (int i = path.size() - 1; i >= 0; --i) {
            for (int j = 1; j < g[path[i]].name.size() - 1; ++j) {
                cout << g[path[i]].name[j];  
            }
            cout << endl;
        }
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
}
