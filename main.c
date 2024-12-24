#include <stdio.h>
#include <locale.h>
#include "queue.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    Queue q;
    init_queue(&q);  // Инициализация очереди

    // Чтение последовательности чисел от пользователя
    read_queue(&q);

    // Запись исходной и отсортированной очереди в файл
    write_to_file(&q, "file.txt");

    return 0;
}
