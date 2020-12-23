#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class MachineFile {
private:
    string path, fileName;
    int fileLineNumber;

public:

    MachineFile() {
        fileLineNumber = 0;
        path = "Machine_Files/";
        fileName = "";
    }

    void setFileName(int machineID) 
    {
        fileName = "Machine_" + to_string(machineID) + ".txt";
    }

    int getFileLineNumber()const
    {
        return fileLineNumber;
    }
    string getFileName() const {
        return fileName;
    }
    void increaseFileLineNumber(int val)
    {
        this->fileLineNumber += val;
    }

    void insert(string value) 
    {
        ofstream out;
        out.open(path + fileName, ios::app);
        out << value << endl;
        out.close();
    }

    string search(int lineNumber) 
    {
        ifstream in;
        in.open(path + fileName);
        string value = "";
        int checklineNumber = 0;
        while (getline(in, value)) {
            checklineNumber++;
            if (checklineNumber == lineNumber)
                return value;
        }
        in.close();
        return value;
    }
    
    T remove(int lineNumber) 
    {
        ifstream in;
        in.open(path + fileName);
        ofstream out;
        out.open(path + "temp.txt");

        T removedData = "";
        string value;
        int checklineNumber = 0;
        while (getline(in, value))
        {
            checklineNumber++;
            if (checklineNumber == lineNumber) {
                removedData = value;
                value = "";
            }
            out << value << endl;
        }
        in.close();
        out.close();
        in.open(path + "temp.txt");
        out.open(path + fileName);
        value = "";
        while (getline(in, value))
        {
            out << value << endl;
        }
        in.close();
        out.close();
        return removedData;
    }
};
