#include <cstdio>
#include <winsock2.h>

#define KEY_LEN 32
#define MAX_COMPUTER 1001

char *getMAC()
{
    NCB ncb;
    typedef struct _ASTAT_
    {
        ADAPTER_STATUS adapt;
        NAME_BUFFER NameBuff[30];
    } ASTAT, *PASTAT;

    ASTAT Adapter;
    typedef struct _LANA_ENUM
    {
        UCHAR length;
        UCHAR lana[MAX_LANA];
    } LANA_ENUM;
    LANA_ENUM lana_enum;
    UCHAR uRetCode;
    memset(&ncb, 0, sizeof(ncb));
    memset(&lana_enum, 0, sizeof(lana_enum));
    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer = (unsigned char *)&lana_enum;
    ncb.ncb_length = sizeof(LANA_ENUM);
    uRetCode = Netbios(&ncb);
    if (uRetCode != NRC_GOODRET)
    {
        return nullptr;
    }
    for (int lana = 0; lana < lana_enum.length; lana++)
    {
        ncb.ncb_command = NCBRESET;
        ncb.ncb_lana_num = lana_enum.lana[lana];
        uRetCode = Netbios(&ncb);
        if (uRetCode == NRC_GOODRET)
        {
            break;
        }
    }
    if (uRetCode != NRC_GOODRET)
    {
        return nullptr;
    }
    memset(&ncb, 0, sizeof(ncb));
    ncb.ncb_command = NCBASTAT;
    ncb.ncb_lana_num = lana_enum.lana[0];
    UCHAR ncb_callname[NCBNAMSZ];
    strcpy_s((char *)ncb.ncb_callname, sizeof(ncb_callname), "*");
    ncb.ncb_buffer = (unsigned char *)&Adapter;
    ncb.ncb_length = sizeof(Adapter);
    uRetCode = Netbios(&ncb);
    if (uRetCode != NRC_GOODRET)
    {
        return nullptr;
    }
    char *mac = new char[17];
    sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X", Adapter.adapt.adapter_address[0], Adapter.adapt.adapter_address[1],
            Adapter.adapt.adapter_address[2], Adapter.adapt.adapter_address[3], Adapter.adapt.adapter_address[4],
            Adapter.adapt.adapter_address[5]);
    return mac;
}