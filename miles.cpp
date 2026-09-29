#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


vector<char> nextLineAsVector(ifstream& infile){
    string line = "";
    getline (infile, line);
    cout << "DEBUG:\t" << line << endl;
    const char* cline = line.c_str();

    vector<char> vect = { };
    for (int i = 0; i < line.length(); i++){
        vect.push_back(cline[i]);
    }

    return vect;
}

int main()
{
    ifstream infile("input.txt");


    cout << "h" << endl;

    vector<char> vect = nextLineAsVector(infile);
    for (int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
    }

    infile.close();

    return 0;
}