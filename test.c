// 구조체 테스트
struct person {
    int id;
    char name[20];
};

int main() {
    struct person p = {1, "Alice"};
    printf("ID: %d, Name: %s\n", p.id, p.name);
    return 0;
}


