//
// Created by William on 3/9/2018.
//

#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Course;
    class Student {
    public:
        Student(const std::string& studentName);
        const std::string& getName()const;
        bool addCourse(Course& course);
        int getCoursesSize()const;
        Course& getCourse(int index);
    private:
        std::string name;
        std::vector<Course*> courses;
    };
}



#endif //STUDENT_H
