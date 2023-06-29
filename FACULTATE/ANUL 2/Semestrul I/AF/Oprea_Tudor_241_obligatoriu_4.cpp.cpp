#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector < int > v[100001];
vector < int > w[100001];

stack < int > stiva;
int n, pozitii[100001], viz[100001], sub[100001], ind, nrm, i;

void dfs(int x){
	pozitii[x] = ind++; //atribuim pozitia nodului ca indice+1
	stiva.push(x);  //punem nodul pe stiva
	viz[x] =1;      //il marcam ca vizitat
	sub[x] = ind;   //si retinem indicele la care l am vizitat (momentul)
	int nr = v[x].size(),y;
	for(i=0;i<nr;i++){
		y=v[x][i];      // pornim prin lista de adiacenta a nodului
		if(!pozitii[y] || viz[y]!=0){
			if(!pozitii[y])
				dfs(y); // daca nodului din lista nu i s a atribuit deja o pozitie,
                                // continuam parcurgerea prin el
            if(sub[x]>sub[y])
                sub[x] = sub[y]; //daca momentul de vizitare al lui x e mai mare decat al lui y
                                // il pastram la x pe al lui y
		}
	}

    if(sub[x] == pozitii[x]){   //daca am ajuns de unde am plecat, am format o componenta tare conexa
		nrm+=1; //crestem numarul de componente cu 1
		while(x!=y){
			y=stiva.top();  //scoatem tot, pe rand din stiva
			stiva.pop();
			w[nrm].push_back(y); // ce era in capatul stivei punem in componenta

            viz[y] = 0;     // marcam capatul stivei ca vizitat
		}
	}
}

int main(){

	int m, x, y, nr, j;
	cin>>n>>m;
	for(int i=0;i<m;++i){
		cin>>x>>y;
		v[x].push_back(y);
	}


    for(i=1 ; i<=n ; ++i)
        if(pozitii[i] == 0)
            dfs(i); //parcurgem  nodurile

    cout<<endl<<nrm<<endl;//afisam nr de componente
    for(i=1;i<=nrm;i++){
        nr = w[i].size();
        for(j=0;j<nr;j++)
            cout<<w[i][j]<<" "; //afisam fiecare muchie din componenta
        cout<<endl;
    }
	return 0;
}