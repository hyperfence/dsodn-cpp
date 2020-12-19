#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class MachineFile {
    string path, fileName;
    int lineNumber;
public:
    MachineFile() {
        lineNumber = 0;
        path = "";
        fileName = "";
    }

    void setFileName(int machineID) {
        fileName = "Machine_" + to_string(machineID) + ".txt";
    }

    void insert(string value) {
        ofstream out;
        out.open(path + fileName, ios::app);
        out << value << endl;
        out.close();
    }

};
