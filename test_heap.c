#include <stdio.h>

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return;
}

//堆为tree，有n个节点，i为从i个节点机型heapify操作
void heapify(int tree[], int n, int i)
{
    if(i >= n)
    {
        return;
    }
    int c1 = 2 * i + 1;
    int c2 = 2 * i + 2;
    int max = i;

    //找出父节点和两个子节点的最大值
    if(c1 < n && tree[c1] > tree[i])
    {
        max = c1;
    }
    if(c2 < n && tree[c2] > tree[max])
    {
        max = c2;
    }

    if(max != i)
    {
        swap(tree, max, i);
        heapify(tree, n, max);
    }
}

void build_heap(int tree[], int n)
{
    int last_node = n - 1;
    int parent = (last_node - 1) / 2;
    int i;
    for (i = parent; i >= 0; i--)
    {
        heapify(tree, n, i);
    }
}
int main()
{
    int tree[] = {4, 10, 3, 5, 1, 2};
    int n = 6;
    build_heap(tree, n);
    //heapify(tree, n, 0);
    int i = 0;
    for(i = 0; i < n; i++)
    {
        printf("%d\n", tree[i]);
    }
    return 0;
}
