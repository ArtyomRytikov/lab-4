#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "queue.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    if (argc != 3 || strcmp(argv[1], "--file") != 0)
    {
        fprintf(stderr, "Чтобы ввести и вывести отсортированную последовательность используйте: %s --file <имя_файла>\n", argv[0]);
        return 0;
    }

    const char *filename = argv[2];
    Queue q;
    init_queue(&q);
    read_queue(&q);
    write_to_file(&q, filename);
    print_file_content(filename);

    return 0;
}
