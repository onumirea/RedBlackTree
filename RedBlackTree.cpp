#include <iostream>
#include <fstream>
using namespace std;

struct Nod
{public:
    long long val;
    bool culoare;
    Nod *st, *dr, *parinte;

    Nod()
    {
       this->val = val;
       st = dr = parinte = NULL;
       this->culoare = 0;
    }
       Nod(long long val)
    {
        this->val = val;
        st=dr=parinte=NULL;
        this->culoare = 0;
    }
    ~Nod()
    {
          if(st!= NULL)
            delete[] st;
             if(dr!= NULL)
            delete[] dr;
             if(parinte!= NULL)
            delete[] parinte;
    }
      Nod& operator=(const Nod& n)
    {
        if(this != &n)
        {
            this->val = n.val;
            this->culoare=n.culoare;
            this->st=n.st;
            this->dr=n.dr;
            this->parinte=n.parinte;
        }

        return *this;
    }
};

Nod* radacina=NULL;
struct ArboreRN
{
public:
    Nod *radacina;
public:
    ArboreRN()
    { this->radacina = NULL; }
    void inser(const long long &n);
    void AfisareInOrdineFinal();
    void RotireStanga(Nod *&);
    void RotireDreapta(Nod *&);
     void InsertFix(Nod *&, Nod *&);
     void deleteFix(Nod *&);
     void delet(const long long &val);
     long long caz3(const long long &val);
     long long caz4(const long long &val);
     long long caz5(const long long &val);
     void caz6(Nod *&,long long &x,long long &y);
};

Nod* BSTInsert(Nod* radacina, Nod *n)
{
    if (radacina == NULL)
       return n;
    else if (n->val < radacina->val)
    {
        radacina->st  = BSTInsert(radacina->st, n);
        radacina->st->parinte = radacina;
    }
    else if (n->val > radacina->val)
    {
        radacina->dr = BSTInsert(radacina->dr, n);
        radacina->dr->parinte = radacina;
    }

    return radacina;
}

void ArboreRN::inser(const long long &val)
{
    Nod *n = new Nod(val);
    radacina = BSTInsert(radacina, n);
    InsertFix(radacina, n);
}

void ArboreRN::RotireStanga(Nod *&n)
{
    Nod *copil_dr = n->dr;
    n->dr = copil_dr->st;

    if (n->dr != NULL)
        n->dr->parinte = n;

    copil_dr->parinte = n->parinte;

    if (n->parinte == NULL)
        radacina = copil_dr;
    else if (n == n->parinte->st)
        n->parinte->st = copil_dr;
    else
        n->parinte->dr = copil_dr;

    copil_dr->st = n;
    n->parinte = copil_dr;
}

void ArboreRN::RotireDreapta(Nod *&n)
{
    Nod *copil_st = n->st;
    n->st = copil_st->dr;

    if (n->st != NULL)
        n->st->parinte = n;

    copil_st->parinte = n->parinte;

    if (n->parinte == NULL)
        radacina = copil_st;
    else if (n == n->parinte->st)
        n->parinte->st = copil_st;
    else
        n->parinte->dr = copil_st;

    copil_st->dr = n;
    n->parinte = copil_st;
}
void ArboreRN::InsertFix(Nod *&radacina, Nod *&n)
{
    Nod *parinte_n = NULL;
    Nod *bunic_n = NULL;

    while ((n != radacina) && (n->culoare != 0) &&
           (n->parinte->culoare == 1))
    {

        parinte_n = n->parinte;
        bunic_n = n->parinte->parinte;

        if (parinte_n == bunic_n->st)
        {

            Nod *unchi_n = bunic_n->dr;

            if (unchi_n != NULL && unchi_n->culoare ==1)
            {
                bunic_n->culoare = 1;
                parinte_n->culoare = 0;
                unchi_n->culoare = 0;
                n = bunic_n;
            }

            else
            {
                if (n == parinte_n->dr)
                {
                    RotireStanga(parinte_n);
                    n = parinte_n;
                    parinte_n = n->parinte;
                }

                else
                {RotireDreapta(bunic_n);
                swap(parinte_n->culoare, bunic_n->culoare);
                n = parinte_n;}
            }
        }

        else
        {
            Nod *unchi_n = bunic_n->st;

            if ((unchi_n != NULL) && (unchi_n->culoare ==
                                                    1))
            {
                bunic_n->culoare = 1;
                parinte_n->culoare = 0;
                unchi_n->culoare = 0;
                n = bunic_n;
            }
            else
            {
                if (n == parinte_n->st)
                {
                    RotireDreapta(parinte_n);
                    n = parinte_n;
                    parinte_n = n->parinte;
                }

                RotireStanga(bunic_n);
                swap(parinte_n->culoare,
                         bunic_n->culoare);
                n = parinte_n;
            }
        }
    }

    radacina->culoare = 0;
}

