// 구조체와 열거형 테스트
//#include <stdio.h>

typedef struct {
    int id;
    char name[20];
} Person;

enum Color { RED, GREEN, BLUE };

int main() {
    Person p = {1, "Alice"};
    enum Color favoriteColor = BLUE;

    printf("ID: %d, Name: %s\n", p.id, p.name);
    printf("Favorite Color: %d\n", favoriteColor);
    return 0;
}
