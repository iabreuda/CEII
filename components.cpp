#ifndef COMPONENTS
#define COMPONENTS

/* Necessario para nao precisar escrever std:: */
using namespace std;

class Components
{
    public:
        /**
         * Construtor
         */
        Components(string n, int a, int b)
        {
            setNome(n);
            setNoA(a);
            setNoB(b);
        }

        /**
         * Define o nome do componente
         * @param n nome na netlist
         */
        void setNome(string n)
        {
            nome = n;
        }

        /**
         * Retorna o nome do component
         */
        string getNome()
        {
            return nome;
        }

        /**
         * Define o no A do componente
         * @param a no A
         */
        void setNoA(int a)
        {
            noA = a;
        }

        /**
         * Retorna o no A
         */
        int getNoA()
        {
            return noA;
        }

        /**
         * Define o no B do componente
         * @param b no B
         */
        void setNoB(int b)
        {
            noB = b;
        }

        /**
         * Retorna o no B
         */
        int getNoB()
        {
            return noB;
        }

    private:
        /**
         * Nome do componentena netlist
         */
        string nome;
        /**
         * Terminal A
         */
        int noA;
        /**
         * Terminal B
         */
        int noB;
};

#endif