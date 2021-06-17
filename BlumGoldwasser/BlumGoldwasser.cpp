#include "criptotools.h"

using namespace std;
using namespace BITS;

#if DEBUG
ofstream file;
#endif


typedef struct name1 
{
    unsigned long long p = 0;
    unsigned long long q = 0;
} large_primes;


typedef struct name2
{
    char* content = nullptr;
    unsigned long long int Xt_plus_1 = 0;
} enc_message;


class CRIPTOSISTEM BlumGoldwasser
{

private:
    large_primes pSIq;
    const char* path;

public:

    const unsigned int LungimeAlfabet;
    unsigned long long n;
    unsigned int blockSize;

    char* alfabet;
    char* message;
    enc_message encMessage;
    char* decMessage;

    constexpr BlumGoldwasser(unsigned int x, const char* y) :LungimeAlfabet(x), n(0), blockSize(0), path(y), //
        alfabet(nullptr), message(nullptr), encMessage({ nullptr, 0 }), decMessage(nullptr){};
    void load_system();
    int da_cod(char c);
    char da_caracter(int i);
    void generare_chei();
    void get_message(const char* x);
    void encrypt(const char* path);
    void decrypt();
    friend long long int* EuclidExtended(long long int a, long long int b);

};


void CRIPTOSISTEM BlumGoldwasser::generare_chei()
{
    unsigned long long int p;
    unsigned long long int q;
    srand(time(NULL));
    p = ( rand());
    while ((!prim(p)) || (p % 4 != 3)) p++;
    q = (rand());
    while ((!prim(q)) || (q % 4 != 3)) q++;
    pSIq.p = p;
    pSIq.q = q;


#if TEST

    pSIq.p = 11;
    pSIq.q = 7;

#endif // DEBUG

    n = pSIq.p * pSIq.q;
    blockSize = floor(log2(log2(n)));

#if DEBUG
    std::cout << pSIq.p << " TEST: " << prim(pSIq.p) << " TEST: " << pSIq.p % 4 << endl;
    std::cout << pSIq.q << " TEST: " << prim(pSIq.q) << " TEST: " << pSIq.q % 4 << endl;
    std::cout << "AFISAM N:   " << n << endl;
    std::cout << "floor(log2(log2(n))):  (lungimea blocului):  " << floor(log2(log2(n))) << endl;
    std::cout << "\n" << "\n";
    std::cout << "Afisam calea fisierului ce contine alfabetul:  ";
    for (int i = 0; i < strlen(path); i++)
        std::cout << path[i];
    std::cout << endl;
#endif

}



long long int* EuclidExtended(long long int a, long long int b)
{
    static long long int result[2] = { 0u, 0u };

    long long int xr[2], q, r;
    long long int x1[2] = { 1u, 0u };
    long long int x2[2] = { 0u, 1u };

    while(b != 0)
    {
        r = a % b;
        q = a / b;
        a = b;
        b = r;


        xr[0] = x1[0] - q * x2[0];
        xr[1] = x1[1] - q * x2[1];

        x1[0] = x2[0];
        x1[1] = x2[1];

        x2[0] = xr[0];
        x2[1] = xr[1];
    }

    if (a == 1) {
        result[0] = x1[0];
        result[1] = x1[1];
    }
    else
    {
        std::cout << endl << "Nu se poate rezolva ecuatia" << endl;
    }
    return result;
}

int CRIPTOSISTEM BlumGoldwasser::da_cod(char c)
{
    for (int i = 0; i < LungimeAlfabet; i++)
        if (alfabet[i] == c)
            return i;
    std::cout << "Textul contine caractere care nu exista in alfabet" << endl;
    return -1;
}

char CRIPTOSISTEM BlumGoldwasser::da_caracter(int i)
{
    return alfabet[modulo(i, LungimeAlfabet)];
}


void CRIPTOSISTEM BlumGoldwasser::load_system()
{
    alfabet = new char[LungimeAlfabet];

    ifstream in(path);
    char c;
    int i = 0;
    while (in >> noskipws >> c)
        alfabet[i++] = c;
    in.close();


#if DEBUG
    std::cout << "AFISAM ALFABETUL:   " << endl;
    for (int j = 0; j < i; j++)
        std::cout << alfabet[j] << "  ";
    std::cout << endl;
    std::cout << "ALFABETUL CONTINE   " << i << "  CARACTERE"<< endl << endl;
#endif // TEST

}

