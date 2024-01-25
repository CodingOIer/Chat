#include <random>

#define KEY_LEN 32

std::mt19937 rnd(std::random_device{}());

char *makeKey()
{
    char *key = new char[KEY_LEN];
    for (int i = 0; i < KEY_LEN; i++)
    {
        int temp = rnd() % 61;
        if (temp <= 9)
        {
            key[i] = '0' + temp;
        }
        else
        {
            temp -= 9;
            if (temp <= 25)
            {
                key[i] = 'a' + temp;
            }
            else
            {
                temp -= 26;
                key[i] = 'A' + temp;
            }
        }
        continue;
    }
    return key;
}