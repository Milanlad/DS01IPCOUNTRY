#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXCHAR 1000
char ip_from_convert[99];
char ip_to_convert[99];
char country_convert[99];

int main (int agrc, char *argv[])
{
long int ip_0 =0;
long int ip_1 =0;
long int ip_2 =0;
long int ip_3 =0;
long int ip_decimal = 0; // l'ip stocker sous un seul entier de 4 octets au lieu de 4 entier de 1 octets
sscanf(argv[1],"%ld.%ld.%ld.%ld",&ip_0,&ip_1,&ip_2,&ip_3);
ip_0= ip_0 * 256 * 256 * 256;
ip_1= ip_1 * 256 * 256;
ip_2= ip_2 * 256;
ip_3= ip_3;
ip_decimal = ip_0 + ip_1 + ip_2 + ip_3;
FILE *fp;
char Ligne[MAXCHAR];
char *Sortie;
fp = fopen("geoip.csv","r");
int member = 0;
int long ip_from = 0;
int long ip_to = 0;
while (feof(fp) != true)
    {
    fgets(Ligne, MAXCHAR, fp);
    Sortie = strtok(Ligne, ",");

    while(Sortie != NULL)
        {

        if (member == 0)    // on passe dans ce if 2 fois par ligne et l'orsque l'on est sur le premier argument et 2eme argument de la ligne soit l'ip from et l'ip to
            {
            int i = 1;

            while (Sortie[i] != '"')
                {
                ip_from_convert[i-1]=Sortie[i];
                i++;
                }
            ip_from = atol(ip_from_convert);
            }

        if(member == 1)
            {
            int i = 1;
            while (Sortie[i] != '"')
                {
                ip_to_convert[i-1]=Sortie[i];
                i++;
                }
            ip_to = atol(ip_to_convert);
            }

        if(member == 2)
            {
            int i = 1;
            while (Sortie[i] != '"')
                {
                country_convert[i-1]=Sortie[i];
                i++;
                }
            }
        Sortie = strtok(NULL, ",");
        member ++;
        }

    if (ip_decimal >= ip_from && ip_decimal <= ip_to)
        {
        printf("Le pays est : %s\n",country_convert);
        return 0;
        }
    memset(ip_from_convert,0,99);
    memset(ip_to_convert,0,99);
    ip_from = 0;
    ip_to = 0;
    member = 0;
    }
return 0;
}