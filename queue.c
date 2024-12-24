#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_queue(Queue *q)
{
    q->BegQ = q->EndQ = NULL;
}
void add_element(Queue *q, int inf)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->inf = inf;
    new_node->link = NULL;

    if (q->EndQ == NULL)
    {
        q->BegQ = q->EndQ = new_node;
    }
    else
    {
        q->EndQ->link = new_node;
        q->EndQ = new_node;
    }
}

int del_element(Queue *q)
{
    Node *temp = q->BegQ;
    int inf = temp->inf;
    q->BegQ = q->BegQ->link;

    if (q->BegQ == NULL) {
        q->EndQ = NULL;
    }

    free(temp);
    return inf;
}

int is_empty(Queue *q)
{
    return q->BegQ == NULL;
}

void selection_sort(Queue *q)
{
    if (is_empty(q) || q->BegQ->link == NULL)
    {
        return; // ������� ����� ��� �������� ���� �������
    }

    Queue sorted;
    init_queue(&sorted);
    for (int i = 0; !is_empty(q); i++)
    {
        int min_value = del_element(q);
        Node *min_node = NULL;
        Queue temp;
        init_queue(&temp);
        for (int j = 0; !is_empty(q); j++)
        {
            int current_value = del_element(q);
            if (current_value < min_value)
            {
                add_element(&temp, min_value);
                min_value = current_value;
            }
            else
            {
                add_element(&temp, current_value);
            }
        }
        add_element(&sorted, min_value);
        for (int k = 0; !is_empty(&temp); k++)
        {
            int inf = del_element(&temp);
            add_element(q, inf);
        }
    }

    // ��������� �������� �� ��������������� ������� ������� � ��������
    for (int i = 0; !is_empty(&sorted); i++)
    {
        int inf = del_element(&sorted);
        add_element(q, inf);
    }
}
void read_queue(Queue *q)
{
    char input[256];
    printf("������� ������������������ ����� ����� ������ (��� ���������� ����� ������� Enter):\n");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "������ ��� ������ �����\n");
        return;
    }

    char *token = strtok(input, " \n");
    while (token != NULL)
    {
        int inf = atoi(token);
        add_element(q, inf);
        token = strtok(NULL, " \n");
    }
}

void write_to_file(Queue *q, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "������ ��� �������� ����� %s\n", filename);
        return;
    }
    // ������ �������� �������
    fprintf(file, "�������� ������������������: ");
    Queue temp;
    init_queue(&temp);

    while (!is_empty(q)) {
        int inf = del_element(q);
        fprintf(file, "%d ", inf);
        add_element(&temp, inf);
    }

    // ���������� �������� ������� � �������� �������
    while (!is_empty(&temp)) {
        int inf = del_element(&temp);
        add_element(q, inf);
    }

    // ���������� �������
    selection_sort(q);

    // ������ ��������������� �������
    fprintf(file, "\n��������������� ������������������: ");
    while (!is_empty(q)) {
        int inf = del_element(q);
        fprintf(file, "%d ", inf);
        add_element(&temp, inf);
    }

    // ���������� �������� ������� � �������� �������
    while (!is_empty(&temp))
    {
        int inf = del_element(&temp);
        add_element(q, inf);
    }

    fclose(file);
}
