/*
 * @author topcue
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define YES		1
#define NO		0
#define NUM	5
typedef int (*order)(int, int);
typedef struct {
	int*   a;
	int   size;
} Array;
void show_Array(Array* X)
{
	int i;
	int size = (*X).size;
	for (i = 0; i < size; i++)
		printf("%3d", *((*X).a + i));
	printf("\n");
}
void gen_Array(Array* src, int size)
{
	src->size = size;
	src->a = NULL;
	src->a = (int*)malloc(sizeof(int) * size);
	int i;
	for (i = 0; i < size; i++)
		src->a[i] = 0;
}
void set_rand_Array(Array* src, int size)
{
	int i;
	for (i = 0; i < size; i++)
		src->a[i] = rand() % NUM;
}
void swap(int*a, int*b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void Copy_Array(Array* dst, Array* src, int side)
{
	int i;
	if (side == YES)
	{
		for (i = 0; i < dst->size; i++)
			dst->a[i] = src->a[i];
	}
	else
	{
		for (i = 0; i < dst->size; i++)
			dst->a[i] = src->a[(src->size >> 1)+ i];
	}
}
void shuffle_Array_Fisher(Array* X)
{
	int i, R;
	int size = X->size;
	for (i = size - 1; i > 1; i--)
	{
		R = rand() % (i + 1);
		swap(&X->a[R], &X->a[i]);
	}
}
int inc(int a, int b)
{
	if (a < b)
		return YES;
	return NO;
}
int dec(int a, int b)
{
	return !inc(a, b);
}
int Partition(Array* X, int low, int high, order order_type)
{
	int i = low - 1, j;
	int pivot = X->a[high];
	for (j = low; j <= high - 1; j++)
	{
		if (order_type(X->a[j], pivot) == YES)
		{
			i++;
			swap(&X->a[i], &X->a[j]);
		}
	}
	swap(&X->a[i + 1], &X->a[high]);
	return i + 1;
}
int Partition_low(Array* A, int low, int high, order order_type)
{
	int pivot = 0;
	pivot = (*A).a[low];
	int i = 0;
	i = high + 1;
	int j;
	for (j = high; j >= low + 1; j--)
	{
		if (order_type((*A).a[j], pivot) == YES)
		{
			i--;
			swap(&(*A).a[i], &(*A).a[j]);
		}
	}
	swap(&(*A).a[i - 1], &(*A).a[low]);
	return i - 1;
} // pivot : low
void Quicksort(Array* X, int low, int high, order order_type)
{
	int m;
	if (low < high)
	{
		m = Partition(X, low, high, order_type);
		Quicksort(X, low, m - 1, order_type);
		Quicksort(X, m + 1, high, order_type);
	}
}
void Merge(Array* X, Array* L, Array* R, order order_type)
{
	int i = 0, j = 0, k = 0;
	while (i < L->size && j < R->size)
	{
		if (order_type(L->a[i], R->a[j]) == YES)
		{
			X->a[k] = L->a[i];
			k++, i++;
		}
		else
		{
			X->a[k] = R->a[j];
			k++, j++;
		}
	}
	while (i < L->size)
		X->a[k] = L->a[i], k++, i++;
	show_Array(L);

	while (j < R->size)
		X->a[k] = R->a[j],	k++, j++;

}
void MergeSort(Array* X, int len, order order_type)
{
	if (len < 2)
		return;
	int pivot = len >> 1;

	Array* L = NULL;
	Array* R = NULL;
	L = (Array*)malloc(sizeof(Array));
	R = (Array*)malloc(sizeof(Array));
	gen_Array(L, pivot);
	gen_Array(R, len - pivot);

	Copy_Array(L, X, YES);
	Copy_Array(R, X, NO);

	MergeSort(L, pivot, order_type);
	MergeSort(R, len - pivot, order_type);
	Merge(X, L, R, order_type);

	free(L);
	free(R);
	L = NULL;
	R = NULL;
}
void sort_insertion(Array* X, order order_type)
{
	int i, j;
	int size = X->size;
	for (i = 1; i < size; i++)
		for (j = i; j > 0; j--)
			if (order_type(X->a[j - 1], X->a[j]) == NO)
				swap(&X->a[j - 1], &X->a[j]);
}
void sort_selection(Array* X, order order_type)
{
	int i, j, t;
	int n = X->size;
	for (i = 0; i <= n - 2; i++)
	{
		t = i;
		for (j = i + 1; j <= n - 1; j++)
		{
			if (order_type(X->a[j], X->a[t]) == YES)
				t = j;
		}
		swap(&X->a[i], &X->a[t]);
	}
}
void sort_bubble(Array* X, order order_type)
{
	int i, j, n = X->size;
	for (i = n - 1; i >= 0; i--)	// i > 0 도 가능, recursion으로 구현해보기
		for (j = 0; j <= i - 1; j++)
			if (!order_type(X->a[j], X->a[j + 1]) == YES)
				swap(&X->a[j], &X->a[j + 1]);
}
void sort_quick(Array* X, order order_type)
{
	int low = 0;
	int high = X->size - 1;
	Quicksort(X, low, high, order_type);
}
void sort_merge(Array* X, order order_type)
{
	MergeSort(X, X->size, order_type);
}
void sort(Array* X, void(*sort_alg)(Array*, int(*)(int, int)), order order_type)
{
	sort_alg(X, order_type);
}
void benchmark(Array* X, void(*sort)(Array*, int(*)(int, int)), order order_type)
{
	clock_t s, f;
	double d;
	s = clock();
	sort(X, order_type);
	f = clock();
	d = (double)(f - s) / CLOCKS_PER_SEC;
	printf("(%f sec.)\n", d);
}
int main()
{
	srand(time(NULL));
	Array A;
	gen_Array(&A, NUM);
	set_rand_Array(&A, NUM);
	//shuffle_Array_Fisher(&A);
	//show_Array(&A);
	

	Array T;
	gen_Array(&T, 5);
	(&T)->a[0] = 4;
	(&T)->a[1] = 1;
	(&T)->a[2] = 3;
	(&T)->a[3] = 5;
	(&T)->a[4] = 2;


	sort(&T, sort_merge, dec);
	show_Array(&T);


	return 0;

	sort(&A, sort_merge, dec);
	show_Array(&A);



	benchmark(&A, sort_merge, inc);

	sort(&A, sort_bubble, dec);
	//show_Array(&A);

	sort(&A, sort_merge, inc);
	show_Array(&A);
}