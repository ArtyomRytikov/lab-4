#include <stdio.h>
#include <locale.h>
#include "queue.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    Queue q;
    init_queue(&q);  // ������������� �������

    // ������ ������������������ ����� �� ������������
    read_queue(&q);

    // ������ �������� � ��������������� ������� � ����
    write_to_file(&q, "file.txt");

    return 0;
}
