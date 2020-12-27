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
        fileName = "Machine_" + to_string(machineID) + "(1).txt";
    }

    int getFileLineNumber()const
    {
        return fileLineNumber;
    }

    string getFilePath()const
    {
        return path;
    }

    string getFileName()const 
    {
        return fileName;
    }

    /*
        This function increases file line Number when new value is inserted
    */
    void increaseFileLineNumber(int val)
    {
        this->fileLineNumber += val;
    }

    /*
        This function is used to insert a value of data in file
    */
    void insert(string value) 
    {
        ofstream out;
        out.open(path + fileName, ios::app);
        out << value << endl;
        out.close();

        cout << "|  >. Data inserted sucessfully!\n";
    }

    /*
        This function is used to search the value using line Number of that value in file
    */
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
    
    /*
        This function is used to remove the value by taking lineNumber of that value
    */
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

    /*
    *   This function makes a new file of specific machine provided that
    *   number of lines of that specific machine exceeds 100.
    */
    void makeNewFile(int machineID)
    {
        static int fileCounter = 2;
        this->fileLineNumber = 0;
        this->fileName = "Machine_" + to_string(machineID) + "(" + to_string(fileCounter++) + ").txt";
    }
};
