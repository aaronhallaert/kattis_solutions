#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// requested
int mem[151][101][51];

class Problem {
    int cokesToBuy;
    int n1;
    int n5;
    int n10;

    Problem *pay_10() {
        if (this->n10 == 0) {
            return nullptr;
        } else {
            return new Problem(n1 + 2, n5, n10 - 1, cokesToBuy - 1);
        }
    }

    Problem *pay_2x5() {
        if (this->n5 < 2) {
            return nullptr;
        } else {
            return new Problem(n1 + 2, n5 - 2, n10, cokesToBuy - 1);
        }
    }

    Problem *pay_5_3x1() {
        if (this->n1 < 3 || this->n5 < 1) {
            return nullptr;
        } else {
            return new Problem(n1 - 3, n5 - 1, n10, cokesToBuy - 1);
        }
    }

    Problem *pay_8x1() {
        if (this->n1 < 8) {
            return nullptr;
        } else {
            return new Problem(n1 - 8, n5, n10, cokesToBuy - 1);
        }
    }

    Problem *pay_10_3x1(){
        if (this->n10 < 1 || this->n1<3) {
            return nullptr;
        } else {
            return new Problem(n1 - 3, n5+1, n10-1, cokesToBuy - 1);
        }
    }

public:
    Problem(int n1, int n5, int n10, int cokesToBuy) {
        this->n1 = n1;
        this->n5 = n5;
        this->n10 = n10;
        this->cokesToBuy = cokesToBuy;
    }

    ~Problem() = default;

    int solve() {
        // if not possible to pay, return max
        if (cokesToBuy * 8 - n5 * 5 - n10 * 10 - n1 > 0) {
            return 99999;
        }

        // return if we already have a solution for this problem and we can pay
        int memValue = mem[cokesToBuy][n5][n10];
        if (memValue != 0) {
            return memValue;
        }

        // if we only have no drinks to buy, return
        if (cokesToBuy==0){
            return 0;
        }

        // if we need more than one drink, we have multiple possible paths to walk
        vector<int> solutions;
        // 4 possible ways to continue
        Problem *a = this->pay_10();
        Problem *b = this->pay_2x5();
        Problem *c = this->pay_5_3x1();
        Problem *d = this->pay_8x1();
        Problem *e = this->pay_10_3x1();
        if (a) {
            solutions.push_back(a->solve()+1);
            delete a;
        }
        if (b) {
            solutions.push_back(b->solve()+2);
            delete b;
        }
        if (c) {
            solutions.push_back(c->solve()+4);
            delete c;
        }
        if (d) {
            solutions.push_back(d->solve()+8);
            delete d;
        }
        if(e){
            solutions.push_back(e->solve()+4);
            delete e;
        }

        // take best one (least cost)
        sort(solutions.begin(), solutions.end());
        mem[cokesToBuy][n5][n10] = solutions.front();
        return solutions.front();
    }
};

int main() {

    // create initial stage with input values
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        for(auto &x: mem){
            for(auto&y:x){
                fill_n(y, 51,0);
            }
        }
        int cokes;
        int n1;
        int n5;
        int n10;

        cin >> cokes >> n1 >> n5 >> n10;
        auto *initial = new Problem(n1, n5, n10, cokes);
        int solution = initial->solve();
        cout << solution << endl;

        // reset
        delete initial;
    }

}


