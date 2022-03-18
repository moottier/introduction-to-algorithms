#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Exercise 4.1-2, 4.1-3
// Solve max subarray problem by brute force
// Runs in O(n2)
tuple<int, int, int> max_subarray_brute(vector<int> arr, int low, int high) {
    int max_sum{ arr.at(low) }, left, right, sum;
    for(int l = low; l <= high; l++) {
        sum = 0;
        for (int h = l; h <= high; h++) {
            sum += arr.at(h);
            if (sum >= max_sum ) { max_sum = sum; left = l; right = h; }
        }
    }
    return tuple<int, int, int>{max_sum, left, right};
}

// Exercise 4.1-3
// Solve max subarray problem by recursion (divide & conquer)
// Runs in O(n lg n)
tuple<int, int, int> find_max_crossing_subarray(vector<int> arr, int low, int mid, int high) {
    int sum{0}, left_sum{ arr.at(mid) }, right_sum{ arr.at(mid + 1) };
    int max_left{mid}, max_right{mid + 1};
    
    for (int j = mid; j > low; j--) {
        sum = sum + arr.at(j);
        if (sum > left_sum) {
            left_sum = sum;
            max_left = j;
        }
    }

    sum = 0;
    for (int k = (mid + 1); k < high; k++) {
        sum = sum + arr.at(k); 
        if (sum > right_sum) {
            right_sum = sum;
            max_right = k;
        }
    }
    
    return tuple<int, int, int>{left_sum + right_sum, max_left, max_right};
}
tuple<int, int, int> max_subarray_divide(vector<int> arr, int low, int high) {    
    int mid;
    tuple<int, int, int> left_tup, right_tup, mid_tup;

    if(low == high) { return tuple<int, int, int>{arr.at(low), low, high}; }
    else {
        mid = floor((low + high) / 2);
        left_tup = max_subarray_divide(arr, low, mid);
        right_tup = max_subarray_divide(arr, mid + 1, high);
        mid_tup = find_max_crossing_subarray(arr, low, mid, high);
    }
    if ((get<0>(left_tup) >= get<0>(right_tup)) && (get<0>(left_tup) >= get<0>(mid_tup))) { 
        return left_tup; 
    } else if ((get<0>(right_tup) >= get<0>(left_tup)) && (get<0>(right_tup) >= get<0>(mid_tup))) { 
        return right_tup; 
    } 
    return mid_tup;
}

// Exercise 4.1-4
// Solve max subarray problem by recursion (divide & conquer)
// If only negatives in array then return empty array
// Runs in O(n lg n)
tuple<int, int, int> find_max_crossing_subarray_allow_empty_return(vector<int> arr, int low, int mid, int high) {
    int sum{0}, left_sum{ arr.at(mid) }, right_sum{ arr.at(mid + 1) };
    int max_left{mid}, max_right{mid + 1};
    
    for (int j = mid; j > low; j--) {
        sum = sum + arr.at(j);
        if (sum > left_sum) {
            left_sum = sum;
            max_left = j;
        }
    }

    sum = 0;
    for (int k = (mid + 1); k < high; k++) {
        sum = sum + arr.at(k); 
        if (sum > right_sum) {
            right_sum = sum;
            max_right = k;
        }
    }
    if ((left_sum + right_sum) > 0) { return tuple<int, int, int>{left_sum + right_sum, max_left, max_right}; }
    return tuple<int, int, int>{0, 0, 0};
}
tuple<int, int, int> max_subarray_divide_allow_empty_return(vector<int> arr, int low, int high) {    
    int mid, v;
    tuple<int, int, int> left_tup, right_tup, mid_tup;

    if(low == high) { return tuple<int, int, int>{arr.at(low), low, high}; }
    else {
        mid = floor((low + high) / 2);
        left_tup = max_subarray_divide(arr, low, mid);
        right_tup = max_subarray_divide(arr, mid + 1, high);
        mid_tup = find_max_crossing_subarray(arr, low, mid, high);
    }
    if ((get<0>(left_tup) >= get<0>(right_tup)) && (get<0>(left_tup) >= get<0>(mid_tup))) { 
        if (get<0>(left_tup) > 0) { return left_tup; }
        return tuple<int, int, int>{0, 0, 0};

    } else if ((get<0>(right_tup) >= get<0>(left_tup)) && (get<0>(right_tup) >= get<0>(mid_tup))) { 
        if (get<0>(right_tup) > 0) { return right_tup; }
        return tuple<int, int, int>{0, 0, 0};

    } 
    if (get<0>(mid_tup) > 0) { return mid_tup; }
    return tuple<int, int, int>{0, 0, 0};
}

