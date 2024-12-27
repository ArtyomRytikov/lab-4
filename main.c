#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "queue.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");

    if (argc < 2)
    {
        printf("Использование:\n");
        printf("1. Для сравнения скорости сортировок: %s --compare <размер_списка> \n", argv[0]);
        printf("2. Для сортировки и записи в файл: %s --file <имя_файла> <1|2>\n", argv[0]);
        printf("1 - сортировка методом прямого выбора\n");
        printf("2 - сортировка методом Хоара\n");
        return 0;
    }

    if (strcmp(argv[1], "--compare") == 0)
    {
        if (argc != 3)
        {
            printf("Для сравнения скорости сортировок используйте: %s --compare <размер_списка> \n", argv[0]);
            return 0;
        }

        int max_size = atoi(argv[2]);
        compare_sorting_performance(max_size);
    }
    else if (strcmp(argv[1], "--file") == 0)
    {
        if (argc != 4)
        {
            printf("Для сортировки и записи в файл используйте: %s --file <имя_файла> <1|2>\n", argv[0]);
            return 0;
        }

        const char *filename = argv[2];
        int sort_method = atoi(argv[3]);

        Queue q;
        init_queue(&q);
        read_queue(&q);
        write_to_file(&q, filename);
        sort_queue(&q, sort_method);
        print_file_content(filename);
    }
    else
    {
        printf("Неверный аргумент. Используйте --compare для сравнения скорости сортировок или --file для сортировки и записи в файл.\n");
        return 0;
    }

    return 0;
}
