//
// Created by William on 3/9/2018.
//

#ifndef COURSE_H
#define COURSE_H

#include "Student.h"
#include <string>
#include <vector>


namespace BrooklynPoly {

    class Student;
    class Course{
    public:
        Course(const std::string& courseName);
        int getSize()const;
        const std::string& getName()const;
        Student getStudent(int index)const;
        void deleteStudentptr(int index);
        const std::string& getStudentName(int index)const;
        void addStudent(Student& student);
    private:
        std::vector<Student*> students;
        std::string name;
    };

}




#endif //UNTITLED1_COURSE_H
