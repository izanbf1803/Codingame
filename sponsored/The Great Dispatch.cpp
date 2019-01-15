#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <array>
#include <ctime>
#include <cstdlib>
using namespace std;

#define D(x) cerr << #x << " = " << x << ", "
#define DOUBLE_INF (std::numeric_limits<double>::infinity())

typedef unsigned int uint;
typedef unsigned long ul;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef unsigned char byte;

template<typename T> using V = vector<T>;
template<typename T, typename U> using P = pair<T,U>;

const clock_t TIMED_OUT = 45 * CLOCKS_PER_SEC; // X seconds
const double TRUCK_MAX_V = 100.0;
const int TRUCK_N = 100;
const int MAX_N = 3300;

struct Box {
    double w;
    double v;
    int index;
    int truck;
};

struct Truck {
    double w;
    double v;
    int index;
    array<int, MAX_N> boxes;
    int bsize;
};

clock_t start;
int n;
array<Box, MAX_N> box;
array<Truck, TRUCK_N> truck;
double current_delta;
int g_seed;

bool operator<(const Box& a, const Box& b)
{
    if (a.w == b.w) return a.v > b.v;
    return a.w > b.w;
}
bool operator<(const Truck& a, const Truck& b)
{
    if (a.w == b.w) return a.v > b.v;
    return a.w > b.w;
}

inline int fastrand()
{ 
  g_seed = (214013*g_seed+2531011); 
  return (g_seed>>16)&0x7FFF; 
} 

#define FAST_MOD(k,m) ((k) < (m) ? (k) : (k) % (m))
inline int random(int min_, int max_)
{
    int r = fastrand();
    int m = max_ - min_ + 1;
    return FAST_MOD(r, m) + min_;
}

double calc_delta() 
{
    V<double> weights(TRUCK_N, 0.0);
    V<double> volumes(TRUCK_N, 0.0);
    double max_w = 0;
    double min_w = DOUBLE_INF;
    for (int b = 0; b < n; ++b) {
        int tindex = truck[box[b].truck].index;
        weights[tindex] += box[b].w;
        volumes[tindex] += box[b].v;
        if (volumes[tindex] > TRUCK_MAX_V) {
            D(tindex); D(volumes[tindex]) << endl;
            return DOUBLE_INF;
        }
    }
    for (int b = 0; b < n; ++b) {
        int index = truck[box[b].truck].index;
        max_w = max(max_w, weights[index]);
        min_w = min(min_w, weights[index]);
    }
    return max_w - min_w;
}

void print_solution_delta()
{
    cerr << "Success! Delta: " << calc_delta() << endl;
}

P<double,double> max_min_w_calc()
{
    double max_w = truck[0].w;
    double min_w = truck[0].w;
    for (int t = 1; t < TRUCK_N; ++t) {
        max_w = max(max_w, truck[t].w);
        min_w = min(min_w, truck[t].w);
    }
    return make_pair(max_w, min_w);
}

