// 有一个面积为负的是所有多边形面积和
typedef vector<Point> Polygon;
double PolygonArea(Polygon poly)
{
    double area = 0;
    int n = poly.size();
    for(int i = 1; i < n-1; i++)
        area += Cross(poly[i]-poly[0], poly[(i+1)%n]-poly[0]);
    return area/2;
}

struct Edge
{
    int from, to; // 起点，终点，左边的面编号
    double ang;
    Edge(int f,int t,double a):from(f),to(t),ang(a) {}
};

const int maxn = 10000 + 10; // 最大边数

// 平面直线图（PSGL）实现
struct PSLG
{
    int n, m, face_cnt;//face_cnt 面数
    double x[maxn], y[maxn];
    vector<Edge> edges;//储存边
    vector<int> G[maxn];//指向边
    int vis[maxn*2];  // 每条边是否已经访问过
    int left[maxn*2]; // 左面的编号
    int prev[maxn*2]; // 相同起点的上一条边（即顺时针旋转碰到的下一条边）的编号

    vector<Polygon> faces;//faces 储存面
    double area[maxn]; // 每个polygon的面积

    void init(int n)
    {
        this->n = n;
        for(int i = 0; i < n; i++)
            G[i].clear();
        edges.clear();
        faces.clear();
    }

    // 有向线段from->to的极角
    double getAngle(int from, int to)
    {
        return atan2(y[to]-y[from], x[to]-x[from]);
    }

    void AddEdge(int from, int to)
    {
        edges.push_back((Edge){ from, to, getAngle(from, to)});
        edges.push_back((Edge){ to, from, getAngle(to, from)});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    // 找出faces并计算面积
    void Build()
    {
        for(int u = 0; u < n; u++)
        {
            // 给从u出发的各条边按极角排序
            int d = G[u].size();
            for(int i = 0; i < d; i++)
                for(int j = i+1; j < d; j++) // 这里偷个懒，假设从每个点出发的线段不会太多
                    if(edges[G[u][i]].ang > edges[G[u][j]].ang)
                        swap(G[u][i], G[u][j]);
            for(int i = 0; i < d; i++)
                prev[G[u][(i+1)%d]] = G[u][i];
        }

        memset(vis, 0, sizeof(vis));
        face_cnt = 0;
        for(int u = 0; u < n; u++)
            for(int i = 0; i < G[u].size(); i++)
            {
                int e = G[u][i];
                if(!vis[e])   // 逆时针找圈
                {
                    face_cnt++;
                    Polygon poly;
                    for(;;)
                    {
                        vis[e] = 1;
                        left[e] = face_cnt;
                        int from = edges[e].from;
                        poly.push_back(Point(x[from], y[from]));
                        e = prev[e^1];
                        if(e == G[u][i])
                            break;
                        assert(vis[e] == 0);
                    }
                    faces.push_back(poly);
                }
            }

        for(int i = 0; i < faces.size(); i++)
        {
            area[i] = PolygonArea(faces[i]);
        }
    }
};
// 利用PSLG求各个多边形的面积

#include <bits/stdc++.h>
#define mem(ar,num) memset(ar,num,sizeof(ar))
#define me(ar) memset(ar,0,sizeof(ar))
#define lowbit(x) (x&(-x))
#define forn(i,n) for(int i = 0;i < n; ++i)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int    prime = 999983;
const int    INF = 0x7FFFFFFF;
const LL     INFF = 0x7FFFFFFFFFFFFFFF;
const double pi = acos(-1.0);
const double inf = 1e18;
const double eps = 1e-6;
const LL     mod = 1e9 + 7;
struct Point
{
	double x, y;

	Point(double x = 0, double y = 0): x(x), y(y) {}

};
typedef Point Vector;
Vector operator + (Vector A, Vector B)
{
	return Vector(A.x + B.x, A.y + B.y);
}
Vector operator - (Vector A, Vector B)
{
	return Vector(A.x - B.x, A.y - B.y);
}
Vector operator / (Vector A, double p)
{
	return Vector(A.x / p, A.y / p);
}
Vector operator * (Vector A, double p)
{
	return Vector(A.x * p, A.y * p);
}
int dcmp(double x)
{
	if (fabs(x) < eps)
		return 0;
	else
		return x < 0 ? -1 : 1;
}
bool operator < (const Point &a, const Point &b)
{
	if (dcmp(a.x - b.x) == 0)
		return a.y < b.y;
	else
		return a.x < b.x;
}


double Cross(Vector A, Vector B)
{
	return A.x * B.y - A.y * B.x;
}
//调用前确保直线有唯一交点，当且仅当Cross(v,w)非0
Point Get_Line_Intersection(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	double t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}
// Point getLL(Point k1, Point k2, Point k3, Point k4) {
// 	double w1 = Cross(k1 - k3, k4 - k3), w2 = Cross(k4 - k3, k2 - k3); return (k1 * w2 + k2 * w1) / (w1 + w2);
// }
typedef vector<Point> Polygon;
double PolygonArea(Polygon poly)
{
	double area = 0;
	int n = poly.size();
	for (int i = 1; i < n - 1; i++)
		area += Cross(poly[i] - poly[0], poly[(i + 1) % n] - poly[0]);
	return area / 2;
}

struct Edge
{
	int from, to; // 起点，终点，左边的面编号
	double ang;
	Edge(int f, int t, double a): from(f), to(t), ang(a) {}
};

const int maxn = 1e6 + 10; // 最大边数

// 平面直线图（PSGL）实现
struct PSLG
{
	int n, m, face_cnt;//face_cnt 面数
	double x[maxn], y[maxn];
	vector<Edge> edges;//储存边
	vector<int> G[maxn];//指向边
	int vis[maxn * 2]; // 每条边是否已经访问过
	int left[maxn * 2]; // 左面的编号
	int prev[maxn * 2]; // 相同起点的上一条边（即顺时针旋转碰到的下一条边）的编号

