//
// Created by William on 3/9/2018.
//
#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


namespace BrooklynPoly {
    void Registrar::addCourse(const string& courseName){
        if(existingCourse(courseName) == -1){
            Course* cptr = new Course(courseName);
            courses.push_back(cptr);
        }
    }
    void Registrar::addStudent(const string& studentName){
        if(existingStudent(studentName) == -1){
            Student* sptr = new Student(studentName);
            students.push_back(sptr);
        }
    }
    bool Registrar::enrollStudentInCourse(const string& student, const string& course){
        int studentIndex = existingStudent(student);
        int courseIndex = existingCourse(course);
        if(studentIndex == -1 || courseIndex == -1){
            return false;
        }
        for(size_t i = 0; i < courses[courseIndex]->getSize(); i++){ //Check is student already in that course
            if(courses[courseIndex]-> getStudentName(i) == student){
                return false;
            }
        }
        for(size_t i = 0; i < students[studentIndex]->getCoursesSize(); i++){
            if(students[studentIndex]->getCourse(i).getName() == course){
                return false;
            }
        }
        courses[courseIndex]->addStudent(*students[studentIndex]);
        students[studentIndex]->addCourse(*courses[courseIndex]);
        return true;
    }

    void Registrar::purge(){
        for(size_t i = 0; i < courses.size(); i++){
            delete courses[i];
        }
        courses.clear();
        for(size_t i = 0; i < students.size(); i++){
            delete students[i];
        }
        students.clear();
    }

    bool Registrar::cancelCourse(const string& courseName){
        int index = existingCourse(courseName);
        if(index == -1){
            return false;
        }
        else{
            for(size_t i = 0; i < courses[index]->getSize(); i++){
                courses[index] -> deleteStudentptr(i);
            }
            delete courses[index];
            courses[index], courses[courses.size()] = courses[courses.size()], courses[index];
            courses.pop_back();
            cout << "Course Size: " << courses.size() << endl;
            return true;
        }
    }


    int Registrar::existingCourse(const string& courseName){
        for(size_t i = 0; i < courses.size(); i++){
            if(courses[i] -> getName() == courseName){
                return i;
            }
        }
        return -1;
    }
    int Registrar::existingStudent(const string& studentName){
        for(size_t i = 0; i < students.size(); i++){
            if(students[i]->getName() == studentName){
                return i;
            }
        }
        return -1;
    }
    ostream& operator<<(ostream& os, const Registrar& r){
        for(size_t i = 0; i < r.courses.size(); i++){
            os << "Course: " << r.courses[i] -> getName() << endl;
            os << "     " << "Students: " << endl;
            for(size_t j = 0; j < r.courses[i] -> getSize(); j++){
                os << "     " << r.courses[i] -> getStudentName(j) << endl;
            }
            os << endl;
        }
        return os;
    }

}
