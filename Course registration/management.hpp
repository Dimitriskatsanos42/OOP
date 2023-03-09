#pragma once
#include <iostream>
#include <vector>
#include "course.hpp"
#include "student.hpp"
#include <fstream>
#include <sstream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Management
{
private:
	vector <Course> courses;
	vector <Student> students;
public:
	Management();
	~Management();
	void insert_student();
	void enroll_to_lesson();
	void display_students();
	//int select_student();

	//getters
	vector <Course> get_courses();
	vector <Student> get_students();
};