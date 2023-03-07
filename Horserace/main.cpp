#include "racing.hpp"
#include <cstdlib>

int main(int argc,char **argv)
{
   int number_of_horses=4;
   int number_of_rounds=10;
   if(argc==3)
   {
      number_of_horses=atoi(argv[1]);
      number_of_rounds=atoi(argv[2]);
   }
   Racing rc(number_of_horses,number_of_rounds);
   rc.display_horses();cout<<endl;
   rc.race();
   rc.display_standings();
   return EXIT_SUCCESS;
}