void CRIPTOSISTEM BlumGoldwasser::get_message(const char* path)
{
    char* temp_msg = new char[1000];
    ifstream in(path);

    char c;
    int i = 0, no_spaces = 0;
    while (in >> noskipws >> c)
    {
#if DEBUG
        std::cout << "  c si i:  " << c << "  " << i << endl;
#endif
        temp_msg[i++] = c;
    }
    in.close();

    i = i - 1;

    while ((i + 1) % blockSize != 0)
    {
        i++;
        no_spaces++;
    }
    message = new char[i + 2];

    std::copy(temp_msg, temp_msg + (i + 1 - no_spaces), message);
    for (int j = no_spaces - 1; j >= 0; j--)
    {
        message[i - j] = da_caracter(30);

    }
    message[i + 1] = '\0';

#if DEBUG
    std::cout << "Verificarea mesajului ca este citit corect: " << endl;
    for (int z = 0; z <= i; z++)
    {
        std::cout << message[z] << "  ";
        file << message[z];
    }
    file << "\n";
    file << pSIq.p << "," << pSIq.q << endl;

    std::cout << endl;
    std::cout << "Lungimea mesajului modifcat la cerintele criptarii este: " << strlen(message) << endl;
    std::cout << "Afisam numarul de spatii adaugate pentru a calibra mesajul la lungimea blocului: " << no_spaces << endl;
    std::cout << "\n\n\n";
#endif

    delete[] temp_msg;
    temp_msg = nullptr;
}

void CRIPTOSISTEM BlumGoldwasser::encrypt(const char* path)
{

    std::cout << endl << endl << endl;
    std::cout << "       CRIPTARE!!!     " << endl;
    std::cout << "\n\n";
    unsigned long long int p;
    unsigned long long int q;
    unsigned long long int random_int;

    unsigned int length = strlen(message);
    unsigned int t = length / blockSize;


    unsigned long long int h_bits_mask_of_1 = pow(2, blockSize) - 1;
    unsigned long long* x_i = new unsigned long long[t + 2];
    unsigned long long* p_i = new unsigned long long[t];
    unsigned long long pt_afisare;

    encMessage.content = new char[strlen(message) + 1];

    srand(time(NULL));
  
    do
    {
        p = (rand());
        q = (rand());
        random_int = p * q;
    } while (random_int >= n);

    

#if TEST
    random_int = 7;
#endif


    x_i[0] = a_la_b_mod_c(random_int, 2, n);

#if DEBUG
    std::cout << "random number generated: " << random_int << endl;
    std::cout << "X_i de 0:  " << x_i[0] << endl;
    std::cout << "h_bits_mask_of_1: " << h_bits_mask_of_1 << endl;
    file << random_int << endl;
#endif


    for (unsigned int i = 1; i <= length; i++)
    {

        if (i % blockSize == 0)
        {
            x_i[i/blockSize] = a_la_b_mod_c(x_i[i/blockSize - 1], 2, n);
            p_i[i/blockSize-1] = x_i[i/blockSize] & h_bits_mask_of_1;
            pt_afisare = ((unsigned long long int)da_cod(message[i-1])) ^ p_i[i/blockSize-1];
            encMessage.content[i-1] = (char)da_caracter(pt_afisare);

#if DEBUG
            std::cout << endl;
            std::bitset<64>  bit1(x_i[i/ blockSize]);
            std::cout << "reprezentarea binara a lui x_i de " << i/ blockSize << " este: \n" << bit1 << endl;
            std::cout << "X de i este:[" << i/ blockSize << "]:  " << x_i[i/ blockSize] << endl;
            std::cout << "P de i este:[" << i/ blockSize - 1 << "]:  " << p_i[i/ blockSize - 1] << endl;
            std::bitset<64>  bit2(p_i[i/ blockSize -1]);
            std::cout << "reprezentarea binara a lui p_i de " << i/ blockSize -1 << " este: \n" << bit2 << endl;
            std::cout << endl << endl;

#endif


        }
        else
        {
            pt_afisare = (unsigned long long int)da_cod(message[i - 1]);
            encMessage.content[i - 1] = (char)da_caracter(pt_afisare);
        }

#if DEBUG1
        std::cout << endl;
        std::cout << "mesajul necriptat cu indexul: " << i << " este: " << message[i - 1] << endl;
        std::bitset<64>  bit3((unsigned long long int)da_cod(message[i - 1]));
        std::cout << "functia \"da cod\"  returneaza: " << ((unsigned long long int)da_cod(message[i - 1])) << "  , adica:" << endl;
        std::cout << bit3 << endl;
        std::cout << "valoarea numerica a mesajului criptat: " << pt_afisare << endl;
        std::bitset<64>  bit4(pt_afisare);
        std::cout << "valoarea numerica in biti a mesajului criptat: \n" << bit4 << endl;
        std::cout << "mesajul criptat cu indexul:  " << i << " este de caracter: " << encMessage.content[i - 1] << endl;
        std::cout << "\n\n\n";
#endif
    }
    encMessage.content[length] = '\0';

    x_i[t+1] = a_la_b_mod_c(x_i[t], 2, n);
    encMessage.Xt_plus_1 = x_i[t+1];

    ofstream fout(path);

    for (int i = 0; i < strlen(encMessage.content); i++)
        fout << encMessage.content[i];
    fout.close();
}

