//
// Created by William on 3/9/2018.
//
#include "Student.h"
#include "Course.h"
#include <string>
#include <Vector>
using namespace std;

namespace BrooklynPoly {
    Course::Course(const string& courseName) : name(courseName){}
    int Course::getSize()const{
        return students.size();
    }
    const string& Course::getName()const{
        return name;
    }
    Student Course::getStudent(int index)const{
        return *students[index];
    }
    void Course::deleteStudentptr(int index){
        students[index], students[students.size()] = students[students.size()], students[index];
        students.pop_back();
    }
    const string& Course::getStudentName(int index)const{
        return students[index] -> getName();
    }
    void Course::addStudent(Student& student){
        Student* sptr = &student;
        students.push_back(sptr);
    }
}
