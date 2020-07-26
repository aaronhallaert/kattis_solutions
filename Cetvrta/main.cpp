#include <iostream>
#include <unordered_set>
using namespace std;
unordered_set<int> checkCoordSet(unordered_set<int> coords, int candidate);
int main() {
    unordered_set<int> xcoords;
    unordered_set<int> ycoords;

    // first coordinate
    int coord1x;
    int coord1y;
    cin >> coord1x >> coord1y;

    xcoords.insert(coord1x);
    ycoords.insert(coord1y);

    // second coordinate
    int coord2x;
    int coord2y;
    cin >> coord2x >> coord2y;
    xcoords = checkCoordSet(xcoords, coord2x);
    ycoords = checkCoordSet(ycoords, coord2y);

    // third coordinate
    int coord3x;
    int coord3y;
    cin >> coord3x >> coord3y;
    xcoords = checkCoordSet(xcoords, coord3x);
    ycoords = checkCoordSet(ycoords, coord3y);

    // find fourth coordinate of rectangle
    int coord4x = *begin(xcoords);
    int coord4y = *begin(ycoords);

    // Output
    cout << coord4x << " " << coord4y;
    return 0;
}

unordered_set<int> checkCoordSet(unordered_set<int> coords, int candidate){
    if(coords.find(candidate) != coords.end()){
        // element found
        coords.erase(candidate);
    }
    else{
        // element not found
        coords.insert(candidate);
    }
    return coords;
}

