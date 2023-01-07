#ifndef MY_HEAD
#define MY_HEAD
#include<bits/stdc++.h>
//选择排序
void selective_sort_double(double *arr, int length)
{
    int t = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}
void selective_sort_int(int *arr, int length)
{
    int t = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}
//冒泡排序
void bubble_sort_double(int *a, int n)
{
    int k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                k = a[j];
                a[j] = a[j + 1];
                a[j + 1] = k;
            }
        }
    }
}

void bubble_sort_int(int *a, int n)
{
    int k = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                k = a[j];
                a[j] = a[j + 1];
                a[j + 1] = k;
            }
        }
    }
}

void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void swap_double(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

// int add_int(int a, int b)
// {
// 	return a + b;
// }

// int sub_int(int a, int b)
// {
// 	return a - b;
// }

// int calc_int(int (*fp)(int, int), int a, int b)//����ָ����Ϊ����
// {
// 	return (*fp)(a, b);
// }

// int (*select_int(char op))(int, int)//���غ���ָ��
// {
// 	switch (op)
// 	{
// 	case '+':
// 		return add;
// 		break;
// 	case '-':
// 		return sub;
// 		break;
// 	}
// }

typedef struct Node {//单向 链表数据结构
	int a;
	struct Node *next;
} node;

int insert_node(node *head, int a, int i) //插入结点
{
	node *p1, *p2;
	p1 = p2 = head;
	int j = 1;
	while (p1->next && j < i - 1)
	{
		p1 = p1->next;
		j++;
	}
	if (!p1->next || j > i)
	{
		printf("insert error");
		system("pause");
		return 0;
	}
	if (i == 1) // �жϲ�����Ƿ��һ��
	{
		p1 = (node *)malloc(sizeof(node));
		p1->a = a;
		p1->next = p2;
		head = p1;
		printf("insert ok");
		system("pause");
		return 1;
	}
	else
	{
		p2 = (node *)malloc(sizeof(node));
		p2->a = a;
		p2->next = p1->next;
		p1->next = p2;
		printf("insert ok");
		system("pause");
		return 1;
	}
}

int delete_node_oder(node **head, int i) // 通过序号来删除结点
{
	if (i <= 0)
	{
		printf("invalid");
		return 0;
	}
	node *p1, *p2;
	p1 = p2 = *head;
	if (head == NULL)
	{
		printf("empty");
		return 0;
	}
	int j = 1;
	if (i == 1)
	{
		*head = p1->next;
		free(p1);
		printf("delete ok");
		return 1;
	}
	else
	{
		while (!p1->next && j < i - 1)
		{
			p1 = p1->next;
			j++;
			if (p1->next == NULL)
			{
				printf("delete error");
				system("pause");
				return 0;
			}
		}
		if (!p1->next || j > i - 1)
		{
			printf("delete error");
			system("pause");
			return 0;
		}
		p2 = p1;
		p1 = p1->next;
		if (p1->next != NULL)
		{
			p2->next = p1->next;
			free(p1);
		}
		else
		{
			free(p1);
			p2->next = NULL;
		}
	}
	printf("delete ok");
	system("pause");
	return 1;
}

int delete_node_number(node **head, int a) // ͨ通过数值来删除链表的结点
{
	node *p1, *p2;
	p1 = p2 = *head;
	if (head == NULL)
	{
		printf("empty");
		return 0;
	}
	if ((*head)->a == a)
	{
		*head = (*head)->next;
		free(p1);
		return 1;
	}
	while (p1->next != NULL && p1->a != a)
	{
		p1 = p1->next;
		if (p1->next == NULL && p1->a == a)
		{
			break;
		}
		if (p1->next == NULL && p1->a != a)
		{
			printf("delete error,no such data");
			system("pause");
			return 0;
		}
	}
	if (p1->next == NULL && p1->a != a)
	{
		printf("delete error");
		system("pause");
		return 0;
	}
	else
	{
		while (p2->next != p1)
			p2 = p2->next;
		p2->next = p1->next;
		free(p1);
	}
	printf("delete ok");
	system("pause");
	return 1;
}

int change_value(node *head, int i, int new_value) // 改变链表节点的值
	node *p1, *p2;
	p1 = p2 = head;
	int j = 1;
	while (p1->next && j < i)
	{
		p1 = p1->next;
		j++;
	}
	if (!p1->next || j > i)
	{
		printf("change error");
		system("pause");
		return 0;
	}
	p1->a = new_value;
	printf("change ok");
	system("pause");
	return 1;
}

int isPrime(int x)//判断素数
{
    int is = 1;
    for (int i = 2; i < sqrt((double)x);i++)
    {
        if(x%i==0)
        {
            return 0;
        }
    }
    return is;
}
void convert_string(char p[])//反转字符串
{
    int l = strlen(p);
    char tamp;
    for (int i = 0, j = l - 1; i < l/2; i++, j--)
    {
        tamp = p[i];
        p[i] = p[j];
        p[j] = tamp;
    }
    p[l + 1] = '\0';
}
#endif