void CRIPTOSISTEM BlumGoldwasser::decrypt()
{
    std::cout << endl << endl << endl;
    std::cout << "       DECRIPTARE!!!     " << endl;
    unsigned long long int dp, dq, up, uq, x0;
    long long int  rp, rq, * res;
    unsigned int length = strlen(encMessage.content);
    unsigned int t = length / blockSize;
    unsigned long long int h_bits_mask_of_1 = pow(2, blockSize) - 1;

    unsigned long long* x_i = new unsigned long long[t + 1];
    unsigned long long* p_i = new unsigned long long[t];
    decMessage = new char[length + 1]; // plus caracterul null
   

    dp = a_la_b_mod_c((pSIq.p + 1) / 4, t + 1, (pSIq.p - 1));
    dq = a_la_b_mod_c((pSIq.q + 1) / 4, t + 1, (pSIq.q - 1));

    up = a_la_b_mod_c(encMessage.Xt_plus_1, dp, pSIq.p);
    uq = a_la_b_mod_c(encMessage.Xt_plus_1, dq, pSIq.q);

    res = EuclidExtended(pSIq.p, pSIq.q);
    rp = res[0];
    rq = res[1];

    file << rp << "," << rq << endl;
    file << encMessage.Xt_plus_1;

    x_i[0] = modulo((uq * rp * pSIq.p + up * rq * pSIq.q), n);
   
    for (int i = 0; i < length; i++)
    {

        if ((i+1) % (blockSize) == 0)
        {
            x_i[(i + 1)/blockSize] = a_la_b_mod_c(x_i[(i + 1)/blockSize - 1], 2, n);
            p_i[(i + 1)/blockSize - 1] = x_i[(i + 1)/blockSize] & h_bits_mask_of_1;

            decMessage[i] = (char)da_caracter((unsigned long long int) da_cod(encMessage.content[i]) ^ p_i[(i + 1)/blockSize - 1]);
        }
        else
        {
            unsigned long long int pt_afisare = (unsigned long long int)da_cod(encMessage.content[i]);
            std::cout << "  T" << pt_afisare  << " ";
            decMessage[i] = da_caracter(pt_afisare);
        }
    }
    decMessage[length] = '\0';

#if DEBUG
    std::cout << "\n\n";
    std::cout << "Afisam (pSIq.p + 1)/4 si dp:  ( " << (pSIq.p + 1) / 4 << " si " << dp << " )" << endl;
    std::cout << "Afisam (pSIq.q + 1)/4 si dq:  ( " << (pSIq.q + 1) / 4 << " si " << dq << " )" << endl;
    std::cout << "Afisam encMessage.Xt_plus_1:  " << encMessage.Xt_plus_1 << endl;
    std::cout << "Afisam up:  " << up << endl;
    std::cout << "Afisam uq:  " << uq << endl;
    std::cout << "Afisam pSIq.p:  " << pSIq.p << endl;
    std::cout << "Afisam pSIq.q:  " << pSIq.q << endl;
    std::cout << "Afisam n:  " << n << endl;
    std::cout << "Afisam rp:  " << rp << endl;
    std::cout << "Afisam rq:  " << rq << endl;
    std::cout << "Afisam x_i[0]:  " << x_i[0] << endl;
    std::cout << "Afisam lungimea mesajului criptat: " << length << endl;
    std::cout << "\n\n";
    std::cout << "Afisam mesajul initial:" << endl;
    for (int i = 0; i < length; i++)
    {
        std::cout << message[i];
    }


    std::cout << endl << endl;;
    std::cout << "Afisam mesajul criptat:" << endl;
    for (int i = 0; i < length; i++)
    {
        std::cout << encMessage.content[i];
    }

    std::cout << endl << endl;;
    std::cout << "Afisam mesajul decriptat:" << endl;
    for (int i = 0; i < length; i++)
    {
        std::cout << decMessage[i];
    }

    std::cout << "\n\n\n";

#endif // DEBUG

}

int main()
{

    BlumGoldwasser criptosistem(32, "alfabet.txt");
    file.open("salvarenumere.txt");
    criptosistem.load_system();
    criptosistem.generare_chei();
    criptosistem.get_message("sursa.txt");
    criptosistem.encrypt("destinatie.txt");
    criptosistem.decrypt();
    file.close();
    
    std::cout << endl;
    SetOfBits<32> x(4);
    SetOfBits<32> y(6);
    x ^= y;

    
    for (int i = 0; i < x.length; i++)
        std::cout << x.representation[i];

    std::cout << endl;
 
    SetOfBits<32> z(0);
    for (int i = 0; i < z.length; i++)
        std::cout << z.representation[i];
    std::cout << endl;
    z.setBitsInterval(0, 5, 6);
    std::cout << z;
    std::cout << endl;

    unsigned long long int aux = z.getValueBitsInterval(0, 5);
    std::cout << aux;
    return 0;
}
