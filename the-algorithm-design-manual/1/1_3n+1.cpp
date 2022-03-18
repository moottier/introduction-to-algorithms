#include <iostream>
using namespace std;

void swap(long long &a, long long &b) {
    long long t { a };
    a = b;
    b = t;
}

// solve collatz conjecture for numbers in input range
// return inputs and max in set count to reach 1
// Input:    1 10
//          10  1
// Output:   1 10 20
//          10  1 20
int main(int argc, char *argv[]) {
    long long in1, in2, col_val, n_curr, n_max;
    long long in_low, in_high;
    while(cin >> in1 >> in2) {
        n_max = 0; in_low = in1; in_high = in2;    // store to output later
        
        if (in1 > in2) { swap(in1, in2); }
        
        for(long long i = in1; i <= in2; i++) {   
            n_curr = 0;
            col_val = i;
            while(col_val != 1) {
                if (col_val % 2 == 1)
                    col_val = (3 * col_val) + 1;
                else
                    col_val /= 2;
                n_curr++;
            }
            if (n_curr > n_max) 
                n_max = n_curr;
        }
        cout << in_low << ' ' << in_high << ' ' << (n_max + 1) << '\n';
    }
    return 0;
}