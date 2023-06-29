#include <bits/stdc++.h>
#define NMax 10001
#define inf 100000
#define NMax5 50005
#define NMax25 2500
#define NMax1 101
#define inf2 1005

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");


class graf
{
    int nrNoduri, nrMuchii;
    bool orientat;
    vector <int> gr[NMax]; // liste de adiacenta ale grafului


public:
    graf(int n, int m, bool o); // constructor
    void Citire_Orientat();
    void Citire_Neorientat();
    void Citire_Arbore();
    void Afisare_Graf();

    // BFS
    vector<int> BFS(int s, bool viz[NMax]); // s - nodul de start

    // DFS
    void DFS(int s, bool viz[NMax]); // s - nodul de start

    // Determinare nr de componente conexe cu DFS
    int Comp_Conexe(bool viz[NMax]); // returneaza cate componente conexe are graful

    // Kosaraju
    void Graf_Transpus(); // creeaza graful transpus in grT
    void ParcurgereGrafInitial(bool viz[NMax]); // parcurgerea in adancime a grafului initial
    void DFST(int s, bool vizDFST[NMax], vector<int> &aux); // s - nodul de start, dfs pe graful transpus
    vector<vector<int>> CTC(); // apeleasa DFST si afiseaza comp tare conexe

    // Algoritm Havel-Hakimi
    bool Havel_Hakimi(vector<int>grade, int nrNoduri);

    // Sortare topologica
    stack<int> Sortare_Topologica();

    // Afisare Muchii Critice
    void Afisare_Muchii_Critice();
    void DFS_Muchii_Critice(int s, int tata, bool viz[], int nivel[], int niv_min_acc[], int &ct_muchii_critice);

    // Afisare Componente Biconexe
    void Afisare_Componente_Biconexe();
    void DFS_Componente_Biconexe(int s, int tata, bool viz[], int nivel[], int niv_min_acc[], int &ct_biconexe, stack <int> &S2);

    // APM
    vector<pair<int,int>> Kruskal(int &cost, int &ct_muchii_adaugate);

    // Dijkstra
    vector<int> Dijkstra(int s);

    // Bellman-Ford
    bool Bellman_Ford(int s, vector<int>&sol);

    // Paduri de multimi disjuncte
    vector<bool> Disjoint(int parinte[NMax]);
    int Find(int x, int parinte[NMax]);
    void Union(int x, int y, int parinte[NMax]);

    //Roy-Floyd
    void Roy_Floyd(int matrice[NMax1][NMax1]);

    // Diametrul unui arbore
    int Diametru_Arbore();
    void BFS_Diametru_Arbore(int s, int &ultim, int &distanta_maxima);

    // Ciclu Eulerian
    void Ciclu_Eulerian();
    void Euler(int s, bool viz[NMax], int &ct, vector<int>&Sol);
};


int N, M;

//-----------Tema1---------------------------------------------------
// DFS

// BFS

// Muchii critice

// Componente biconexe

// Kosaraju
stack <int> S; // stiva pentru memorarea nodurilor in ordinea timpilor de final
vector <int> grT[NMax]; // liste de adiacenta ale grafului transpus

// Havel-Hakimi

// Muchii Critice + Componente Biconexe
vector <vector<int>> muchii_critice;

// Componente Biconexe
vector <int> componente_biconexe[NMax];


//-----------Tema2---------------------------------------------------
// Kruskal

// Dijkstra
vector<pair<int,int>> muchii[NMax25];

// Bellman-Ford

// Disjoint


//-----------Tema3---------------------------------------------------
// Roy-Floyd

// Diametru arbore


//-----------Tema4---------------------------------------------------
// Ciclu eulerian


graf :: graf(int n, int m, bool o)
{
    nrNoduri = n;
    nrMuchii = m;
    orientat = o;
}

void graf :: Citire_Orientat()
{
    for(int i = 1; i <= nrMuchii; ++i)
    {
        int x, y;
        fin >> x >> y;
        gr[x].push_back(y);
    }
}

