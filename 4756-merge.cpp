#include <iostream>
#include <pthread.h>
#define width 20
using namespace std;
int arr[width];
void read_input_file(int part_size){
    for(int i=0; i<part_size; i++)
    {
        cin>>arr[i];
    }
}
void merge_update(int first, int last){
    int mid_index = (first+last)/2;
    int left_indexes_first_arr = first;
    int left_indexes_second_arr = mid_index+1;
    int size_of_new_arr = last-first+1 ;
    int updated_arr[size_of_new_arr];
    int updated_arr_index = 0;
    while(left_indexes_first_arr <= mid_index && left_indexes_second_arr <= last)
    {
        if (arr[left_indexes_first_arr] > arr[left_indexes_second_arr])
        {
            updated_arr[updated_arr_index] = arr[left_indexes_second_arr];
            updated_arr_index++;
            left_indexes_second_arr++;
        }
        else
        {
            updated_arr[updated_arr_index] = arr[left_indexes_first_arr];
            updated_arr_index++;
            left_indexes_first_arr++;
        }
    }
    while(left_indexes_second_arr <= last)
    {
        updated_arr[updated_arr_index++] = arr[left_indexes_second_arr++];
    }
    while(left_indexes_first_arr <= mid_index)
    {
        updated_arr[updated_arr_index++] = arr[left_indexes_first_arr++];
    }
    for (int i = 0; i < size_of_new_arr ; i++)
    {
        arr[first+i] = updated_arr[i];
    }
}
void * merge_thread_update(void* thread_data){
    int* Info_main = (int*)thread_data;
    int middle=(Info_main[0]+Info_main[1])/2;
    int *Info_1 = new int[2];
    int *Info_2 = new int[2];
    Info_1[0] = Info_main[0];
    Info_1[1] = middle;
    Info_2[0]=middle+1;
    Info_2[1]=Info_main[1];
    if (Info_main[0] >= Info_main[1])
    {

    }
    else
    {
        pthread_t first_half_thread,second_half_thread;
        pthread_create(&first_half_thread,NULL,merge_thread_update,(void*)Info_1);
        pthread_create(&second_half_thread,NULL,merge_thread_update,(void*)Info_2);
        pthread_join(first_half_thread,NULL);
        pthread_join(second_half_thread,NULL);
        merge_update(Info_main[0],Info_main[1]);
    }
}
void merge_thread(int part_size){
    int* Info = new int[2];
    Info[0]=0;
    Info[1]=part_size-1;
    pthread_t main_thread;
    pthread_create(&main_thread,NULL,merge_thread_update,(void*)Info);
    pthread_join(main_thread,NULL);
    for(int i=0; i<part_size; i++)
    {
        cout<<arr[i]<<" ";
    }
}
int main(){
    freopen("input.txt","r",stdin);
    int part_size;
    cin>>part_size;
    read_input_file(part_size);
    merge_thread(part_size);
    return 0;
}
