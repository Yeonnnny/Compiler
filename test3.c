// 배열과 포인터 테스트
int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    int i;
    for (i = 0; i < 5; i++) {
        printf("Element %d: %d\n", i, *(ptr + i));
    }
    return 0;
}
