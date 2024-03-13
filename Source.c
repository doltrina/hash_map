#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>

typedef double hash_type;

typedef struct hash_cell {
    int key;
    hash_type data;
} cell;

typedef struct hash_table {
    cell* list;
    size_t size;
} table;

int hash(int key, int size);
table* hash_table_create(size_t size);
table* hash_table_expand(table* map);
table* hash_table_insert(table* map, int key, hash_type data);
int have_key(table* map, int key);
hash_type find(table* map, int key);

int main() {
    setlocale(LC_CTYPE, "RUS");

    table* map = hash_table_create(1);
    int choice, key, n = 0;
    hash_type data, find_data;
    while (1)
    {
        printf("\n1.Вставить элемент в хэш-таблицу\n2.Найти элемент по ключу\n3.Проверить, заполнена ли хэш-таблица\n4.Вывести хэш-таблицу\n\nПожалуйста, выберите нужный вариант: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            printf("Введите ключ: ");
            scanf("%d", &key);
            data = key * sqrt(7);
            map = hash_table_insert(map, key, data);
            n++;
            break;
        case 2:
            printf("Введите ключ: ");
            scanf("%d", &key);
            getchar();
            find_data = find(map, key);
            if (find_data) {
                printf("Найденное значение: ");
                if (find_data == (int)find_data) printf("%d\n", find_data);
                else printf("%lf\n", find_data);
            }
            else printf("Введенный ключ отсутствует\n");
            break;
        case 3:
            if (n == map->size) printf("Таблица заполнена\n");
            else printf("Таблица не заполнена\n");

            break;
        case 4:
            for (int ind = 0; ind < map->size; ind++) {
                if (map->list[ind].key == NULL) {
                    printf("Незаполненная ячейка\n");
                }
                else {
                    printf("Ключ: %d  ", map->list[ind].key, map->list[ind].data);
                    if (map->list[ind].data == (int)map->list[ind].data) printf("Значение: %d\n", map->list[ind].data);
                    else printf("Значение: %lf\n", map->list[ind].data);
                }
                    
            }

            break;
        default:
            printf("Неверно введены данные\n");
        }

    }
}

int hash(int key, int size) {
    return key % size;
}

table* hash_table_create(size_t size) {
    table* map = malloc(sizeof(table));

    map->size = size;
    map->list = calloc(map->size, sizeof(cell));

    return map;
}

table* hash_table_expand(table* map) {
    table* expanded = hash_table_create(map->size * 2);
    
    for (int ind = 0; ind < map->size; ind++) {
        if (map->list[ind].key != NULL) {
            expanded = hash_table_insert(expanded, map->list[ind].key, map->list[ind].data);
        }
    }
    
    return expanded;
}

table* hash_table_insert(table* map, int key, hash_type data) {
    int ind = hash(key, map->size);
    while (map->list[ind].key != NULL) {
        ind += 1;
        
        if (ind == map->size) {
            return hash_table_insert(hash_table_expand(map), key, data);
        }
    }
    map->list[ind].key = key;
    map->list[ind].data = data;
    return map;

}

int have_key(table* map, int key) {
    for (int ind = hash(key, map); ind < map->size; ind++) {
        int current = map->list[ind].key;
        if (current == NULL) continue;
        if (current == key) return 1;
    }
    return 0;
}

hash_type find(table* map, int key) {
    
        for (int ind = hash(key, map->size); ind < map->size; ind++) {
            int current = map->list[ind].key;
            if (current == NULL) continue;
            if (current == key) return map->list[ind].data;
        }
    
    return 0;
}