#include <bits/stdc++.h>
using namespace std;
const int N = 6;
int men[N][N], women[N][N];
bool woman_attached[N];
int next_opportunity[N];
vector<int> proposals[N];

/*

    - Theorem: The defferred acceptance algorithm always terminates
    - Proof: once a man has at least one proposal, that man will
    never have an empty queue of women. At the start of each round
    the women rejected go to the next candidate in their list.
    Since there are only a finite number of candidates, the
    proposals will never continue indifinetely. Since no man
    ever keeps more than one women, and since the numbers of women 
    and man are equal, eventually every man will have a proposal.

    - Theorem: The deffered acceptance algorithm always produces
    a stable assignment.
    - Proof: Suposse a man A, he's unhappy with the mate, X,
    assigned by the defferred acceptance algorithm. There may be
    a woman, Y, that A likes better than X. However, since women
    propose in the order of their preferences, Y must never have
    proposed to A (otherwise, A would have rejected X in favor of Y).
    If Y never proposed to A, then Y must have been accepted by a 
    man, B, that Y prefers to A. Thus, A will be unable to find a
    woman (ranked higher than X) who is willing to elope. The
    conclusion is that no man will be able to find a
    higher-ranking women who is willing to elope.

*/
int defferred_acceptance() {
    int round = 0;
    int pending_proposals = N;
    fill(next_opportunity, next_opportunity + N, -1);
    while(pending_proposals > 0) {
        for(int i = 0; i < N; ++i) {
            if(!woman_attached[i]) {
                next_opportunity[i] += 1;
                assert(next_opportunity[i] < N);
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
    int total_rounds = defferred_acceptance();
    printf("total_rounds: %d\n", total_rounds);
    return 0;
}