void graf :: Citire_Neorientat()
{
    for(int i = 1; i <= nrMuchii; ++i)
    {
        int x, y;
        fin >> x >> y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
}

void graf :: Citire_Arbore()
{
    for(int i = 1; i <= nrMuchii; ++i)
    {
        int x, y;
        fin >> x >> y;
        gr[x].push_back(y);
        gr[y].push_back(x);
    }
}

void graf :: Graf_Transpus()
{
    for(int i = 1; i <= nrNoduri; ++i)
        for(auto j : gr[i])
            grT[j].push_back(i);
}

void graf :: Afisare_Graf()
{
    for(int i=1; i <= nrNoduri; ++i)
    {
        fout << i << " : " ;
        for(auto j: gr[i])
            fout << j << " ";
        fout << "\n";
    }
}

vector <int> graf :: BFS(int s, bool viz[NMax])
{
    int distanta[NMax];
    vector <int> sol;
    queue <int> q;

    viz[s] = 1;
    q.push(s);

    while(!q.empty())
    {
        int k = q.front();  // elem din varful cozii
        q.pop();            // sterg elem din varful cozii
        for(auto i : gr[k])
            if(!viz[i])
            {
                viz[i] = 1;
                q.push(i);
                distanta[i] = distanta[k] + 1;
            }
    }

    for(int i = 1; i<= nrNoduri; ++i)
        sol.push_back(distanta[i]);

    return sol;
}

void graf :: DFS(int s, bool viz[NMax])
{
    viz[s] = 1;
    for(auto i : gr[s])
        if(!viz[i])
            DFS(i, viz);

    // pentru CTC(Kosaraju) - stabilim timpul de finalizare pentru nodul s
    S.push(s);
}

int graf :: Comp_Conexe(bool viz[NMax])
{
    int ct = 0;
    for(int i = 1; i <= nrNoduri; ++i)
        if(!viz[i])
        {
            ct++;
            DFS(i, viz);
        }
    return ct;
}

void graf :: ParcurgereGrafInitial(bool viz[NMax])
{
    for(int i = 1; i <= nrNoduri; ++i)
        if(!viz[i])
            DFS(i, viz);
}

void graf :: DFST(int s, bool vizDFST[NMax], vector<int> &aux)
{
    vizDFST[s] = 1;
    aux.push_back(s);

    for(auto i : grT[s])
        if(!vizDFST[i])
            DFST(i, vizDFST, aux);
}

vector<vector<int>> graf :: CTC()
{
    int ct_ctc = 0;
    bool vizDFST[NMax] = {0};

    vector<vector<int>> sol;

    while(!S.empty()) // luam nodurile din stiva si facem un dfs din nodul respectiv daca nodul nu a fost deja vizitat
    {
        // in acest caz se va forma o noua comp tare conexa
        int varf = S.top();
        S.pop();
        if(!vizDFST[varf])
        {
            ct_ctc ++;
            vector<int> aux;

            DFST(varf, vizDFST, aux);
            sol.push_back(aux);
        }
    }

    fout << ct_ctc << "\n";

    return sol;
}

bool myfunction(int i, int j)
{
    return (i>j);
}

bool graf :: Havel_Hakimi(vector <int> grade, int nrNoduri)
{
    bool ok =1;

    while(ok)
    {
        sort(grade.begin(), grade.end(), myfunction); // sortam descrescator

        if(grade[0] == 0) // daca cel mai mare element dupa sortare este 0 => toate elementele sunt 0 => se poate forma
            return true;

        if(grade[0] > grade.size() - 1) // daca gradul este mai mare decat (nr de noduri curente - 1 => NU se poate forma
            return false;

        int grad_curent = grade[0];
        grade.erase(grade.begin() + 0); // elimin primul element

        for(int i = 0; i < grad_curent; ++i) // scad 1 doar din primele grad_curent elemente
        {
            grade[i] --;
            if(grade[i] < 0)
                return false;
        }
    }
}

stack<int> graf :: Sortare_Topologica() // o parcurgere in adancime a grafului unde se determina timpii de finalizare pt fiecare nod
{
    // nodurile vor fi afisate in ordinea descrescatoare a timpilor de finalizare
    bool viz[NMax];
    ParcurgereGrafInitial(viz);

    return S;
}

void graf :: DFS_Muchii_Critice(int s, int tata, bool viz[], int nivel[], int niv_min_acc[], int &ct_muchii_critice)
{
    viz[s] = 1;
    nivel[s] = nivel[tata] + 1; // calculam nivelul pe care se afla nodul curent s
    niv_min_acc[s] = nivel[s]; // nivelul minim accesibil este acelasi cu nivelul pe care se afla nodul curent s pentru moment

    for(auto i : gr[s])
        if(i != tata)
        {
            if(viz[i] == 1)   // (s,i) (deci nu poate fi muchie critica) deoarece i a fost vizitat deja
            {
                if(niv_min_acc[s] > nivel[i])
                    niv_min_acc[s] = nivel[i];
            }
            else
            {
                DFS_Muchii_Critice(i, s, viz, nivel, niv_min_acc, ct_muchii_critice);

                if(niv_min_acc[s] > niv_min_acc[i])
                    niv_min_acc[s] = niv_min_acc[i];
            }

            // determinare muchii critice
            if(nivel[s] < niv_min_acc[i]) // conditie necesara ca (s,i) sa fie muchie critica
            {
                // (s, i)
                ct_muchii_critice++;
                vector <int> v1;
                v1.push_back(s);
                v1.push_back(i);
                muchii_critice.push_back(v1);
            }
        }
}

void graf :: Afisare_Muchii_Critice()
{
    bool viz[NMax] = {0};
    int nivel[NMax] = {0};
    int niv_min_acc[NMax] = {0};
    int ct_muchii_critice = 0;

    DFS_Muchii_Critice(1, 0, viz, nivel, niv_min_acc, ct_muchii_critice);

    fout << ct_muchii_critice << "\n";

    for(vector<vector<int>>::iterator i = muchii_critice.begin() ; i != muchii_critice.end(); i++)
    {
        fout << "[" ;
        vector<int>::iterator j = i->begin();
        fout<<*j;
        fout << ",";
        j++;
        fout <<*j;
        fout << "] ";
    }
}

void graf :: DFS_Componente_Biconexe(int s, int tata, bool viz[], int nivel[], int niv_min_acc[], int &ct_biconexe, stack <int> &S2)
{
    viz[s] = 1;
    S2.push(s); // adaugam nodurile in stiva S2 in oridinea in care le vizitam

    nivel[s] = nivel[tata] + 1; // calculam nivelul pe care se afla nodul curent s
    niv_min_acc[s] = nivel[s];  // nivelul minim accesibil este acelasi cu nivelul pe care se afla nodul curent s pentru moment

    for (auto i : gr[s])
    {
        if (viz[i] == 1)       // (s,i) (deci nu poate fi muchie critica) deoarece i a fost vizitat deja
        {
            if(niv_min_acc[s] > nivel[i])
                niv_min_acc[s] = nivel[i];
        }
        else
        {
            DFS_Componente_Biconexe(i, s, viz, nivel, niv_min_acc, ct_biconexe, S2);

            if(niv_min_acc[s] > niv_min_acc[i])
                niv_min_acc[s] = niv_min_acc[i];


            // determinare componente biconexe
            if(niv_min_acc[i] >= nivel[s]) // conditie necesara ca (s,i) sa fie muchie critica
            {
                ct_biconexe ++;

                while(!S2.empty() && S2.top() != i) // eliminam nodurile pana la nodul i
                {
                    componente_biconexe[ct_biconexe].push_back(S2.top());
                    S2.pop();
                }
                componente_biconexe[ct_biconexe].push_back(S2.top()); // adaugam si nodul i
                S2.pop();
                componente_biconexe[ct_biconexe].push_back(s);        // adaugam si nodul s
            }
        }
    }
}

void graf :: Afisare_Componente_Biconexe()
{
    bool viz[NMax] = {0};

    int nivel[NMax] = {0};
    int niv_min_acc[NMax] = {0};
    int ct_biconexe = 0;
    stack <int> S;

    DFS_Componente_Biconexe(1, 0, viz, nivel, niv_min_acc, ct_biconexe, S);

    fout << ct_biconexe << "\n";

    for(int i = 1; i <= ct_biconexe; ++i)
    {
        for(auto j : componente_biconexe[i])
            fout << j << " ";
        fout << "\n";
    }
}

vector<pair<int,int>> graf :: Kruskal(int &cost, int &ct_muchii_adaugate)
{
    pair< int, pair<int, int> > v[NMax]; // structura de date pt graful neorientat ponderat -> (c, {x,y})
    int C[NMax];                         // C[x] = numarul componentei din care face parte nodul x
    vector<pair<int,int>> Sol;           // structura de date pt arcele din APM

    // citire graf ponderat
    for(int i = 1; i <= nrMuchii; ++i)
    {
        fin >> v[i].second.first >> v[i].second.second; // muchia (x,y)
        fin >> v[i].first;                              // cu costul c
    }

    sort(v + 1, v + nrMuchii + 1); // sortam crescator muchiile in functie de cost

    for(int i = 1; i <= nrNoduri; ++i) C[i] = i; // initial se pleaca cu n arbori formati dintr-un singur nod

    for(int i = 1; i <= nrMuchii && ct_muchii_adaugate < nrNoduri - 1; ++i)
    {
        // verificam daca muchia i poate fi adaugata
        // cele doua extremitati trebuie sa faca parte din compomnente conexe diferite
        if(C[v[i].second.first] != C[v[i].second.second])
        {
            cost += v[i].first;      // marim costul arborelui

            ct_muchii_adaugate++;    // adaugam muchia de ordin i la arbore
            Sol.push_back({v[i].second.first,v[i].second.second});

            // unificare
            int cx = C[v[i].second.first];  // componenta din care face parte o extremitate -> x
            int cy = C[v[i].second.second]; // componente din care face parte cealalta extremitate -> y
            for(int j = 1; j <= nrNoduri; ++j)
                if(C[j] == cx) // pt toate nodurile care fac parte din componenta lui x le vom trece in componenta lui y
                    C[j] = cy;
        }
    }

    return Sol;
}

vector<int> graf :: Dijkstra(int s)
{
    priority_queue <pair<int,int>> q;   // coada cu prioritati {cost,nod}
    bool vizDij[NMax5] = {0};     // viz[x] = 1 daca nodul a fost vizitat
    int dist[NMax5];        // dist[x] = distanta de la nodul de start la nodul x
    vector <int> Sol;

    // initial presupunem fiecare distanta ca fiind infinit
    for(int i = 1; i <= N; ++i)
        dist[i] = inf;

    q.push({0,s});  // adaugam in coada nodul de inceput cu costul 0 (de la s la s avem distanta 0)
    vizDij[s] = 1;  // marcam nodul ca fiind vizitat
    dist[s] = 0;    // distanta de la s la s va fi 0

    while(!q.empty())
    {
        int nod_curent = q.top().second; // nodul curent
        q.pop();

        vizDij[nod_curent] = 0; // presupunem ca nodul curent nu a fost vizitat inca

        for(auto i : muchii[nod_curent])  // parcurgem nodurile adiacente cu nodul curent
        {
            int y = i.second;      // nodul adiacent cu nodul curent
            int cost = i.first;    // costul de la nodul curent  pana la y

            if(dist[nod_curent] + cost < dist[y])
            {
                dist[y] = dist[nod_curent] + cost;
                if(!vizDij[y]) // marcam nodul ca fiind vizitat daca nu era
                {
                    vizDij[y] = 1;
                    q.push({dist[y],y}); // adaugam din nou in coada pt ce ne ar putea imbunatati costul ulterior
                }
            }
        }
    }

    for(int i = 2; i <= nrNoduri; ++i)
    {
        if(dist[i] != inf)
            Sol.push_back(dist[i]);
        else
            Sol.push_back(0);
    }

    return Sol;
}

bool graf :: Bellman_Ford(int s, vector<int>&Sol)
{
    queue <int> C;
    vector <bool> adaugat(nrNoduri + 1, 0);
    vector <int> dist(nrNoduri + 1, inf);
    vector <int> viz(nrNoduri + 1, 0);
    bool ciclu_negativ = 0;

    // declarare si citire graf ponderat
    vector <vector <pair<int, int> >> muchii(nrNoduri + 1);
    for(int i = 1; i <= nrMuchii; ++i)
    {
        int x, y, cost;
        fin >> x >> y >> cost;
        muchii[x].push_back({cost,y});
    }

    C.push(s);          // adaugam nodul s in coada
    dist[s] = 0;        // distanta de la s la s va fi 0
    adaugat[s] = 1;     // marcam cu 1 nodul ca fiind adaugat in coada

    while(!C.empty() && !ciclu_negativ)
    {
        int nod_curent = C.front();
        C.pop();
        adaugat[nod_curent] = 0; // punem 0 pt ca nodul a fost eliminat din coada


        for(int i = 0; i < muchii[nod_curent].size(); ++i) // parcurgem nodurile adiacente cu nodul curent
        {
            int y = muchii[nod_curent][i].second;   // nodul destinatie
            int cost = muchii[nod_curent][i].first; // costul de la nodul curent la nodul destinatie

            if(dist[nod_curent] + cost < dist[y])   // recalculam distanta minima daca este necesar
            {
                dist[y] = dist[nod_curent] + cost;

                if(!adaugat[y]) // adaugam nodul in coada daca nu exista deja
                {
                    C.push(y);
                    adaugat[y] = 1;
                }

                viz[y] ++;
                if(viz[y] >= nrNoduri) // cazul pt care se formeaza ciclu negativ
                {
                    ciclu_negativ = 1;
                    break;
                }
            }
        }
    }

    if(!ciclu_negativ)
    {
        for(int i = 2; i <= nrNoduri; ++i)
            Sol.push_back(dist[i]);
    }
    return ciclu_negativ;
}

int graf :: Find(int x, int parinte[NMax]) // determina radacina arborelui din care face parte nodul x
{
    if(parinte[x] == x) // inseamna ca x insusi este radacina
        return x;
    else
    {
        parinte[x] = Find(parinte[x], parinte); // apeleaza recursiv pana ajunge la radacina
        return parinte[x];
    }
}

void graf :: Union(int x, int y, int parinte[NMax]) // se reunesc multimile celor doua numere x si y
{
    // unim radacina lui x cu radacina lui y (adaugand rad lui y la rad lui x)
    int a, b;
    a = Find(x, parinte);
    b = Find(y, parinte);
    parinte[b] = a;
}

vector<bool> graf :: Disjoint(int parinte[NMax])
{
    vector<bool> Sol;
    for(int i = 1; i <= nrNoduri; ++i) // initial fiecare nod este propriul sau parinte
        parinte[i] = i;

    for(int i = 1; i <= M; ++i)
    {
        int op, x, y;
        fin >> op >> x >> y;

        if(op == 1) // se reunesc multimile nodurilor x si y, adica vor avea acelasi parinte
            Union(x, y, parinte);
        else
        {
            int a = Find(x, parinte);  // daca nodurile x si y au aceeasi radacina atunci sunt din aceeasi multime
            int b = Find(y, parinte);
            if(a == b)
                Sol.push_back(true);
            else
                Sol.push_back(false);
        }
    }
    return Sol;
}

void graf :: Roy_Floyd(int matrice[NMax1][NMax1])
{
    for(int k = 1; k <= nrNoduri; ++k)
        for(int i = 1; i <= nrNoduri; ++i)
            for(int j = 1; j <= nrNoduri; ++j)
                if(matrice[i][j] > matrice[i][k] + matrice[k][j])
                    matrice[i][j] = matrice[k][j] + matrice[i][k];

    // afisare
    for(int i = 1; i <= nrNoduri; ++i)
    {
        for(int j = 1; j <= nrNoduri; ++j)
            if(matrice[i][j] != inf2)
                fout << matrice[i][j] << " ";
            else fout << 0 << " ";
        fout << "\n";
    }
}

void graf :: BFS_Diametru_Arbore(int s, int &capat, int &distanta_maxima)
{
    int distanta[NMax];
    queue <int> q;
    bool viz[NMax] = {0};

    viz[s] = 1;
    distanta[s] = 1;
    q.push(s);

    while(!q.empty())
    {
        int k = q.front();  // elem din varful cozii
        q.pop();            // sterg elem din varful cozii
        for(auto i : gr[k])
            if(!viz[i])
            {
                viz[i] = 1;
                q.push(i);
                distanta[i] = distanta[k] + 1;
            }
    }

    distanta_maxima = 0;
    for(int i = 1; i<= nrNoduri; ++i)
        if(distanta[i] > distanta_maxima)
        {
            distanta_maxima = distanta[i];
            capat = i;
        }
}

int graf :: Diametru_Arbore()
{
    int capat1, capat2, distanta_maxima;
    BFS_Diametru_Arbore(1, capat1, distanta_maxima); // facem un BFS din primul nod si aflam capatul cel mai indepartat si distanta pana la capatul cel mai indepartat
    BFS_Diametru_Arbore(capat1, capat2, distanta_maxima); // facem un BFS din capatul rezultat in apelul anterior si aflam capatul cel mai indepartat de acesta si distanta dintre ele

    return distanta_maxima;
}

void graf :: Euler(int s, bool viz[NMax], int &ct, vector<int>&Sol)
{
    while (!muchii[s].empty()) // luam pe rand fiecare nod adiacent cu nodul s
    {
        int vecin = muchii[s].back().second; // nod vecin cu nodul s
        int muchie = muchii[s].back().first; // index muchie
        muchii[s].pop_back();

        if(viz[muchie] == 0)
        {
            viz[muchie] = 1;
            Euler(vecin, viz, ct, Sol);
        }
    }
    ct++;
    Sol.push_back(s);
}

void graf :: Ciclu_Eulerian()
{
    for (int i = 1; i <= nrMuchii; ++i) // citire muchii
    {
        int x, y;
        fin >> x >> y;
        muchii[x].push_back({i, y});
        muchii[y].push_back({i, x});
    }

    for (int i = 1; i <= nrNoduri; ++i) // verificam gradul fiecarui nod sa fie par
        if (muchii[i].size() % 2)
        {
            fout << "-1";
            return;
        }

    bool viz[NMax] = {0};
    int ct = 0;
    vector<int> Sol;

    Euler(1, viz, ct, Sol);

    for (auto i : Sol)
        fout << i << " ";
}



int main()
{
    cout << "Alegeti task-ul:\n Task 1: DFS - Afisare numar componente conexe\n Task 2: BFS\n Task 3: Determinare CTC\n Task 4: Havel-Hakimi\n";
    cout << " Task 5: Sortare topologica\n Task 6: Afisare muchii critice\n Task 7: Componente biconexe\n Task 8: APM\n Task 9: Dijkstra\n Task 10: Bellman-Ford\n Task 11: Disjoint\n";
    cout << " Task 12: Roy-Floyd\n Task 13: Diametru arbore\n";
    cout << " Task 14: Ciclu Eulerian\n\n";
    cout << "Scrie task-ul : ";

    int task;
    cin >> task;

    if(task == 1) // DFS - nr comp conexe
    {
        bool viz[NMax] = {0};
        fin >> N >> M;
        graf G(N, M, 0);
        G.Citire_Neorientat();
        int nr_componente_conexe = G.Comp_Conexe(viz);
        fout << nr_componente_conexe << "\n";
    }
    else if(task == 2) // BFS
    {
        int s;
        bool viz[NMax];
        fin >> N >> M >> s;
        graf G(N, M, 1);
        G.Citire_Orientat();
        vector <int> distante = G.BFS(s, viz);

        int poz = 1;
        for(auto i : distante)
            if(viz[poz])
                fout << i << " ", poz++;
            else
                fout << -1 << " ", poz++;
    }

    else if(task == 3) // Componente tare conexe
    {
        bool viz[NMax] = {0};
        vector<vector<int>> sol;

        fin >> N >> M;
        graf G(N, M, 1);
        G.Citire_Orientat();
        G.Graf_Transpus();
        G.ParcurgereGrafInitial(viz);
        sol = G.CTC();

        for (int i = 0; i < sol.size(); ++i)
        {
            for (int j = 0; j < sol[i].size(); ++j)
                fout << sol[i][j] << " ";
            fout << "\n";
        }
    }

    else if(task == 4) // Havel - Hakimi
    {
        fin >> N;
        graf G(N, 0, 0);

        vector <int> grade;

        for(int i = 1; i <= N; ++i)
        {
            int x;
            fin >> x;
            grade.push_back(x);
        }

        bool ok = G.Havel_Hakimi(grade, N);
        if(ok == true)
            fout << "DA se poate construi un graf.";
        else fout << "NU se poate construi un graf. ";
    }

    else if(task == 5) // Sortare Topologica
    {
        fin >> N >> M;
        graf G(N, M, 1);

        stack <int> sol;

        G.Citire_Orientat();
        sol = G.Sortare_Topologica();

        while(!sol.empty())
        {
            fout << sol.top() << " ";
            sol.pop();
        }
    }
    else if(task == 6) // Muchii critice
    {
        fin >> N >> M;
        graf G(N, M, 0);
        G.Citire_Neorientat();
        G.Afisare_Muchii_Critice();
    }
    else if(task == 7) // Componente biconexe
    {
        fin >> N >> M;
        graf G(N, M, 0);
        G.Citire_Neorientat();
        G.Afisare_Componente_Biconexe();
    }
    else if(task == 8) // APM - Kruskal
    {
        fin >> N >> M;
        graf G(N, M, 0);

        int cost = 0, ct_muchii_adaugate = 0; // costul minim total, numarul de muchii adaugate in subgraful de cost minim determinat
        vector <pair<int,int>> Sol;
        Sol = G.Kruskal(cost, ct_muchii_adaugate);

        // afisare cost, nr muchii si muchii
        fout << cost << "\n" << ct_muchii_adaugate << "\n";
        for(auto i : Sol)
            fout << i.first << " " << i.second << "\n";
    }
    else if(task == 9) // Dijkstra
    {
        fin >> N >> M;
        graf G(N, M, 0);

        vector <int> Sol;

        //citire
        for(int i = 1; i <= M; ++i)
        {
            int x, y, cost;
            fin >> x >> y >> cost;
            muchii[x].push_back({cost,y});
        }

        // apel functie + afisare
        Sol = G.Dijkstra(1);
        for(auto i : Sol)
            fout << i << " ";
    }
    else if(task == 10) // Bellman-Ford
    {
        fin >> N >> M;
        graf G(N, M, 0);

        vector<int>Sol;

        bool ciclu_negativ = G.Bellman_Ford(1, Sol);

        if(ciclu_negativ == 0)
            for(auto i: Sol)
                fout << i << " ";
        else
            fout << "Ciclu negativ!";
    }
    else if(task == 11) // Disjoint
    {
        fin >> N >> M;
        graf G(N, 0, 0);

        int parinte[NMax];
        vector<bool>Sol;
        Sol = G.Disjoint(parinte);


        for(auto i : Sol)
            if(i == 1)
                fout << "DA\n";
            else fout << "NU\n";
    }
    else if(task == 12) // Roy-Floyd
    {
        fin >> N;
        graf G(N, 0, 0);

        int matrice[NMax1][NMax1];

        // citire
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
                fin >> matrice[i][j];

        // initializare
        for(int i = 1; i <= N; ++i)
            for(int j = 1; j <= N; ++j)
                if(i == j)
                    matrice[i][j] = 0;
                else if(i != j && matrice[i][j] == 0)
                    matrice[i][j] = inf2;

        G.Roy_Floyd(matrice);
    }
    else if(task == 13) // Diametru arbore
    {
        fin >> N;
        graf G(N, N-1, 0); // arbore
        G.Citire_Arbore();
        int d = G.Diametru_Arbore();
        fout << d;
    }
    else if(task == 14) // Ciclu Eulerian
    {
        fin >> N >> M;
        graf G(N, M, 0);
        G.Ciclu_Eulerian();
    }
    return 0;
}

