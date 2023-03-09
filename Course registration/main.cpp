#include <wx/wx.h>
#include <wx/listctrl.h>
#include "management.hpp"
#define MAX_INPUT_LENGTH 255
#pragma execution_character_set("utf-8")

namespace app
{
    vector <Student> students;
    vector <Course> courses;
    void set_students(Management& msystem)
    {
        students = msystem.get_students();
    }
    void set_courses(Management& msystem)
    {
        courses=msystem.get_courses();
    }
};

class Frame :public wxFrame {
private:
    wxListCtrl* studentsctrl;
    wxListCtrl* lessonsctrl;
    wxBoxSizer* sizer;
    vector <Student> students;
    vector <Course> courses;
    void create_students_list(wxWindow *parent)
    {
        auto size = this->GetSize();
        this->studentsctrl = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth() * 0.45, size.GetHeight() * 0.45),wxLC_REPORT);
        this->studentsctrl->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        this->studentsctrl->SetBackgroundColour(wxColor("#a88fb3"));
        this->studentsctrl->InsertColumn(0, wxT("ΑΜ"),wxLIST_FORMAT_CENTER,size.GetWidth()*0.45/4);
        this->studentsctrl->InsertColumn(1, wxT("ΟΝΟΜΑ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->studentsctrl->InsertColumn(2, wxT("ΕΞΑΜΗΝΟ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->studentsctrl->InsertColumn(3, wxT("Δ. ΜΟΝΑΔΕΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        for (int i = 0, t = this->students.size(); i < t; i++)
        {
            // Προσθήκη νέου αντικειμένου στην λίστα
            wxListItem it;
            it.SetAlign(wxLIST_FORMAT_CENTER);
            this->studentsctrl->InsertItem(i,it);

            // Προσθήκη φοιτητή στό αντικείμενο
            this->studentsctrl->SetItem(i, 0, wxString(this->students.at(i).get_id()));
            this->studentsctrl->SetItem(i, 1, wxString(this->students.at(i).get_name()));
            this->studentsctrl->SetItem(i, 2, wxString(to_string(this->students.at(i).get_semester())));
            this->studentsctrl->SetItem(i, 3, wxString(to_string(this->students.at(i).get_credits())));
        }
    }

    void create_lessons_list(wxWindow* parent)
    {
        auto size = this->GetSize();
        this->lessonsctrl = new wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth() * 0.45, size.GetHeight() * 0.45),wxLC_REPORT);
        this->lessonsctrl->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        this->lessonsctrl->SetBackgroundColour(wxColor("#a88fb3"));
        this->lessonsctrl->InsertColumn(0, wxT("ΚΩΔΙΚΟΣ"),wxLIST_FORMAT_CENTER,size.GetWidth()*0.45/4);
        this->lessonsctrl->InsertColumn(1, wxT("ΤΙΤΛΟΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->lessonsctrl->InsertColumn(2, wxT("ΕΞΑΜΗΝΟ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
        this->lessonsctrl->InsertColumn(3, wxT("Δ. ΜΟΝΑΔΕΣ"), wxLIST_FORMAT_CENTER, size.GetWidth() * 0.45 / 4);
    
        //Προσθήκη μαθημάτων στην λίστα
        for (int i=0,t=this->courses.size();i<t;i++)
        {
            wxListItem it;
            it.SetAlign(wxLIST_FORMAT_CENTER);
            this->lessonsctrl->InsertItem(i,it);

            this->lessonsctrl->SetItem(i, 0, wxString(wxString::FromUTF8(this->courses.at(i).get_code())));
            this->lessonsctrl->SetItem(i, 1, wxString(wxString::FromUTF8(this->courses.at(i).get_title())));
            this->lessonsctrl->SetItem(i, 2, wxString(wxString::FromUTF8(to_string(this->courses.at(i).get_semester()))));
            this->lessonsctrl->SetItem(i, 3, wxString(wxString::FromUTF8(to_string(this->courses.at(i).get_credits()))));
        }
    }

    void panel1()
    {
        auto size = this->GetSize();
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        wxStaticText* text = new wxStaticText(panel, wxID_ANY, wxT("ΦΟΙΤΗΤΕΣ"), wxDefaultPosition, wxSize(size.GetWidth()*0.22,size.GetHeight()*0.05),wxTEXT_ALIGNMENT_CENTER);
        text->SetFont(wxFont(15,wxFONTFAMILY_ROMAN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD));
        text->SetForegroundColour(wxColor("#701682"));
        this->create_students_list(panel);
        wxButton* button = new wxButton(panel, wxID_ANY, wxT("ΕΜΦΑΝΙΣΗ ΜΑΘΗΜΑΤΩΝ"), wxDefaultPosition, wxSize(150, 30));
        button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::showlessons, this);
        wxBoxSizer* panelsizer = new wxBoxSizer(wxVERTICAL);
        panelsizer->AddSpacer(15);
        panelsizer->Add(text,0,wxALIGN_CENTER);
        panelsizer->AddSpacer(15);
        panelsizer->Add(this->studentsctrl,0,wxALIGN_CENTER);
        panelsizer->AddSpacer(15);
        panelsizer->Add(button, 0, wxALIGN_CENTER);
        panel->SetSizer(panelsizer);
        this->sizer->Add(panel);
    }

    void panel2()
    {
        auto size = this->GetSize();
        wxBoxSizer* bx = new wxBoxSizer(wxVERTICAL);
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        wxStaticText* text = new wxStaticText(panel, wxID_ANY, wxT("ΜΑΘΗΜΑΤΑ"), wxDefaultPosition, wxSize(size.GetWidth() * 0.22, size.GetHeight() * 0.05),wxTEXT_ALIGNMENT_CENTER);
        text->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        text->SetForegroundColour(wxColor("#701682"));
        this->create_lessons_list(panel);
        bx->AddSpacer(15);
        bx->Add(text,0,wxALIGN_CENTER);
        bx->AddSpacer(15);
        bx->Add(this->lessonsctrl,0,wxALIGN_CENTER);
        panel->SetSizer(bx);
        this->sizer->Add(panel);
        
    }

public:
    Frame(vector <Student> &sts,vector <Course> &crs) :wxFrame(nullptr, wxID_ANY, wxT("ΣΥΣΤΗΜΑ ΔΙΑΧΕΙΡΗΣΗΣ ΦΟΙΤΗΤΩΝ"), wxDefaultPosition, wxSize(800, 600))
    {
        this->students = sts;
        this->courses = crs;
        this->SetMinSize(wxSize(800,600));
        this->SetMaxSize(wxSize(800, 600));
        this->SetBackgroundColour(wxColor("#ebe2e1"));
        this->sizer = new wxBoxSizer(wxHORIZONTAL);
        this->sizer->AddSpacer(16);
        this->panel1();
        this->sizer->AddSpacer(16);
        this->panel2();
        this->SetSizer(this->sizer);
    }
    ~Frame() {}

    void showlessons(wxCommandEvent& ev)
    {
        auto it = this->studentsctrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        auto student_id = this->studentsctrl->GetItemText(it);
        int pos = -1;
        for (int i = 0; i < this->students.size(); i++)
        {
            if (this->students.at(i).get_id() == student_id)
            {
                pos = i;
                break;
            }
        }
        
         std::string student_elements = this->students.at(pos).get_id() + " " + this->students.at(pos).get_name()
           + " " + to_string(this->students.at(pos).get_semester()) + " " + to_string(this->students.at(pos).get_credits());
        wxMessageBox(wxString(student_elements),wxT("ΕΜΦΑΝΙΣΗ"), wxICON_INFORMATION);
        //0-->Αρχή της λίστας
        //wxLIST_STATE_SELECTED-->Η κατάσταση του αντικειμένου να είναι επιλεγμένη
    }
};

class App :public wxApp {
public:
    bool OnInit()wxOVERRIDE
    {
        Frame* f = new Frame(app::students, app::courses);
        f->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(App);

void menu()
{
    system("cls");
    SetConsoleOutputCP(65001);
    cout << "1. Εισαγωγή νέου φοιτητή" << endl;
    cout << "2. Ενημέρωση στοιχείων φοιτητή" << endl;
    cout << "3. Διαγραφή φοιτητή" << endl;
    cout << "4. Δήλωση μαθήματος" << endl;
    cout << "5. Εμφάνιση δηλώσεων ανά φοιτητή(GUI)" << endl;
    cout << "0. Έξοδος" << endl;
    cout << "Δώστε επιλογή :";
}

int main(int argc,char **argv)
{   
    SetConsoleOutputCP(65001);
    Management msystem;
    int choice;
    while (true)
    {
        menu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            msystem.insert_student();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            msystem.enroll_to_lesson();
            break;
        case 5:
            app::set_courses(msystem);
            app::set_students(msystem);
            wxEntry(argc, argv);
            break;
        case 0:
            exit(EXIT_SUCCESS);
        default:
            cerr << "Μη διαθέσιμη επιλογή!Παρακαλώ επιλέξτε μία από τις διαθέσιμες επιλογές[0-5]" << endl;
            break;
        }
    }
    return 0;
}


/*
int main()
{
    vector <Course> courses;
    vector <Student> students;

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
        courses.push_back(Course(data[0],stoi(data[1]),data[2],stoi(data[3])));
    }
    fs.close();

    int choice;
    while (true)
    {
        menu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            string id,name;
	        int semester, credits;
	        cout << "Δώσε AM φοιτητή:";
	        cin >> id;
	        cout << "Δώσε Όνομα φοιτητή:";
	        cin.ignore();
	        getline(cin,name);
	        cout << "Δώσε Εξάμηνο φοιτητή:";
	        cin >> semester;
	        cout << "Δώσε Δ. Μονάδες φοιτητή:";
	        cin >> credits;
	        students.push_back(Student(id, name, semester, credits));
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 0:
            exit(EXIT_SUCCESS);
        default:
            cerr << "Μη διαθέσιμη επιλογή!Παρακαλώ επιλέξτε μία από τις διαθέσιμες επιλογές[0-5]" << endl;
            break;
        }
    }
    return 0;
}
*/