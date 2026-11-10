#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>

#define MAX_SIZE 20 // дл€ лабы правки
#define MAX_LEN  256
/// вторые правки

//  Ћ– 8.1  Ч  fscanf / fprintf  (числова€ информаци€)


// 8.1.1 Ч создать текстовый файл с информацией о студенте
void task_8_1_1(void)
{
    // "wt" Ч write text: создает файл или перезаписывает существующий
    FILE* f = fopen("output0.txt", "wt");  //открытие файла дл€ работы
    if (!f)
    {
        printf("ERROR!\n");
        return;
    }

    fprintf(f, " оновалова ѕолина\n»—Ёбд-11");
    fclose(f);

    printf("SUCCESS! output0.txt created\n");
}

// 8.1.2 Ч прочитать 3 числа, записать максимум
void task_8_1_2(void)
{
    FILE* fin = fopen("in2.txt", "rt");
    if (!fin)
    {
        printf("in2.txt not found\n");
        return;
    }

    int a, b, c;
    if (fscanf(fin, "%d%d%d", &a, &b, &c) != 3)  // fscanf возвращает число успешно прочитанных переменных.
    {
        printf("Bad input\n");
        fclose(fin);
        return;
    }
    fclose(fin);

    int max = a;
    if (b > max)
    {
        max = b;
    }
    if (c > max)
    {
        max = c;
    }

    FILE* fout = fopen("out2.txt", "wt");
    if (!fout)
    {
        printf("Cannot create out2.txt\n");
        return;
    }

    fprintf(fout, "%d", max);
    fclose(fout);

    printf("Max = %d -> out2.txt\n", max);
}

// 8.1.3 Ч сохранение / загрузка массива (формат: N, потом N чисел)
int saveArray(const char* filename, int arr[], int n)
{
    FILE* f = fopen(filename, "wt");
    if (!f)
    {
        return 0;
    }

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; ++i)
    {
        fprintf(f, "%d ", arr[i]);
    }
    fclose(f);

    return 1;
}

int loadArray(const char* filename, int arr[], int maxSize)
{
    FILE* f = fopen(filename, "rt");
    if (!f)
    {
        return -1;
    }

    int n = 0;
    if (fscanf(f, "%d", &n) != 1 || n < 0 || n > maxSize)
    {
        fclose(f);
        return -1;
    }

    for (int i = 0; i < n; ++i)
    {
        if (fscanf(f, "%d", &arr[i]) != 1)
        {
            fclose(f);
            return -1;
        }
    }
    fclose(f);

    return n;
}

void task_8_1_3(void)
{
    int arr[MAX_SIZE] = { 1, 2, 4, 6, 7, 8 };
    int n = 6;

    if (!saveArray("state.txt", arr, n))
    {
        printf("Save failed\n");
        return;
    }
    printf("Saved %d elements -> state.txt\n", n);

    int arr2[MAX_SIZE];
    int n2 = loadArray("state.txt", arr2, MAX_SIZE);
    if (n2 < 0)
    {
        printf("Load failed\n");
        return;
    }

    printf("Loaded %d elements: ", n2);
    for (int i = 0; i < n2; ++i)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");
}

// 8.1.4 Ч загрузка, обработка, вывод, сохранение 
void task_8_1_4(void)
{
    FILE* fin = fopen("in0.txt", "rt");
    if (!fin)
    {
        printf("in0.txt not found\n");
        return;
    }

    int n = 0;
    if (fscanf(fin, "%d", &n) != 1 || n < 0 || n > MAX_SIZE)
    {
        printf("Bad n\n");
        fclose(fin);
        return;
    }

    int A[MAX_SIZE];
    for (int i = 0; i < n; ++i)
    {
        if (fscanf(fin, "%d", &A[i]) != 1)
        {
            printf("Bad element #%d\n", i);
            fclose(fin);
            return;
        }
    }
    fclose(fin);

    printf("Loaded A[%d]: ", n);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    int firstEven = -1;
    int lastEven = -1;
    for (int i = 0; i < n; ++i)
    {
        if (A[i] % 2 == 0)
        {
            if (firstEven == -1)
            {
                firstEven = i;
            }
            lastEven = i;
        }
    }

    if (firstEven != -1 && firstEven != lastEven)
    {
        for (int i = firstEven + 1; i < lastEven; ++i)
        {
            if (A[i] % 2 == 0)
            {
                A[i] += 100;
            }
        }
    }

    printf("Processed A[%d]: ", n);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", A[i]);
    }
    printf("\n");

    FILE* fout = fopen("out0.txt", "wt");
    if (!fout)
    {
        printf("Cannot create out0.txt\n");
        return;
    }

    fprintf(fout, "%d\n", n);
    for (int i = 0; i < n; ++i)
    {
        fprintf(fout, "%d ", A[i]);
    }
    fclose(fout);

    printf("Saved -> out0.txt\n");
}


