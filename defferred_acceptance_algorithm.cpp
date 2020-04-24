#include <bits/stdc++.h>
using namespace std;
const int N = 6;
int men[N][N], women[N][N];
bool woman_attached[N];
int next_opportunity[N];
vector<int> proposals[N];

int deferred_acceptance() {
    int round = 0;
    cout<<"Start rounds\n";
    int pending_proposals = N;
    fill(next_opportunity, next_opportunity + N, -1);
    while(pending_proposals > 0) {
        for(int i = 0; i < N; ++i) {
            if(!woman_attached[i]) {
                next_opportunity[i] += 1;
                assert(next_opportunity[i] <= N);
                proposals[women[i][next_opportunity[i]] - 1].emplace_back(i + 1);
            }
        }
        pending_proposals = N;
        for(int i = 0; i < N; ++i) {
            int best = -1;
            for(int j = 0; j < N; ++j) {
                for(int k : proposals[i]) {
                    if(men[i][j] == k) {
                        best = k; break;
                    }
                }
            }
            for(int j : proposals[i]) {
                if(j == best) woman_attached[j - 1] = true;
                else woman_attached[j - 1] = false;
            }
            if(best != -1) {
                pending_proposals--;
                proposals[i].clear();
                proposals[i].emplace_back(best);
            }
        }
        round += 1;
    }
    for(int i = 0; i < N; ++i) {
        printf("%d -> %d\n", i + 1, proposals[i][0]);
    }
    return round;
}

int main() {
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    for(int i = 0; i < N; ++i) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(perm.begin(), perm.end(), std::default_random_engine(seed));
        for(int j = 0; j < N; ++j) men[i][j] = perm[j];
    }
    for(int i = 0; i < N; ++i) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(perm.begin(), perm.end(), std::default_random_engine(seed));
        for(int j = 0; j < N; ++j) women[i][j] = perm[j];
    }
    int total_rounds = deferred_acceptance();
    printf("total_rounds: %d\n", total_rounds);
    return 0;
}
