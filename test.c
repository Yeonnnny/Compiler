int main() {
    int num;

    if (num == 0) {
        num = num + 3;
    }

    do {
        printf("현재 값: %d\n", num);
        num--;
    } while (num != 0);

    return 0;
}
