#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Soo{
    int x, y, cost;
};

int main(int argc, char** argv)
{
	int T;
    cin >> T;
	for(int test_case = 1; test_case <= T; ++test_case)
	{
        int ans = -1;
        int N, M;
        cin >> N >> M;
        vector<string> map(N);
        for(int i = 0; i < N; i++)
        {
            string line;
            cin >> line;
            map[i] = line;
        }


        pair<int, int> dStart;
        pair<int, int> sStart;
        vector<pair<int, int>> demon;

        //find D and S and *
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                if(map[i][j] == 'D')
                {
                    dStart.first = i;
                    dStart.second = j;
                }
                else if(map[i][j] == 'S')
                {
                    sStart.first = i;
                    sStart.second = j;
                }
                else if(map[i][j] == '*')
                {
                    demon.push_back({i, j});
                }
            }
        }

        //make demon movement
        vector<vector<int>> demonMap(N, vector<int>(M, 0));
        queue<pair<int, int>> demonQueue;
        for(int i = 0; i < demon.size(); i++)
        {
            demonQueue.push({demon[i].first, demon[i].second});
        }
        while(!demonQueue.empty())
        {
            int curx = demonQueue.front().first;
            int cury = demonQueue.front().second;
            demonQueue.pop();

            for(int i = 0; i < 4; i++)
            {
                int newx = curx + dx[i];
                int newy = cury + dy[i];

                if(newx >= 0 && newx < N && newy >= 0 && newy < M)
                {
                    if(map[newx][newy] == 'X' || map[newx][newy] == 'D' || demonMap[newx][newy] != 0)
                        continue;
                    demonMap[newx][newy] = demonMap[curx][cury] + 1;
                    demonQueue.push({newx, newy});
                }
            }
        }
        for(int i = 0; i < demon.size(); i++)
        {
            demonMap[demon[i].first][demon[i].second] = 0;
        }
        demonMap[dStart.first][dStart.second] = 987654321;


        // move S by BFS
        bool found = false;
        queue<Soo> Q;
        Q.push({sStart.first, sStart.second, 0});
        while(!Q.empty())
        {
            Soo cur = Q.front();
            Q.pop();
            for(int i = 0; i < 4; i++)
            {
                int newx = cur.x + dx[i];
                int newy = cur.y + dy[i];
                int newCost = cur.cost + 1;
                if(newx >= 0 && newx < N && newy >= 0 && newy < M )
                {
                    if(map[newx][newy] == '.')
                    {
                        if(newCost < demonMap[newx][newy])
                        {
                            Q.push({newx, newy, newCost});
                        }
                    }
                    else if(map[newx][newy] == 'D')
                    {
                        found = true;
                        ans = newCost;
                        break;
                    }
                }
            }
            if(found == true)
                break;
        }
        if(ans == -1)
            cout << "#" << test_case << " " << "GAME OVER\n";
        else
            cout << "#" << test_case << " " << ans<<"\n";

	}
	return 0;
}



/*
1
5 3
D*S
.X.
.X.
.X.
...

// // */
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
// // ........*.........................................
// // .........*........................................
// // ..........*.......................................
// // ...........*......................................
// // ............*.....................................
// // .............*....................................
// // ..............*...................................
// // ...............*..................................
// // ...............*.................................D
// // ................S..............................*..
// // ..................................................
// // ..................................................
// // ..................................................
// // ..................................................
