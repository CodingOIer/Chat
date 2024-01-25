#include "head/key.h"
#include "head/mac.h"
#include "head/netcom.h"

#include <cstdio>
#include <cstring>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>

#define MAX_COMPUTER 1001

std::mt19937 rnd(std::random_device{}());

std::unordered_map<std::string, int> link;

char *key[MAX_COMPUTER];

bool checkConnectWanted(const char *s)
{
    for (int i = 2; i < 17; i++)
    {
        if (s[i] != '-')
        {
            return false;
        }
    }
    return true;
}

std::tuple<char *, char *, char *> split(const char *s)
{
    char *temp1 = new char[105];
    char *temp2 = new char[105];
    char *temp3 = new char[105];
}

void reply()
{
    char temp[1005];
    char out_temp[1005];
    char key_temp[1005];
    for (;;)
    {
        strcpy(temp, net::Listen(7000));
        if (temp[17] != '#' || !checkConnectWanted(temp))
        {
            continue;
        }
        strcpy(key_temp, makeKey());
        sprintf(out_temp, "200#%s", key_temp);
    }
}

int main()
{

    return 0;
}