#include <iostream>
using namespace std;
int main()
 { int v[101], nr_elemente, limita_inferioara, limita_superioara, mijloc, gasit, variabila_cautata;

cin>>variabila_cautata;
cin>>nr_elemente;

for(int i=1;i<=nr_elemente;i++)
 cin>>v[i];


limita_inferioara=1;
limita_superioara=nr_elemente;
gasit=0;

while((limita_inferioara<=limita_superioara)&&(gasit==0))
{
mijloc=(limita_inferioara+limita_superioara)/2;
if(variabila_cautata==v[mijloc])
    {
    cout<<"Numarul se afla pe pozitia "<<mijloc<<".";
    gasit=1;
    }
else if(variabila_cautata>v[mijloc]) 
    limita_inferioara=mijloc+1; 
else limita_superioara=mijloc-1;

}

if(gasit==0)

cout<<"Numarul cautat nu se afla in vector.";

return 0;
}