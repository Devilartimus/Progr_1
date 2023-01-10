/*Дана целочисленная матрица A размера MxN, элементы которой могут принимать значения от 0 до 100.
Найти количество строк матрицы, похожих на первую.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int random(void)    //функция генерации случайного числа от 0 до 101
{
        return (double)(rand())/RAND_MAX*(5);
}
int check(void)     //функция ввода и проверки числа(размера массива)
{
    int size;
    scanf("%d", &size);
    if (size<=0)
    {
        do
        {
            printf("\nIncorrect (Size can't be less then 0). \nRepeat: ");
            scanf("%d", &size);
        } while (size<=0);
    }
    return size;
}
int SizeOfRow(int n, int a[n])       //нахождения мощности (числа всех различных элементов) строки
{
    int sor=1;
    int buf;
    for(int i=0; i<n; i++)  //да будет выборочная сортировка
    {
        int k=i;
        for(int j=i+1; j<n; j++)
        {
            if(a[k] > a[j])
                k = j;
        }
        if(k!=i)
        {
            buf=a[i];
            a[i]=a[k];
            a[k]=buf;
        }
    }
    for (int i=0; i<n-1; i++)
    {
        if (a[i]!=a[i+1])
            sor++;
    }
    return sor;
}
bool SortMasEquals(int n, int a[n], int b[n])       //сортировка и сравнение массива
{
    int minPosition, buf;

    for (int i = 0; i<n; i++)
    {
        minPosition = i;
        for (int j = i + 1; j<n; j++)
        {
            if (a[minPosition] > a[j])
                minPosition = j;
        }
        buf=a[minPosition];
        a[minPosition]=a[i];
        a[i]=buf;
    }
    int m=n;
    for(int i=0; i<m; i++)
    {
       for(int j=i+1; j<=m; j++)
       {
           if(a[i]==a[j])
           {
               for(int k=j; k<=m; k++)
                    a[k]=a[k+1];
               m=m-1;
               j=j-1;
            }
        }
    }

    for (int i = 0; i<n; i++)
    {
        minPosition = i;
        for (int j = i + 1; j<n; j++)
        {
           if (b[minPosition] > b[j])
                minPosition = j;
        }
        buf=b[minPosition];
        b[minPosition]=b[i];
        b[i]=buf;
    }
    m=n;
    for(int i=0; i<m; i++)
    {
       for(int j=i+1; j<=m; j++)
       {
           if(b[i]==b[j])
           {
               for(int k=j; k<=m; k++)
                    b[k]=b[k+1];
               m=m-1;
               j=j-1;
            }
        }
    }
    int count=0;
    for (int i=0; i<n; i++)
    {
        if (a[i]==b[i])
            count++;
    }
    if (count==m)
        return true;
    else
        return false;
}
int similar(int m, int n, int a[m][n])  //функция нахождения строк, похожих на первую
{
    int sim=0;
    for (int i=1; i<m; i++)
    {
       if (SizeOfRow(n, a[0])==SizeOfRow(n, a[i]))
       {
           printf("\nThe number of a similar power row: %d", i+1);
           if (SortMasEquals(n, a[0], a[i])==true)
                sim++;
       }
    }
    return sim;
}
int main()      //ввод размеров матрицы и ее заполнение
{
    srand((unsigned int)time(NULL));
    //ввод размеров матрицы
    printf("Enter size of matrix (MxN): \n");
    printf("M: ");
    int M=check();
    printf("N: ");
    int N=check();
    int a[M][N];        //инициализация матрицы
    printf("Select the input type.\n[1]-automaticelly\n[2]-manually\n");
    int choose;
    scanf("%d", &choose);
    switch (choose)     //выбор типа задания матрицы
    {
    case 1:
        for (int i=0; i<M; i++)     //генерация и вывод матрицы
        {
            for (int j=0; j<N; j++)
            {
                a[i][j]=random();
                printf("%d\t", a[i][j]);
            }
            printf("\n");
        }
        break;
    case 2:
        for (int i=0; i<M; i++)     //ручной ввод матрицы
        {
            for (int j=0; j<N; j++)
            {
                printf("A[%d][%d]: ", i+1, j+1);
                scanf("%d", &a[i][j]);
            }
        }
        break;
    }
    int sim=similar(M, N, a);
    printf("\nThe number of lines similar to the first one: %d", sim);
    return 0;
}