Nod* NodValMinima(Nod* node)
{
    Nod* current = node;

    while (current && current->st != NULL)
        current = current->st;

    return current;
}


void ArboreRN::deleteFix(Nod *&x)
{
    Nod* s;
    while (x != radacina && x->culoare == 0)
    {
      if (x == x->parinte->st)
      {
        s = x->parinte->dr;
        if (s->culoare == 1)
        {
          s->culoare = 0;
          x->parinte->culoare = 1;
          RotireStanga(x->parinte);
          s = x->parinte->dr;
        }

        if (s->st->culoare == 0 && s->dr->culoare == 0)
        {
          s->culoare = 1;
          x = x->parinte;
        }
        else
        {
              if (s->dr->culoare == 0)
              {
                s->st->culoare = 0;
                s->culoare = 1;
                RotireDreapta(s);
                s = x->parinte->dr;
              }

              s->culoare = x->parinte->culoare;
              x->parinte->culoare = 0;
              s->dr->culoare = 0;
              RotireStanga(x->parinte);
              x = radacina;
        }
      }
      else
      {
        s = x->parinte->st;
        if (s->culoare == 1)
        {
          s->culoare = 0;
          x->parinte->culoare = 1;
          RotireDreapta(x->parinte);
          s = x->parinte->st;
        }

        if (s->dr->culoare == 0 && s->dr->culoare == 0)
        {
          s->culoare = 1;
          x = x->parinte;
        }
          else
        {
          if (s->st->culoare == 0)
          {
            s->dr->culoare = 0;
            s->culoare = 1;
            RotireStanga(s);
            s = x->parinte->st;
          }

          s->culoare = x->parinte->culoare;
          x->parinte->culoare = 0;
          s->st->culoare = 0;
          RotireDreapta(x->parinte);
          x = radacina;
        }
      }
    }
    x->culoare = 0;
  }

Nod* deleteNod(Nod* radacina, long long val)
{

    if (radacina == NULL)
        return radacina;

    if (val < radacina->val)
        radacina->st = deleteNod(radacina->st, val);

    else if (val > radacina->val)
        radacina->dr = deleteNod(radacina->dr, val);
    else
    {

        if (radacina->st==NULL and radacina->dr==NULL)
            return NULL;

        else if (radacina->st == NULL)
        {
            Nod* temp = radacina->dr;
            return temp;
        }
        else if (radacina->dr == NULL)
        {
            Nod* temp = radacina->st;
            return temp;
        }

        Nod* temp = NodValMinima(radacina->dr);
        radacina->val = temp->val;
        radacina->dr = deleteNod(radacina->dr, temp->val);
    }
      return radacina;
}
  void ArboreRN::delet(const long long &val)
{
    deleteNod(radacina, val);
    deleteFix(radacina);
}

Nod* cautare(Nod* radacina, long long val)
{
    if (radacina == NULL || radacina->val == val)
       return radacina;

    if (radacina->val < val)
       return cautare(radacina->dr, val);

    return cautare(radacina->st, val);
}
void AfisareInOrdine(Nod *radacina, int space)
{
    int COUNT=1;
    if (radacina == NULL)
        return;

   space += COUNT;
   AfisareInOrdine(radacina->dr, space);
   for (int i = COUNT; i < space; i++)
      cout<<"\t";
   cout<<radacina->val<<"\n";
  AfisareInOrdine(radacina->st, space);

}
void ArboreRN::AfisareInOrdineFinal()
{
     AfisareInOrdine(radacina,0);
}




int main()
{
    ArboreRN a;
    a.inser(3);
    a.inser(1);
    a.inser(6);
    a.inser(5);
    a.inser(7);
    a.inser(4);
    cout << "Mr. Tree: ";
    cout<<endl;
    a.delet(5);
    a.AfisareInOrdineFinal();
    cout<<endl;
}
/*
   ccee88oo
  C8O8O8Q8PoOb o8oo
 dOB69QO8PdUOpugoO9bD
CgggbU8OU qOp qOdoUOdcb
    6OuU  /p u gcoUodpP
      \\\//  /douUP
        \\\////
         |||/\
         |||\/
         |||||
   .....//||||\....
*/


