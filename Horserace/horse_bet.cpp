#include <iostream>
#include "racing.hpp"

using namespace std;

int select_horse(vector <horse> &horses)
{
    int x;
    cout<< "==== horse selection ===="<<endl;
    for(int i =0; i=horses.size(); i++)
     {
         cout<< i+1 << " "<<horses[i] <<endl; 
     }
     cout << "select: ";
     cin >> x;

     while(x <=0 || x>horses.size()) 
      {
          cout<< "try again" <<endl;
          cin>>x;
          cout<<endl;
      }
}

int main(int argc, char **argv)
{
    int number_of_horses=8;
    int number_of_rounds=10;
    if(argc==3)
     {
         number_of_horses=atoi(argv[1]);
         number_of_rounds=atoi(argv[2]);
     }
    Racing rc(number_of_horses,number_of_rounds);
    double money_amount;
    double betting_money;
    vector <horse> horses;
    
    int choice;

    do {
        cout << "Give users money amount:";
        cin >> money_amount;
        cout << endl;
    } while (money_amount<0  || money_amount >10000000);
     
     
    while(true)
    {
       cout<< "=== Money amount ==== " <<endl;
       if(choice==1)
         {
             rc.display_horses();
         }
         else if(choice==2)
         {
             cout << "==== Money betting ==" <<endl;
             cout << "select your bet amount:";
             cin >>betting_money;
             cout<<endl;

             while(betting_money<=0 || betting_money>money_amount) 
             {
                cout<<"-->Please provide a valid betting amount";
                cin>>betting_money;      
             }

             int position;

             if(position ==1)
              {
                  money_amount +=betting_money *2;
              }
              else if(position >3)
              {
                  money_amount -= betting_money;
              }
              cout<< "===== Bettig result ===="<<endl;
              cout<< position << endl;
         }
         else{
             cout<< "exit race your amount:"<<money_amount<<endl;
             exit(EXIT_SUCCESS);
         }
         
    }

     
} 