//  Ћ– 8.2  Ч  fgets  (построчна€ обработка)


// 8.2.1 Ч заменить \t на '%'
void task_8_2_1(void)
{
    char s[MAX_LEN];

    FILE* fin = fopen("text1.txt", "rt");
    if (!fin)
    {
        printf("text1.txt not found\n");
        return;
    }

    FILE* fout = fopen("out1.txt", "wt");
    if (!fout)
    {
        printf("Cannot create out1.txt\n");
        fclose(fin);
        return;
    }

    while (fgets(s, MAX_LEN, fin) != NULL)
    {
        for (int i = 0; s[i] != '\0'; ++i)
        {
            if (s[i] == '\t')
            {
                s[i] = '%';
            }
        }
        fprintf(fout, "%s", s);
    }

    fclose(fin);
    fclose(fout);

    printf("Done -> out1.txt\n");
}

// 8.2.2 Ч все латинские в UPPER
void task_8_2_2(void)
{
    char s[MAX_LEN];

    FILE* fin = fopen("text2.txt", "rt");
    if (!fin)
    {
        printf("text2.txt not found\n");
        return;
    }

    FILE* fout = fopen("out2.txt", "wt");
    if (!fout)
    {
        printf("Cannot create out2.txt\n");
        fclose(fin);
        return;
    }

    while (fgets(s, MAX_LEN, fin) != NULL)
    {
        for (int i = 0; s[i] != '\0'; ++i)
        {
            s[i] = (char)toupper((unsigned char)s[i]);
        }
        fprintf(fout, "%s", s);
    }

    fclose(fin);
    fclose(fout);

    printf("Done -> out2.txt\n");
}

// 8.2.3* Ч '#' в начале строки, если в строке есть латинска€ буква
void task_8_2_3(void)
{
    char s[MAX_LEN];

    FILE* fin = fopen("text3.txt", "rt");
    if (!fin)
    {
        printf("text3.txt not found\n");
        return;
    }

    FILE* fout = fopen("out3.txt", "wt");
    if (!fout)
    {
        printf("Cannot create out3.txt\n");
        fclose(fin);
        return;
    }

    while (fgets(s, MAX_LEN, fin) != NULL)
    {
        int hasLatin = 0;
        for (int i = 0; s[i] != '\0'; ++i)
        {
            unsigned char c = (unsigned char)s[i];
            if (c < 128 && isalpha(c))
            {
                hasLatin = 1;
                break;
            }
        }

        if (hasLatin)
        {
            fprintf(fout, "#");
        }
        fprintf(fout, "%s", s);
    }

    fclose(fin);
    fclose(fout);

    printf("Done -> out3.txt\n");
}


//  Ћ– 8.3  Ч  getc  (посимвольна€ обработка, HTML)

// 8.3.1 Ч обернуть текст в HTML, \n -> <br>
void task_8_3_1(void)
{
    FILE* fin = fopen("text1.txt", "rt");
    if (!fin)
    {
        printf("text1.txt not found\n");
        return;
    }

    FILE* fout = fopen("text1_out.html", "wt");
    if (!fout)
    {
        printf("Cannot create html\n");
        fclose(fin);
        return;
    }

    fprintf(fout, "<!DOCTYPE html>");
    fprintf(fout, "<html>");
    fprintf(fout, "<head>");
    fprintf(fout, "<meta charset=\"utf-8\" />");
    fprintf(fout, "<title>HTML Document</title>");
    fprintf(fout, "</head>");
    fprintf(fout, "<body>");

    int ch;
    while ((ch = getc(fin)) != EOF)
    {
        fprintf(fout, "%c", ch);
        if (ch == '\n')
        {
            fprintf(fout, "<br>");
        }
    }

    fprintf(fout, "</body>");
    fprintf(fout, "</html>");

    fclose(fin);
    fclose(fout);

    printf("Done -> text1_out.html\n");
}

// 8.3.2 Ч HTML с <b>/<i> (пример: вариант 1)
int isLetterMy(unsigned char ch)
{
    if (ch < 128)
    {
        return isalpha(ch) ? 1 : 0;
    }
    if (ch >= 192 && ch <= 255)
    {
        return 1;
    }
    if (ch == 168 || ch == 184)
    {
        return 1;
    }
    return 0;
}

