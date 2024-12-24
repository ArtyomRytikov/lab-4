#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

// ������������� �������
void init_queue(Queue *q)
{
    q->BegQ = q->EndQ = NULL;
}

// ���������� �������� � �������
void add_element(Queue *q, int inf)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        fprintf(stderr, "������ ��� ��������� ������\n");
        exit(1);
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

// �������� �������� �� �������
int del_element(Queue *q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "������: ������� �����\n");
        exit(1);
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

// ��������, ����� �� �������
int is_empty(Queue *q)
{
    return q->BegQ == NULL;
}

// ���������� ������� ������� ������� ������
void selection_sort(Queue *q)
{
    if (is_empty(q) || q->BegQ->link == NULL)
    {
        return; // ������� ����� ��� �������� ���� �������
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

        // ������� ����������� ������� �� �������� �������
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

        // ��������� ����������� ������� � ��������������� �������
        add_element(&sorted, min_node->inf);
    }

    // ��������� ��������������� ������� ������� � ��������
    q->BegQ = sorted.BegQ;
    q->EndQ = sorted.EndQ;
}

// ������ ������� �� ������������ �����
void read_queue(Queue *q)
{
    char input[100];
    printf("������� ������������������ ��������� ����� ������ (��� ���������� ����� ������� Enter): \n");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token != NULL) {
        int value = atoi(token);
        add_element(q, value);
        token = strtok(NULL, " ");
    }
}

// ������ ������� � ����
void write_to_file(Queue *q, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "������ ��� �������� ����� %s\n", filename);
        exit(1);
    }

    fprintf(file, "�������� ������������������: ");
    Node *current = q->BegQ;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->inf);
        current = current->link;
    }
    fprintf(file, "\n");
    selection_sort(q);
    fprintf(file, "��������������� ������������������: ");
    current = q->BegQ;
    while (current != NULL)
    {
        fprintf(file, "%d ", current->inf);
        current = current->link;
    }
    fprintf(file, "\n");
    fclose(file);
}

// ����� ����������� �����
void print_file_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "������ ��� �������� ����� %s\n", filename);
        exit(1);
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);
}
