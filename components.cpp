#ifndef COMPONENTS
#define COMPONENTS
/* Necessario para nao precisar escrever std:: */
using namespace std;

class Components
{
    public:
        Components(string n, int a, int b)
        {
            setNome(n);
            setNoA(a);
            setNoB(b);
        }

        void setNome(string n)
        {
            nome = n;
        }

        string getNome()
        {
            return nome;
        }

        void setNoA(int a)
        {
            noA = a;
        }

        int getNoA()
        {
            return noA;
        }

        void setNoB(int b)
        {
            noB = b;
        }

        int getNoB()
        {
            return noB;
        }

    private:
        string nome;
        int noA;
        int noB;
};

#endif