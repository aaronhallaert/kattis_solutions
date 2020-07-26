#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// current best solution
int min_value = 99999;

class Stage {
    int requested;
    int value;
    int iteration;
    int n1;
    int n5;
    int n10;

    vector<Stage *> children;

    Stage(int requested, int n1, int n5, int n10, int value, int iteration) {
        this->requested= requested;
        this->n1 = n1;
        this->n5 = n5;
        this->n10 = n10;
        this->value = value;
        this->iteration = iteration;
    }

    Stage *pay_10() {
        if (this->n10 == 0) {
            return nullptr;
        } else {
            return new Stage(requested, n1 + 2, n5, n10 - 1, value + 1, iteration + 1);
        }
    }

    Stage *pay_2x5() {
        if (this->n5 < 2) {
            return nullptr;
        } else {
            return new Stage(requested, n1 + 2, n5 - 2, n10, value + 2, iteration + 1);
        }
    }

    Stage *pay_5_3x1() {
        if (this->n1 < 3 || this->n5 < 1) {
            return nullptr;
        } else {
            return new Stage(requested, n1 - 3, n5 - 1, n10, value + 4, iteration + 1);
        }
    }

    Stage *pay_8x1() {
        if (this->n1 < 8) {
            return nullptr;
        } else {
            return new Stage(requested, n1 - 8, n5, n10, value + 8, iteration + 1);
        }
    }

    bool operator<(const Stage &other) const{
        return value < other.value;
    }



public:
    Stage(int requested, int n1, int n5, int n10) {
        this->requested = requested;
        this->n1 = n1;
        this->n5 = n5;
        this->n10 = n10;
        this->value = 0;
        this->iteration = 0;
    }

    ~Stage() {
        Stage *st;
        for(auto & it : children) {
            st = it;
            delete st;
        }
    }

    void solve() {
        if (iteration == requested && (min_value > this->value)) {
            min_value = this->value;
            return;
        }
        else if(this->value < min_value){
            Stage *a = this->pay_10();
            if (a) {
                children.push_back(a);
            }
            Stage *b = this->pay_2x5();
            if (b) {
                children.push_back(b);
            }
            Stage *c = this->pay_5_3x1();
            if (c) {
                children.push_back(c);
            }

            Stage *d = this->pay_8x1();
            if (d) {
                children.push_back(d);
            }
        }

        if (children.empty()) {
            return;
        } else {
            std::sort(children.begin(), children.end());
            for (Stage *stage: children) {
                stage->solve();
            }
        }
    }
};

int main() {

    // create initial stage with input values
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        int cokes;
        int n1;
        int n5;
        int n10;
        cin >> cokes >> n1 >> n5 >> n10;
        auto* initial= new Stage(cokes, n1, n5, n10);
        initial->solve();
        cout<<min_value<<endl;

        // reset
        delete initial;
        min_value= 9999;
    }

}


