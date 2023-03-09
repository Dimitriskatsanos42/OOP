#pragma once
#include <iostream>
#include <vector>
#include "course.hpp"
using namespace std;

class Student
{
private:
    // αριθμός μητρώου,ονοματεπώνυμο,εξάμηνο,διδακτικές μονάδες
    string id;
    string fullname;
    int semester;
    int credits;
    int credits_left;
    vector <Course> courses;
public:
    Student(string sid, string sfullname, int ssemester, int scredits);
    void add_course(Course& c);
    string get_id();
    string get_name();
    int get_semester();
    int get_credits();
    int get_credits_left();
    vector <Course> get_courses();
    bool is_course_valid(const Course &c);
    friend ostream& operator<<(ostream& os, const Student& s);
};