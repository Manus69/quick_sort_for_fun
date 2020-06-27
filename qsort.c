#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EPSILON 1e-2

#define PRINT_ITEM(format, cast, x) printf(format, cast x)
#define GET_VARIABLE(type, name) type name
#define CAST(cast, name) cast name
#define ABS(x) (x) < 0 ? -(x) : (x)
#define COMPARE(x, y) ((x) < (y)) ? -1 : ((x) != (y))

void swap(void* array, int j, int k, size_t item_size)
{
    void* copy = malloc(item_size);
    if (!copy) return ;
    copy = memcpy(copy, array + j * item_size, item_size);
    memcpy(array + j * item_size, array + k * item_size, item_size);
    memcpy(array + k * item_size, copy, item_size);
    free(copy);
}

void print_array(void* array, int size, int item_size, char type)
{
    int n = 0;
    void* entry = array;

    while (n < size)
    {
        if (type == 'i')
            PRINT_ITEM("%d ", *(int*), entry);
        else if (type == 'c')
            PRINT_ITEM("%c ", *(char*), entry);
        else if (type == 'f')
            PRINT_ITEM("%f ", *(double*), entry);
        else
            printf("%c ", '?');
        n ++;
        entry = entry + item_size;
    }
    printf("\n");
}

int compare_integers(void* lhs, void* rhs)
{
    int left = *(int*)lhs;
    int right = *(int*)rhs;
    int result = left < right ? -1 : left != right;
    return result;
}

int compare_characters(void* lhs, void* rhs)
{
    GET_VARIABLE(char, left) = CAST(*(char*), lhs);
    GET_VARIABLE(char, right) = CAST(*(char*), rhs);
    int result = left < right ? -1 : left != right;
    return result;
}

int compare_doubles(void* lhs, void* rhs)
{
    double left = *(double*)lhs;
    double right = *(double*)rhs;
    // double diff = ABS(right - left);
    int result = left < right ? -1 : left != right;
    return result;
}

void qsort_mk1
(void* array, int left_index, int right_index, size_t item_size, int (*compare)(void* , void*))
{
    int pivot_index = right_index;
    int current_index = 0;
    void* pivot = array + pivot_index * item_size;
    void* current_item = NULL;

    if (left_index >= right_index)
        return ;

    while (current_index < pivot_index)
    {
        current_item = array + current_index * item_size;
        if (compare(current_item, pivot) == 1)
        {
            if (pivot_index - current_index != 1)
                swap(array, pivot_index - 1, pivot_index, item_size);
            swap(array, current_index, pivot_index, item_size);
            pivot_index --;
            pivot = pivot - item_size;
        }
        else
        {
            current_index ++;
            current_item = current_item + item_size;
        }
    }
    qsort_mk1(array, left_index, pivot_index - 1, item_size, compare);
    qsort_mk1(array, pivot_index + 1, right_index, item_size, compare);
}

void why_qsort(void* array, size_t number_of_items, size_t item_size, int (*compare)(void* , void* ))
{
    qsort_mk1(array, 0, number_of_items - 1, item_size, compare);
}

#define RUN 1
#ifdef RUN
int main(void)
{
    char* string = strdup("9876eatshit54321");
    int size = strlen(string);
    size_t item_size = sizeof(char);

    print_array(string, size, item_size, 'c');
    why_qsort(string, size, item_size, compare_characters);
    print_array(string, size, item_size, 'c');

    // double d_array[] = {-1, 3.14, 3.14159, 2.71828, -666};
    // int size = 5;
    // size_t item_size = sizeof(double);
    // print_array(d_array, size, item_size, 'f');
    // why_qsort(d_array, size, item_size, compare_doubles);
    // print_array(d_array, size, item_size, 'f');


    return 0;
}
#endif