int isCat1(const char* w)
{
    int len = (int)strlen(w);
    if (len < 2)
    {
        return 0;
    }
    if (!(w[0] >= 'A' && w[0] <= 'Z'))
    {
        return 0;
    }
    for (int i = 1; i < len; ++i)
    {
        if (!(w[i] >= 'a' && w[i] <= 'z'))
        {
            return 0;
        }
    }
    return 1;
}

int isCat2(const char* w)
{
    int len = (int)strlen(w);
    if (len == 0)
    {
        return 0;
    }
    for (int i = 0; i < len; ++i)
    {
        if (!(w[i] >= 'a' && w[i] <= 'z'))
        {
            return 0;
        }
    }
    return 1;
}

void task_8_3_2(void)
{
    FILE* fin = fopen("text2.txt", "rt");
    if (!fin)
    {
        printf("text2.txt not found\n");
        return;
    }

    FILE* fout = fopen("text2.html", "wt");
    if (!fout)
    {
        printf("Cannot create html\n");
        fclose(fin);
        return;
    }

    fprintf(fout, "<!DOCTYPE html>");
    fprintf(fout, "<html>");
    fprintf(fout, "<head>");
    fprintf(fout, "<meta charset=\"utf-8\" />");
    fprintf(fout, "<title>HTML</title>");
    fprintf(fout, "</head>");
    fprintf(fout, "<body>");

    char word[128];
    int wlen = 0;
    int ch;

    while ((ch = getc(fin)) != EOF)
    {
        if (isLetterMy((unsigned char)ch))
        {
            if (wlen < 127)
            {
                word[wlen++] = (char)ch;
            }
        }
        else
        {
            if (wlen > 0)
            {
                word[wlen] = '\0';
                if (isCat1(word))
                {
                    fprintf(fout, "<b>%s</b>", word);
                }
                else if (isCat2(word))
                {
                    fprintf(fout, "<i>%s</i>", word);
                }
                else
                {
                    fprintf(fout, "%s", word);
                }
                wlen = 0;
            }

            if (ch == '<')
            {
                fprintf(fout, "&lt;");
            }
            else if (ch == '>')
            {
                fprintf(fout, "&gt;");
            }
            else if (ch == '&')
            {
                fprintf(fout, "&amp;");
            }
            else if (ch == '\n')
            {
                fprintf(fout, "<br>\n");
            }
            else
            {
                fprintf(fout, "%c", ch);
            }
        }
    }

    if (wlen > 0)
    {
        word[wlen] = '\0';
        if (isCat1(word))
        {
            fprintf(fout, "<b>%s</b>", word);
        }
        else if (isCat2(word))
        {
            fprintf(fout, "<i>%s</i>", word);
        }
        else
        {
            fprintf(fout, "%s", word);
        }
    }

    fprintf(fout, "</body>");
    fprintf(fout, "</html>");

    fclose(fin);
    fclose(fout);

    printf("Done -> text2.html\n");
}

// задачи

void printMenu(void)
{
    printf("\nЋабораторна€ работа #8\n");
    printf("1  - 8.1.1  output0.txt (студент)\n");
    printf("2  - 8.1.2  max из 3 (in2.txt -> out2.txt)\n");
    printf("3  - 8.1.3  save/load (state.txt)\n");
    printf("4  - 8.1.4  обработка (in0.txt -> out0.txt)\n");
    printf("5  - 8.2.1  \\t -> %% (text1.txt -> out1.txt)\n");
    printf("6  - 8.2.2  UPPER (text2.txt -> out2.txt)\n");
    printf("7  - 8.2.3  '#' если латиница (text3.txt -> out3.txt)\n");
    printf("8  - 8.3.1  HTML (text1.txt -> text1_out.html)\n");
    printf("9  - 8.3.2  HTML <b>/<i> (text2.txt -> text2.html)\n");
    printf("0  - выход\n");
    printf("¬ыбор: ");
}

int main(void)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice = 0;
    do
    {
        printMenu();
        if (scanf("%d", &choice) != 1)
        {
            choice = -1;
        }
        while (getchar() != '\n')
        {
        }

        switch (choice)
        {
        case 1:
            task_8_1_1();
            break;
        case 2:
            task_8_1_2();
            break;
        case 3:
            task_8_1_3();
            break;
        case 4:
            task_8_1_4();
            break;
        case 5:
            task_8_2_1();
            break;
        case 6:
            task_8_2_2();
            break;
        case 7:
            task_8_2_3();
            break;
        case 8:
            task_8_3_1();
            break;
        case 9:
            task_8_3_2();
            break;
        case 0:
            printf("Bye\n");
            break;
        default:
            printf("Ќет такой задачи: %d\n", choice);
            break;
        }
    } while (choice != 0);

    return 0;
}