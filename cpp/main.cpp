#include <iostream>
#include <random>
#include <ctime>
#include <gmpxx.h>
using namespace std;

#define MAX_TEXT_LENGHT 2048

mpz_class z_powm(const mpz_class base, mpz_class exponent, const mpz_class modulo);
mpz_class z_gcd(mpz_class a, mpz_class b);
mpz_class z_multiplicate_inverse(mpz_class e, mpz_class phi);
bool z_isPrime(mpz_class number);

void z_generate_keypair(const mpz_class prime_one, const mpz_class prime_two, mpz_class* result);

void z_encrypt(const mpz_class* z_key, const char* plaintext, const int lenght, mpz_class* result);
void z_decrypt(const mpz_class* z_key, const mpz_class* cipher, const int lenght, char* result);

int main()
{
    srand(time(NULL));

    mpz_class input_prime_one, input_prime_two, key_pair[3], encrypted_text[MAX_TEXT_LENGHT];
    char input_plaintext[MAX_TEXT_LENGHT], decrypted_text[MAX_TEXT_LENGHT];

    cout << "Hello world!" << endl << "Note: Accents will not work because of cin limitations." << endl << endl;

    cout << "Enter a prime number: ";
    cin >> input_prime_one;

    if (!z_isPrime(input_prime_one)){ //Optional
        cout << endl << "This is not a prime number !" << endl << endl << "Exit 1" << endl;
        return 1;
    }

    cout << endl << "Enter another prime number: ";
    cin >> input_prime_two;

    if (input_prime_one == input_prime_two){ //Optional
        cout << endl << "The numbers you entered are identical !" << endl << endl << "Exit 1" << endl;
        return 1;
    }

    if (!z_isPrime(input_prime_two)){ //Optional
        cout << endl << "This is not a prime number !" << endl << endl << "Exit 1" << endl;
        return 1;
    }

    z_generate_keypair(input_prime_one, input_prime_two, key_pair);

    cout << endl <<  "Common key: " << key_pair[0]
         << endl <<  "Public key: " << key_pair[1]
         << endl << "Private key: " << key_pair[2];

    cout << endl << "Enter a text to encrypt: ";

    cin.ignore();
    cin.getline(input_plaintext, MAX_TEXT_LENGHT);

    int text_lenght = strlen(input_plaintext); //needed for the decryption because there's no clean way to obtain an array's lenght

    cout << endl << "Text lenght: " << text_lenght;

    z_encrypt(key_pair, input_plaintext, text_lenght,encrypted_text);

    cout << endl << "Encrypted text: "; //note that the output is not representative since the value is stored in an array
    for (int i=0; i<text_lenght; ++i) // plus the encryption is made on characters 1 by 1
        cout << encrypted_text[i];

    z_decrypt(key_pair, encrypted_text, text_lenght, decrypted_text);

    cout << endl << "Decrpted text: ";
    for (int i=0; i<text_lenght; ++i)
        cout << decrypted_text[i];
    cout << endl << endl << "Exit 0" << endl;
    return 0;
}


mpz_class z_powm(const mpz_class base, mpz_class exponent, const mpz_class modulo)
{
    mpz_class x=1, y=base;
    while (exponent>0){
        if (exponent % 2 == 1)
            x = (x*y) % modulo;
        y = (y*y) % modulo;
        exponent /=2;
    }

    return x%modulo;
}

mpz_class z_gcd(mpz_class a, mpz_class b)
{
    mpz_class c;
    while (b!=0)
    {
        c = b;
        b = a%b;
        a = c;
    }
    return a;
}

mpz_class z_multiplicate_inverse(mpz_class e, mpz_class phi)
{
    mpz_class d = 0, x1 = 0, x2 = 1, y1 = 1, temp_phi = phi, temp1, temp2, x, y;

    while (e >0){
        temp1 = temp_phi/e;
        temp2 = temp_phi - temp1*e;
        temp_phi = e;
        e = temp2;

        x = x2 - temp1*x1;
        y = d - temp1*y1;

        x2 = x1;
        x1 = x;
        d = y1;
        y1 = y;
    }

    if (temp_phi == 1) return d+phi;

    return -1; //failsafe
}

void z_generate_keypair(const mpz_class prime_one, const mpz_class prime_two, mpz_class* result) //since return can't return arrays you need a pointer to an exteernal array...
{
    //check for primarity ?

    mpz_class p_times_q = prime_one * prime_two;

    mpz_class phi = (prime_one - 1) * (prime_two -1);

    mpz_class e = rand() % phi + 1;

    mpz_class g = z_gcd(e, phi);

    while (g != 1) {
        e = rand() % phi + 1;
        g = z_gcd(e, phi);
    }

    mpz_class d = z_multiplicate_inverse(e, phi);

    //0 is common key(modulo), 1 is public key, 3 is private key

    result[0] = p_times_q;
    result[1] = e;
    result[2] = d;

    return;
}

void z_encrypt(const mpz_class* z_key, const char* plaintext, const int lenght, mpz_class* result) //same here
{
    for (int i=0; i<lenght; ++i){
        result[i] = z_powm(mpz_class(plaintext[i]), z_key[1], z_key[0]);
    }
    return;
}

void z_decrypt(const mpz_class* z_key, const mpz_class* cipher, const int lenght, char* result) //same
{
    for (int i=0; i<lenght; ++i){
        result[i] = z_powm(cipher[i], z_key[2], z_key[0]).get_ui();
    }
    return;
}

bool z_isPrime(mpz_class number)
{
    if(number<2)
        return false;
    if(number==2)
        return true;
    if(number%2==0)
        return false;
    for(int i=3;i<=sqrt(number);i += 2)
    {
        if(number%i==0)
            return false;
    }
    return true;
}
