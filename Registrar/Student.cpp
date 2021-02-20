//
// Created by William on 3/9/2018.
//
#include "Student.h"
#include "Course.h"
#include <string>
#include <vector>
using namespace std;
namespace BrooklynPoly {
    Student::Student(const string& studentName) : name(studentName){}

    bool Student::addCourse(Course& course){
        for(size_t i = 0; i < courses.size(); i++){
            if(courses[i] -> getName() == course.getName()){
                return false;
            }
        }
        Course* cptr = &course;
        courses.push_back(cptr);
        return true;
    }

    const string& Student::getName()const{
        return name;
    }

    Course& Student::getCourse(int index){
        return *courses[index];
    }
    int Student::getCoursesSize()const{
        return courses.size();
    }
}
