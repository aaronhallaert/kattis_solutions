#include <iostream>
using namespace std;

int main() {
    // input
    string name;
    cout << "Enter input line:" << endl;
    cin >> name;

    // parse name
    string initials;
    for (int i = 0; i< name.length(); i++){
        if(isupper(name[i])){
            initials += name[i];
        }
    }

    // output
    cout << initials << endl;


    return 0;
}
