//
// Created by William on 3/9/2018.
//

#ifndef REGISTRAR_H
#define REGISTRAR_H
#include <string>
#include <vector>
#include <iostream>
#include "Course.h"
#include "Student.h"

namespace BrooklynPoly {

    class Course;
    class Student;

    class Registrar{
        friend std::ostream& operator<<(std::ostream& os, const Registrar& r);
    public:
        Registrar(){}
        void addCourse(const std::string& courseName);
        void addStudent(const std::string& studentName);
        bool enrollStudentInCourse(const std::string& student,  const std::string& course);
        void purge();
        bool cancelCourse(const std::string& courseName);
        int existingCourse(const std::string& courseName);
        int existingStudent(const std::string& studentName);
    private:
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}



#endif //UNTITLED1_REGISTRAR_H