void optimize()
{    
    const int MAX_SWAP = 4;
    
    int bswap;

    if (n < 1500) {
        bswap = random(1, MAX_SWAP);
    }
    else {
        bswap = random(1, MAX_SWAP - 1);
    }
    
    // Ret random non-equal trucks to swap boxes:
    int a, b;
    a = random(0, TRUCK_N-1);
    b = random(0, TRUCK_N-1);
    while (b == a or min(truck[a].boxes.size(), truck[b].boxes.size()) < bswap) {
        a = random(0, TRUCK_N-1);
        b = random(0, TRUCK_N-1);
    }
    
    Truck& ta = truck[a];
    Truck& tb = truck[b];

    int ta_boxes_n = bswap;
    int tb_boxes_n = bswap;
    if (bswap > 1) tb_boxes_n -= random(0, 1);
    
    array<int, MAX_SWAP> ta_b;
    array<int, MAX_SWAP> tb_b;
    
    double ta_v = ta.v;
    double ta_w = ta.w;
    double tb_v = tb.v;
    double tb_w = tb.w;
    
    int ta_size = ta.bsize;
    for (int i = 0; i < ta_boxes_n; ++i) {
        int it = random(0, ta_size-1);
        int index = ta.boxes[it];
        ta_v -= box[index].v;
        ta_w -= box[index].w;
        tb_v += box[index].v;
        tb_w += box[index].w;
        ta_b[i] = index;
        swap(ta.boxes[it], ta.boxes[ta_size-1]); // Move all selected boxes to the end of the vector
        --ta_size;
    }
    
    int tb_size = tb.bsize;
    for (int i = 0; i < tb_boxes_n; ++i) {
        int it = random(0, tb_size-1);
        int index = tb.boxes[it];
        ta_v += box[index].v;
        ta_w += box[index].w;
        tb_v -= box[index].v;
        tb_w -= box[index].w;
        tb_b[i] = index;
        swap(tb.boxes[it], tb.boxes[tb_size-1]); // Move all selected boxes to the end of the vector
        --tb_size;
    }
    
    if (max(ta_v, tb_v) <= TRUCK_MAX_V) {
        double old_ta_w = ta.w;
        double old_tb_w = tb.w;
        ta.w = ta_w;
        tb.w = tb_w;
        
        P<double,double> mm = max_min_w_calc();
        double new_delta = mm.first - mm.second;
    
        if (new_delta < current_delta) {
            current_delta = new_delta;
            // Apply box removal:
            ta.bsize -= ta_boxes_n;
            tb.bsize -= tb_boxes_n;
            // Switch trucks:
            for (int i = 0; i < ta_boxes_n; ++i) {
                box[ta_b[i]].truck = b;
                tb.boxes[tb.bsize] = ta_b[i];
                ++tb.bsize;
            }
            for (int i = 0; i < tb_boxes_n; ++i) {
                box[tb_b[i]].truck = a;
                ta.boxes[ta.bsize] = tb_b[i];
                ++ta.bsize;
            }
            // Apply volume change:
            ta.v = ta_v;
            tb.v = tb_v;
        }
        else {
            // Restore w:
            ta.w = old_ta_w;
            tb.w = old_tb_w;
        }
    }
}

int main()
{
    srand(time(0));
    g_seed = rand();
    start = clock();

    // Read input:
    cin >> n; cin.ignore();
    for (int i = 0; i < TRUCK_N; ++i) {
        truck[i] = {0.0, 0.0, i, array<int, MAX_N>(), 0};
    }
    for (int i = 0; i < n; i++) {
        cin >> box[i].w >> box[i].v; cin.ignore();
        box[i].index = i;
        box[i].truck = -1;
    }
    
    // Generate valid solution before start testing random modifications:
    array<Box, MAX_N> box_sorted;
    copy(box.begin(), box.begin() + n, box_sorted.begin());
    array<Truck, TRUCK_N> truck_sorted;
    copy(truck.begin(), truck.end(), truck_sorted.begin());
    sort(box_sorted.begin(), box_sorted.begin() + n);
    for (int i = 0; i < n; ++i) {
        int b = box_sorted[i].index;
        sort(truck_sorted.begin(), truck_sorted.end());
        for (int j = TRUCK_N-1; j >= 0; --j) {
            int t = truck_sorted[j].index;
            if (truck[t].v + box[b].v <= TRUCK_MAX_V) {
                box[b].truck = t;
                truck[t].boxes[truck[t].bsize] = b;
                ++truck[t].bsize;
                truck[t].w += box[b].w;
                truck[t].v += box[b].v;
                truck_sorted[j].w += box[b].w;
                truck_sorted[j].v += box[b].v;
                break;
            }
        }
    }

    // Calc initial delta:
    P<double,double> max_min_w = max_min_w_calc();
    current_delta = max_min_w.first - max_min_w.second;
    
    // Control time to avoid Time Limit Exception
    while (clock() - start < TIMED_OUT) {
        for (int i = 0; i < 4096; ++i) {
            optimize();
        }
    }

#define OUTPUT_SOLUTION 1
#if OUTPUT_SOLUTION
    cout << truck[box[0].truck].index;
    for (int i = 1; i < n; ++i) {
        cout << ' ' << truck[box[i].truck].index;   
    }
    cout << endl;
#else
    print_solution_delta();
#endif
}