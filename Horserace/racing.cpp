#include "racing.hpp"
#define DNF -1000

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

void press_enter()
{
    cout<<"Press [Enter] to continue....";
    cin.get();
}



Racing::Racing(int number_of_horses,int number_of_rounds):n_horses(number_of_horses),rounds(number_of_rounds)
{
    auto random_value=uniform_int_distribution<int>(50,100);
    vector <string> names{"Blitz","Bolt","Goliath","Hercules","Rogue","Danger","Raider","Storm","Nitro","Hulk"};
    shuffle(names.begin(),names.end(),default_random_engine(chrono::steady_clock::now().time_since_epoch().count()));
    for(int i=0;i<this->n_horses;i++)
    {
        horse a_horse(i+1,names[i],random_value(mt),random_value(mt),random_value(mt));
        horses.push_back(a_horse);
        position.push_back(0);
        standings.push_back(make_pair(a_horse,DNF));
    }

}

Racing::~Racing() {}

void Racing::race()
{
    mt19937 gen(steady_clock::now().time_since_epoch().count());
    const int steps_will_be_made=rounds * 2;
    auto rand_real=uniform_real_distribution<double>(0,100);
    bool can_be_moved;
    drawing();
    press_enter();
    int rank=1;
    for(int i=0;i<steps_will_be_made;i++)
    {
        for(int j=0;j<horses.size();j++)
        {
            if(position[j]==rounds-1)
            {
                if(standings[j].second==DNF)
                {
                    standings[j].second=rank;
                    rank++;
                }
                continue;
            }
            can_be_moved=horses[j].move_forward(position[j],rand_real(gen));
            if(can_be_moved)
            {
                position[j]++;
            }
        }
        drawing();
        press_enter();
    }
}

void Racing::auto_race()
{
    mt19937 gen(steady_clock::now().time_since_epoch().count());
    const int steps_will_be_made=rounds * 2;
    auto rand_real=uniform_real_distribution<double>(0,100);
    bool can_be_moved;
    drawing();
    
    for(int i=0;i<steps_will_be_made;i++)
    {
        for(int j=0;j<horses.size();j++)
        {
            if(position[j]==rounds-1)
            {
                continue;
            }
            can_be_moved=horses[j].move_forward(position[j],rand_real(gen));
            if(can_be_moved)
            {
                position[j]++;
            }
        }
        drawing();
        
    }
}


void Racing::drawing()
{
    for(int i=0;i<horses.size();i++)
    {
        cout<<"";
        for(int j=0;j<rounds;j++)
        {
            if(position[i]==j)
            {
                cout<<i;
            }
            else
                cout<<".";
        }
        cout<<""<<endl;
    }
}

void Racing::display_standings()
{
    cout<<"====== Standings ======="<<endl;
    for(int i=0;i<standings.size();i++)
    {
        cout<<standings[i].first.get_name()<<"->"<<standings[i].second<<endl;
    }
    cout<<endl;
}

void Racing::display_horses()
{
    for(auto &h:horses)
    {
        cout<<h<<endl;
    }
}

vector <horse> Racing::get_horses()const
{
    return horses;
}

vector <pair <horse,int>> Racing::get_standings()const
{
    return standings;
}