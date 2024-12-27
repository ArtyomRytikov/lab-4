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
        printf("�������������:\n");
        printf("1. ��� ��������� �������� ����������: %s --compare <������_������> \n", argv[0]);
        printf("2. ��� ���������� � ������ � ����: %s --file <���_�����> <1|2>\n", argv[0]);
        printf("1 - ���������� ������� ������� ������\n");
        printf("2 - ���������� ������� �����\n");
        return 0;
    }

    if (strcmp(argv[1], "--compare") == 0)
    {
        if (argc != 3)
        {
            printf("��� ��������� �������� ���������� �����������: %s --compare <������_������> \n", argv[0]);
            return 0;
        }

        int max_size = atoi(argv[2]);
        compare_sorting_performance(max_size);
    }
    else if (strcmp(argv[1], "--file") == 0)
    {
        if (argc != 4)
        {
            printf("��� ���������� � ������ � ���� �����������: %s --file <���_�����> <1|2>\n", argv[0]);
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
        printf("�������� ��������. ����������� --compare ��� ��������� �������� ���������� ��� --file ��� ���������� � ������ � ����.\n");
        return 0;
    }

    return 0;
}
