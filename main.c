/*Ђорђе Јовић РА 41-2022

Направити модул који представља једноструко спрегнуту листу.
Модул извести као динамичку библиотеку.
Ослањајући се на тај модул направити модул који симулира динамичко заузимање меморије.
Свака слободна меморијска зона представљена је адресом свог почетка и свог краја.
На почетку извршавања постоји само једна велика слободна зона,
док се процесом заузимања и ослобађања меморије врши њено парчање и спајање.
Омогућити кориснику да одабере адресу са које жели да заузме меморију,
као и количину меморије коју жели да заузме.

компајлирање кода:
gcc -shared -fPIC mem.c -L. -llist -o libmem.so
gcc -shared -fPIC list.c -o liblist.so
gcc main.c -L. -lmem -llist -o program

Покретање кода:
./program

МИСРА Ц ствари које су испоштоване:
-провера NULL показивача
-#define уместо магичних бројева
-не користи се while(1) него контролна променљива
-експлицитне гране кода
-додаванје const где је то могуће

МИСРА Ц ствари које нису испоштоване:
-употреба malloca и free
-scanf
-енум типови за стања

*/

#include <stdio.h>
#include "mem.h"

#define MEM_SIZE 1024U

int main(void)
{
    Node* mem = mem_init(MEM_SIZE);
    int option = 0;
    int run = 1;

    if (mem == NULL)
    {
        printf("Greska: memorija nije inicijalizovana.\n");
        return 1;
    }

    while (run==1)
    {
        printf("\n1. Prikazi slobodne blokove\n");
        printf("2. Alociraj memoriju\n");
        printf("3. Oslobodi memoriju\n");
        printf("4. Izlaz\n");
        printf("Izbor: ");

        if (scanf("%d", &option) != 1)
        {
            printf("Nevalidan unos.\n");
            return 1;
        }

        if (option == 1)
        {
            list_print(mem);
        }
        else if (option == 2)
        {
            size_t addr = 0U;
            size_t size = 0U;

            printf("Unesi adresu: ");
            (void)scanf("%lu", (unsigned long*)&addr);
            printf("Unesi velicinu: ");
            (void)scanf("%lu", (unsigned long*)&size);

            mem = mem_alloc(mem, addr, size);
        }
        else if (option == 3)
        {
            size_t addr = 0U;
            size_t size = 0U;

            printf("Unesi pocetnu adresu: ");
            (void)scanf("%lu", (unsigned long*)&addr);
            printf("Unesi velicinu: ");
            (void)scanf("%lu", (unsigned long*)&size);

            mem = mem_free(mem, addr, size);
        }
        else if (option == 4)
        {
            run=0;
        }
        else
        {
            printf("Nepostojeca opcija.\n");
        }
    }

    list_free(mem);
    return 0;
}
