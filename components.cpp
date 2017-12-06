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
            setNos(2);
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
         * Define a linearidade do componente
         */
        void setLinearidade(bool l)
        {
            linear = l;
        }

        /**
         * retorna a linearidade do componente
         */
        bool getLinearidade()
        {
            return linear;
        }

        /**
         * Verifica se o componente e linear
         */
        bool isLinear()
        {
            return linear == true;
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

        /**
         * Metodos virtuais utilizados por componentes de 4 terminais
         */
        int virtual getNoC() {return 0;};
        int virtual getNoD() {return 0;};
        /**
         * Necessario para pegar as correntes no capacitor, caso contrario
         * o metodo nao pode ser utilizado no vetor de componentes
         */
        void virtual setCorrente(double v) {};
        double virtual getCorrente() {return 0;};
        double virtual getCapacitancia() {return 0;};

        /**
         * numero de nos de ligacao
         */
        void setNos(int n)
        {
            nos = n;
        }

        /**
         * Retorna numero de nos de ligacao
         */
        int getNos()
        {
            return nos;
        }

        /**
         * Estanpa da matriz nodal abstrata
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         */
        void virtual estampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<string> nodes,
            vector<double> resultado) = 0;

        /**
         * Desestampa da matriz nodal abstrata
         * @param condutancia matriz de condutancia
         * @param correntes   matriz de correntes
         */
        void virtual desestampar(vector<vector<double> >& condutancia,
            vector<double>& correntes,
            vector<double> resultado) {};

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
        /**
         * Numero de nos
         */
        int nos;
        /**
         * Linearidade do componente
         */
        bool linear = true;
};

#endif