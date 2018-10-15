//
// Created by Eddie Lee on 2018/10/15.
//

#ifndef ALGORITHM_STUDENT_H
#define ALGORITHM_STUDENT_H

#include <iostream>

using namespace std;

struct Student{

    string name;

    int score;

    bool operator < (const Student &otherStudent){
        return score < otherStudent.score;
    }

    friend ostream& operator << (ostream &os, const Student &student){
        os << "Student:" << student.name << " " << student.score << endl;
        return os;
    }
};

#endif
