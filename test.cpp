#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);

    move(v2.begin(), v2.end(), back_inserter(v1));

    for (const auto& elem : v1) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
