#include <iostream>

using namespace std;

class horse
{
    private:
        int id;
        string name;
        int startup_speed;
        int power;
        int stamina;
    
    public:
        horse(int h_id,string h_name,int h_startup_speed,int h_power,int h_stamina);
        ~horse();
        bool move_forward(int step,double r);
        string get_name();
        bool operator==(const horse &h)const;
        friend ostream &operator<<(ostream &os,const horse &h);
};