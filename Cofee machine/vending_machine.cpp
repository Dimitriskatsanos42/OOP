#include "vending_machine.hpp"
#include <math.h>

const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);
    strftime(buf, sizeof(buf), "%Y-%m-%d   %X", &tstruct);

    return buf;
}

float _round(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

map <string, string> Vending_Machine::products_in_greek{
    {"coffee","Καφές"},
    {"chocolate","σοκολάτα"},
    {"milk","γάλα"}
};

Vending_Machine::Vending_Machine() :total_check(0.0), temporary_amount(0.0)
{
    this->products = {
        {"coffee",1.5},
        {"chocolate",2.1},
        {"milk",0.3}
    };
    this->quantity = {
        {"coffee",10},
        {"chocolate",10},
        {"milk",20}
    };

    this->coin_buffer = {
        {0.1,0},
        {0.2,0},
        {0.5,0},
        {1.0,0},
        {2.0,0},
        {5.0,0},
        {10.0,0}
    };
}

Vending_Machine::~Vending_Machine() {}


void Vending_Machine::payout(string product, bool has_milk)
{
    cout << endl;
    this->temporary_amount = 0;
    if (this->quantity[product] == 0)
    {
        cout << "Η ποσότητα του προιόντος:" << Vending_Machine::products_in_greek[product] << " δεν επαρκεί για την παρασκευή του" << endl;
        system("pause");
        return;
    }
    if (has_milk)
    {
        if (this->quantity["milk"] == 0)
        {
            cout << "Η ποσότητα του προιόντος:" << Vending_Machine::products_in_greek["milk"] << " δεν επαρκεί για την παρασκευή του" << endl;
            system("pause");
            return;
        }
    }
    this->total_check = this->products[product];
    if (has_milk)
    {
        this->total_check += this->products["milk"];
    }
    bool cancel;
    while (this->temporary_amount < this->total_check)
    {
        cancel = this->coin_insert();
        if (cancel)
        {
            // apopliromi tous prointos h apotelesma tou prointos 
            stringstream ss;
            ss << "Ημερομηνία:" << currentDateTime() << endl;
            ss << "Προιόν:" << Vending_Machine::products_in_greek[product] << endl;
            ss << "Ποσό προιόντος:" << this->total_check << endl;
            ss << "Ποσό πληρωμής Χρήστη:" << this->temporary_amount << endl;
            ss << "Ρέστα:" << this->temporary_amount - this->total_check << "ευρώ" << endl;
            ss << "Καταάσταση Παραγγελίας:Ακυρώθηκε" << endl;
            this->vending_machine_memory.push_back(ss.str());
            return;
        }
    }
    this->reduce_quantity(product);
    if (has_milk)
    {
        this->reduce_quantity("milk");
    }
    cout << endl << "=== ΑΠΟΔΕΙΞΗ ===" << endl;
    cout << "Ημερομηνία:" << currentDateTime() << endl;
    cout << "Προιόν:" << Vending_Machine::products_in_greek[product] << (has_milk ? " με γάλα" : "") << endl;
    cout << "Συνολικό ποσό πληρωμής:" << this->total_check << " ευρώ" << endl;
    cout << "Ποσό πληρωμής:" << this->temporary_amount << " ευρώ" << endl;
    cout << "Ρέστα:" << this->temporary_amount - this->total_check << " ευρώ" << endl;
    this->change();
    system("pause");

    //string message = "Ημερομηνια:"+currentDateTime()+"\n"+"Προιόν:"+Vending_Machine::products_in_greek[products]+"\n"+"Ποσό προιόντος:"+this->total_check; 
    stringstream ss;
    ss << "Ημερομηνία:" << currentDateTime() << endl;
    ss << "Προιόν:" << Vending_Machine::products_in_greek[product] << endl;
    ss << "Ποσό προιόντος:" << this->total_check << endl;
    ss << "Ποσό πληρωμής Χρήστη:" << this->temporary_amount << endl;
    ss << "Ρέστα:" << this->temporary_amount - this->total_check << "ευρώ" << endl;;
    this->vending_machine_memory.push_back(ss.str());
}


bool Vending_Machine::coin_insert()
{
    map <int, double> coin_selected;
    int count = 0;
    unsigned int coin_selection;
    cout << endl << "=== Εισαγωγή νομίσματος ===" << endl;
    for (auto& coin : this->coin_buffer)
    {
        cout << " " << count << ". " << coin.first << endl;
        coin_selected[count] = coin.first;
        count++;
    }
    cout << "-1. Ακύρωση παραγγελίας" << endl;
    cout << "Επιλέξτε νόμισμα:";
    cin >> coin_selection;
    while (coin_selection != -1 && (coin_selection<0 || coin_selection>this->coin_buffer.size() - 1))
    {
        cout << coin_selection << endl;
        cout << endl << "Η επιλογή δεν ήταν έγκυρη παρακαλώ επιλέξτε μία από τις διαθέσιμες επιλογές[-1-" << this->coin_buffer.size() - 1 << "]:";
        cin >> coin_selection;
    }
    if (coin_selection == -1)
    {
        cout << endl << currentDateTime() << "-Ακύρωση παραγγελίας" << endl;
        cout << "Νομίσματα" << endl;
        cout << "----" << endl;
        for (auto& coin : this->coin_buffer)
        {
            cout.precision(3);
            if (coin.second > 0)
                cout << "Νόμισμα:" << coin.first << " ευρώ\tΠοσότητα:" << coin.second << endl;
        }
        cout << "Επιστροφή στον Χρήστη:" << this->temporary_amount << endl;
        system("pause");
        return true;
    }
    this->coin_buffer[coin_selected[coin_selection]]++;
    this->temporary_amount += coin_selected[coin_selection];
    cout << "\n==>Περιγραφή εισαγωγής" << endl;
    cout << " Πραγματοποιήθηκε εισαγωγή νομίσματος::Νόμισμα:" << coin_selected[coin_selection] << " ευρώ" << endl;
    cout << " Υπόλοιπο για συμπλήρωση πληρωμής:" << (this->total_check - this->temporary_amount > 0 ? this->total_check - this->temporary_amount : 0) << endl;
    system("pause");
    return false;
}

void Vending_Machine::reduce_quantity(const string product)
{
    this->quantity[product]--;

}

void Vending_Machine::refill()
{
    for (auto& product : this->quantity)
    {
        std::cout << "Προιόν:" << Vending_Machine::products_in_greek[product.first] << "\tΠοσότητα:" << product.second << std::endl;
    }
    std::cout << endl;
    this->quantity["coffee"] = 10;
    this->quantity["chocolate"] = 10;
    this->quantity["milk"] = 20;
    for (auto& product : this->quantity)
    {
        std::cout << "Προιόν:" << Vending_Machine::products_in_greek[product.first] << "\tΠοσότητα:" << product.second << std::endl;
    }
    stringstream ss;
    ss << "Ημερομηνία:" << currentDateTime() << endl;
    ss << "Κατάσταση:Ανατροφοδότηση αυτόματου πωλήτη" << endl;
    this->vending_machine_memory.push_back(ss.str());
    std::cout << endl;
}
ostream& operator<<(ostream& os, const Vending_Machine& vm)
{
    for (auto& record : vm.vending_machine_memory)
    {
        os << record << endl;
    }
    return os;
}
void Vending_Machine::change()
{
    float nchange = this->temporary_amount - this->total_check;
    cout << "Ρέστα:" << nchange << endl;

    float lefta;
    int i, cur;

    lefta = nchange;

    if (lefta >= 10) {
        cur = div(lefta, 10).quot;
        lefta -= cur * 10;
        cout << "Επιστρέφονται 10:" << cur << endl;
    }

    if (lefta >= 5) {
        cur = div(lefta, 5).quot;
        lefta -= cur * 5;
        cout << "Επίστρέφονται 5:" << cur << endl;
    }

    if (lefta >= 2) {
        cur = div(lefta, 2).quot;
        lefta -= cur * 2;;
        cout << "Επιστρέφονται 2:" << cur << endl;
    }

    if (lefta >= 1) {
        cur = div(lefta, 1).quot;
        lefta -= cur;
        cout << "Επιστρέφονται 1:" << cur << endl;
    }

    if (_round(lefta) >= 0.5) {
        cur = _round(lefta) / 0.5;
        lefta -= cur * 0.5;
        cout << "Επιστρέφονται 0.5:" << cur << endl;  }

    if (_round(lefta) >= 0.2) {
        cur = _round(lefta) / 0.2;
        lefta -= cur * 0.2;
        cout << "Επιστρέφονται 0.2:" << cur << endl;
    }

    if (_round(lefta) >= 0.1) {
        cur = _round(lefta / 0.1);
        lefta -= cur * 0.1;
        cout << "Επιστρέφονται 0.1:" << cur << endl;
    }

   
}
