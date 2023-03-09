#include "student.hpp"

Student::Student(string sid, string sfullname, int ssemester, int scredits) :id(sid), fullname(sfullname), semester(ssemester), credits(scredits),credits_left(scredits) {}


void Student::add_course(Course& c)
{
    this->credits_left -= c.get_credits();
    this->courses.push_back(c);
}

string Student::get_id()
{
    return this->id;
}

string Student::get_name()
{
    return this->fullname;
}

int Student::get_semester()
{
    return this->semester;
}

int Student::get_credits()
{
    return this->credits;
}

int Student::get_credits_left()
{
    return this->credits_left;
}

bool Student::is_course_valid(const Course& c)
{
    for (auto& course : this->courses)
    {
        if (c.get_code() == course.get_code())
        {
            return false;
        }
    }
    return true;
}

vector <Course> Student::get_courses()
{
    return this->courses;
}

ostream& operator<<(ostream& os, const Student& s)
{
    return os << s.id << " " << s.fullname << " " << s.semester << " " << s.credits;
}