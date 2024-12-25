#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

// Инициализация очереди
void init_queue(Queue *q)
{
    q->BegQ = q->EndQ = NULL;
}

// Добавление элемента в очередь
void add_element(Queue *q, int inf)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Ошибка при выделении памяти\n");
    }
    new_node->inf = inf;
    new_node->link = NULL;

    if (q->EndQ == NULL)
    {
        q->BegQ = q->EndQ = new_node;
    } else
    {
        q->EndQ->link = new_node;
        q->EndQ = new_node;
    }
}

// Удаление элемента из очереди
int del_element(Queue *q)
{
    if (is_empty(q))
    {
        printf("Ошибка: очередь пуста\n");
    }
    Node *temp = q->BegQ;
    int inf = temp->inf;
    q->BegQ = q->BegQ->link;

    if (q->BegQ == NULL)
    {
        q->EndQ = NULL;
    }

    free(temp);
    return inf;
}

// Проверка, пуста ли очередь
int is_empty(Queue *q)
{
    return q->BegQ == NULL;
}

// Сортировка очереди методом прямого выбора
void selection_sort(Queue *q)
{
    if (is_empty(q) || q->BegQ->link == NULL)
    {
        return; // Очередь пуста или содержит один элемент
    }

    Queue sorted;
    init_queue(&sorted);
    while (!is_empty(q))
    {
        Node *min_node = q->BegQ;
        Node *current = q->BegQ->link;
        while (current != NULL)
        {
            if (current->inf < min_node->inf)
            {
                min_node = current;
            }
            current = current->link;
        }

        // Удаляем минимальный элемент из исходной очереди
        if (min_node == q->BegQ)
        {
            del_element(q);
        }
        else
        {
            Node *prev = q->BegQ;
            while (prev->link != min_node)
            {
                prev = prev->link;
            }
            prev->link = min_node->link;
            if (min_node == q->EndQ)
            {
                q->EndQ = prev;
            }
            free(min_node);
        }

        // Добавляем минимальный элемент в отсортированную очередь
        add_element(&sorted, min_node->inf);
    }

    // Переносим отсортированную очередь обратно в исходную
    q->BegQ = sorted.BegQ;
    q->EndQ = sorted.EndQ;
}

// Чтение очереди из стандартного ввода
void read_queue(Queue *q)
{
    char input[100];
    printf("Введите последовательность элементов через пробел (для завершения ввода нажмите Enter): \n");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token != NULL) {
        int value = atoi(token);
        add_element(q, value);
        token = strtok(NULL, " ");
    }
}

// Запись очереди в файл
void write_to_file(Queue *q, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Ошибка при открытии файла %s\n", filename);
    }

    fprintf(file, "Исходная последовательность: ");
    Node *current = q->BegQ;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->inf);
        current = current->link;
    }
    fprintf(file, "\n");
    selection_sort(q);
    fprintf(file, "Отсортированная последовательность: ");
    current = q->BegQ;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->inf);
        current = current->link;
    }
    fprintf(file, "\n");
    fclose(file);
}

// Вывод содержимого файла
void print_file_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Ошибка при открытии файла %s\n", filename);
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);
}
// Сортировка очереди методом Хоара
void quick_sort(Queue *q)
{
    if (is_empty(q) || q->BegQ->link == NULL)
    {
        return; // Очередь пуста или содержит один элемент
    }

    Queue less, equal, greater;
    init_queue(&less);
    init_queue(&equal);
    init_queue(&greater);

    Node *pivot = q->BegQ;
    int pivot_value = pivot->inf;

    while (!is_empty(q))
    {
        int value = del_element(q);
        if (value < pivot_value)
        {
            add_element(&less, value);
        }
        else if (value == pivot_value)
        {
            add_element(&equal, value);
        }
        else
        {
            add_element(&greater, value);
        }
    }

    quick_sort(&less);
    quick_sort(&greater);

    // Переносим отсортированные очереди обратно в исходную
    while (!is_empty(&less))
    {
        add_element(q, del_element(&less));
    }
    while (!is_empty(&equal))
    {
        add_element(q, del_element(&equal));
    }
    while (!is_empty(&greater))
    {
        add_element(q, del_element(&greater));
    }
}
// Выбор сортировки
void sort_queue(Queue *q, int sort_method)
{
    if (sort_method == 1)
    {
        selection_sort(q);
    }
    else if (sort_method == 2)
    {
        quick_sort(q);
    }
    else
    {
        printf("Неверный метод сортировки. Используйте 1 для сортировки методом прямого выбора или 2 для сортировки методом Хоара.\n");
    }
}
