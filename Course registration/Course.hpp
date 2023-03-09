#pragma once
#include <iostream>

using namespace std;

class Course
{
private:
    // kωδικός, τίτλος, εξάμηνο διδασκαλίας και διδακτικές μονάδες
    string code;
    string title;
    int semester;
    int credits;
public:
    Course(string c, int s, string t, int cr);
    int get_credits();
    int get_semester();
    string get_code()const;
    string get_title()const;
    bool operator==(const Course& c)const;
    friend ostream& operator<<(ostream& os, const Course& c);
};