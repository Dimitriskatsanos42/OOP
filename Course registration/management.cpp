#include "management.hpp"
#include <algorithm>


Management::Management()
{
	string filename = "dit_uoi_course.txt";
	fstream fs;
	fs.open(filename, ios::in);
	if (!fs.is_open())
	{
		cerr << "File " << filename << " does not exist" << endl;
		return;
	}
	string line,word;
	bool first_line = true;
	vector <string> data;
	while (getline(fs, line))
	{
		if (first_line)
		{
			first_line = false;
			continue;
		}
		data.clear();
		stringstream ss(line);
		while (getline(ss, word, ','))
		{
			data.push_back(word);
		}
		this->courses.push_back(Course(data[0],stoi(data[1]),data[2],stoi(data[3])));
	}
	fs.close();
}

Management::~Management() {}

void Management::insert_student()
{
	system("cls");
	string id,name;
	int semester, credits;
	cout << "Δώσε AM φοιτητή:";
	cin >> id;
	bool student_exists;
	while (1)
	{
		student_exists = false;
		for (auto student : this->students)
		{
			if (student.get_id() == id)
			{
				student_exists = true;
				break;
			}
		}
		if (!student_exists)
		{
			break;
		}
		cout << "Το ΑΜ:" << id << " υπάρχει ήδη στο σύστημα!Εισάγεται ένα έγκυρο ΑΜ:";
		cin >> id;
	}
	// find()
	/*
	while (find_if(this->students.begin(), this->students.end(), [&](Student& s) {
		return s.get_id() == id;
		}) != this->students.end())
	{
		cout << "Δώσε έγκυρο ΑΜ:";
		cin >> id;
	}
	*/
	
	cin.ignore();
	cout << "Δώσε όνομα φοιτητή:";
	getline(cin, name);
	cout << "Δώσε Εξάμηνο φοιτητή:";
	cin >> semester;
	cout << "Δώσε Δ. Μονάδες φοιτητή:";
	cin >> credits;
	this->students.push_back(Student(id, name, semester, credits));
	this->display_students();
	system("pause");
	
}

void Management::enroll_to_lesson()
{
	int student_selected;
	for (int i = 0, t = this->students.size(); i < t; i++)
	{
		cout << i << "." << this->students.at(i) << endl;
	}
	cout << "Επελεξε φοιτητή:";
	cin >> student_selected;
	// Έλεγχος εγκυρότητας επιλεγμένης θέσης σε πίνακα students.
	while (student_selected<0 || student_selected>=this->students.size())
	{
		cout << "Μη έγκυρη επιλογή!Επέλεξε αριθμό από [0-" << this->students.size() - 1 << "]:";
		cin >> student_selected;
	}
	//Φοιτητής που δουλεύω-->this->students[student_selected];
	//Επιλογή από μενού 4-->ΦΟΙΤΗΤΗΣ 3-->ΜΑΘΗΜΑ 1,ΜΑΘΗΜΑ 2,ΜΑΘΗΜΑ 3
	//Επιλη 1-->Εισαγωγή φοιτητή
	//Επιλογή 4-->ΦΟΙΤΗΤΗΣ 3
	vector <Course> student_available_courses;
	for (auto& course : this->courses)
	{

		if (this->students[student_selected].get_semester() % 2 == course.get_semester() % 2 
			&& this->students[student_selected].get_semester()>=course.get_semester() 
			&& this->students[student_selected].get_credits_left()>=course.get_credits() 
			&& this->students[student_selected].is_course_valid(course))
		{
			student_available_courses.push_back(course);
		}
	}
	
	int course_choice;
	for (int i = 0; i < student_available_courses.size(); i++)
	{
		cout << i << "." << student_available_courses[i] << endl;
	}
	cout << "Διάλεξε μάθημα:";
	cin >> course_choice;
	while (course_choice < 0 || course_choice >= student_available_courses.size())
	{
		cout << "Μη έγκυρη επιλογή[0-" << student_available_courses.size() - 1 << "]:";
		cin >> course_choice;
	}

	this->students[student_selected].add_course(student_available_courses[course_choice]);
}


void Management::display_students()
{
	std::cout << "=== ΦΟΙΤΗΤΕΣ ===" << std::endl;
	for (auto& student : this->students)
	{
		std::cout << student << std::endl;
	}
}

/*
int Management::select_student()
{

}
*/


// getters-->Σημαντικοί για κατασκευή παραθύρου
vector <Course> Management::get_courses()
{
	return this->courses;
}

vector <Student> Management::get_students()
{
	return this->students;
}