	vector<Polygon> faces;//faces 储存面
	double area[maxn]; // 每个polygon的面积

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i < n; i++)
			G[i].clear();
		edges.clear();
		faces.clear();
	}

	// 有向线段from->to的极角
	double getAngle(int from, int to)
	{
		return atan2(y[to] - y[from], x[to] - x[from]);
	}

	void AddEdge(int from, int to)
	{
		edges.push_back((Edge) { from, to, getAngle(from, to)});
		edges.push_back((Edge) { to, from, getAngle(to, from)});
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	// 找出faces并计算面积
	void Build()
	{
		for (int u = 0; u < n; u++)
		{
			// 给从u出发的各条边按极角排序
			int d = G[u].size();
			for (int i = 0; i < d; i++)
				for (int j = i + 1; j < d; j++) // 这里偷个懒，假设从每个点出发的线段不会太多
					if (edges[G[u][i]].ang > edges[G[u][j]].ang)
						swap(G[u][i], G[u][j]);
			for (int i = 0; i < d; i++)
				prev[G[u][(i + 1) % d]] = G[u][i];
		}

		memset(vis, 0, sizeof(vis));
		face_cnt = 0;
		for (int u = 0; u < n; u++)
			for (int i = 0; i < G[u].size(); i++)
			{
				int e = G[u][i];
				if (!vis[e])  // 逆时针找圈
				{
					face_cnt++;
					Polygon poly;
					for (;;)
					{
						vis[e] = 1;
						left[e] = face_cnt;
						int from = edges[e].from;
						poly.push_back(Point(x[from], y[from]));
						e = prev[e ^ 1];
						if (e == G[u][i])
							break;
						assert(vis[e] == 0);
					}
					faces.push_back(poly);
				}
			}

		for (int i = 0; i < faces.size(); i++)
		{
			area[i] = PolygonArea(faces[i]);
		}
	}
};
PSLG pslg;
// const int maxn = 1000+10;
Point p[maxn], v[maxn];
vector<Point> vec[maxn];
// const int maxn =

Point ps[maxn];
vector<int> G[maxn];
bool cmp2(const int &a, const int &b) {
	return ps[a] < ps[b];

}
int main(void)
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].x >> p[i].y >> v[i].x >> v[i].y;
		v[i]  = v[i] - p[i];
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (dcmp(Cross(v[i] , v[j] )) == 0) continue;
			ps[cnt] = Get_Line_Intersection(p[i], v[i], p[j], v[j]);
			// ps[cnt] = getLL(p[i], v[i], p[j], v[j]);
			G[i].push_back(cnt);
			G[j].push_back(cnt);
			++cnt;
		}
		sort(G[i].begin(), G[i].end(), cmp2);
		// for (auto c : G[i])
		// 	cout << ps[c].x << " ";
		// cout << endl;
	}
	// cout << cnt << endl;

	pslg.init(cnt);
	// cout<<c
	for (int i = 0; i < cnt; ++i)
		pslg.x[i] = ps[i].x, pslg.y[i] = ps[i].y;
	// for (int i = 0; i < cnt; ++i) {
	// 	// cout << pslg.x[i] << " " << pslg.y[i] << endl;
	// 	printf("%.6f %.6f\n", pslg.x[i], pslg.y[i]);
	// }
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < G[i].size() - 1; j++) {
			pslg.AddEdge(G[i][j], G[i][j + 1]);
			// cout << G[i][j] << " " << G[i][j + 1] << endl;
		}
	}
	int m;
	pslg.Build();
	sort(pslg.area, pslg.area + pslg.face_cnt);
	printf("%d %.5f %.5f\n", pslg.face_cnt - 1, pslg.area[pslg.face_cnt - 1], pslg.area[1]);
	scanf("%d", &m); int k;
	// cout << pslg.face_cnt << endl;
	while (m--) {
		scanf("%d", &k);
		if (k < pslg.face_cnt)printf("%.6f\n", pslg.area[pslg.face_cnt - k]);
		else printf("Invalid question\n");
	}




	return 0;
}
