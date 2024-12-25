#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "queue.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    if (argc != 4 || strcmp(argv[1], "--file") != 0)
    {
        printf("Чтобы ввести и вывести отсортированную последовательность используйте: %s --file <имя_файла> <1|2>\n", argv[0]);
        printf("1 - сортировка методом прямого выбора\n");
        printf("2 - сортировка методом Хоара\n");
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

    return 0;
}