// Exercise 4.1-5
// Solve max subarray problem by linear
// Runs in O(n)
tuple<int, int, int> max_subarray_linear(vector<int> arr, int low, int high) {
    int ending_here_high, ending_here_low, l, h;
    int ending_here_sum{-1 * numeric_limits<int>::infinity()}, max_sum{-1 * numeric_limits<int>::infinity()};
    
    for (int i = low + 1; i < high; i++) {
        ending_here_high = i;
        if (ending_here_sum > 0) { 
            ending_here_sum += arr.at(i);
         } else {
            ending_here_low = i;
            ending_here_sum = arr.at(i);
         }
         if (ending_here_sum > max_sum) {
            max_sum = ending_here_sum;
            l = ending_here_low;
            h = ending_here_high;
         }
    }
    return tuple<int, int, int>{max_sum, l, h};
}

// Utility for for driver
void print_arr(vector<int> arr, int low, int high) {
    std::cout << "[";
    for (int i = low; i <= high; i++) {
        std::cout << arr.at(i);
        if (i != high) { std::cout << ", "; }
    }
    std::cout << "]";
}

int main(int argc, char *argv[]) {
    vector<int> vals {13, -3, -25, 20, -3, -16, -23, 18, 20 ,-7, 12, -5, -22, 15, -4, 7};
    //vector<int> vals {-13, -3, -25, 20, -3, -16, -23, 18, 20 ,-7, 12, -5, -22, 15, -4, 7};
    // vector<int> vals {-13, -3, -25, -20, -3, -16, -23, -18, -20 ,-7, -12, -5, -22, -15, -4, -7};
    // vector<int> vals { -1,  -1};
    // vector<int> vals {-5, -3,  -3}; 
    tuple<int, int, int> result = max_subarray_brute(vals, 0, vals.size() - 1);
    std::cout << "Sum: "     << get<0>(result)
         << " Left Index: "  << get<1>(result)
         << " Right Index: " << get<2>(result) 
         << " Array vals: ";
    print_arr(vals, get<1>(result), get<2>(result));
    std::cout << endl;

    result = max_subarray_divide(vals, 0, vals.size() - 1);
    std::cout << "Sum: "     << get<0>(result)
         << " Left Index: "  << get<1>(result)
         << " Right Index: " << get<2>(result) 
         << " Array vals: ";
    print_arr(vals, get<1>(result), get<2>(result));
    std::cout << endl;

    result = max_subarray_divide_allow_empty_return(vals, 0, vals.size() - 1);
    std::cout << "Sum: "     << get<0>(result)
         << " Left Index: "  << get<1>(result)
         << " Right Index: " << get<2>(result);
    //   << " Array vals: ";
    //print_arr(vals, get<1>(result), get<2>(result));     TODO: rework print fn 
    std::cout << endl;

    result = max_subarray_linear(vals, 0, vals.size() - 1);
    std::cout << "Sum: "     << get<0>(result)
            << " Left Index: "  << get<1>(result)
            << " Right Index: " << get<2>(result) 
            << " Array vals: ";
    print_arr(vals, get<1>(result), get<2>(result));
    std::cout << endl;
    return 0;
}