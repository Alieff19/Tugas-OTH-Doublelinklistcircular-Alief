#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = newNode;
    return newNode;
}

void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* last = (*head)->prev;
        newNode->next = *head;
        (*head)->prev = newNode;
        newNode->prev = last;
        last->next = newNode;
    }
}

void printList(Node* head) {
    if (head == NULL) return;
    Node* temp = head;
    do {
        printf("Address: %p, Data: %d\n", (void*)temp, temp->data);
        temp = temp->next;
    } while (temp != head);
}

void sortList(Node** head) {
    if (*head == NULL) return;
    Node* current = *head;
    Node* index = NULL;
    Node* temp = NULL;

    do {
        index = current->next;
        while (index != *head) {
            if (current->data > index->data) {
                Node* prevCurrent = current->prev;
                Node* nextCurrent = current->next;
                Node* prevIndex = index->prev;
                Node* nextIndex = index->next;

                if (current->next == index) {
                    current->next = nextIndex;
                    current->prev = index;
                    index->next = current;
                    index->prev = prevCurrent;
                    if (nextIndex != *head) nextIndex->prev = current;
                    if (prevCurrent != *head) prevCurrent->next = index;
                } else {
                    current->next = nextIndex;
                    current->prev = prevIndex;
                    index->next = nextCurrent;
                    index->prev = prevCurrent;
                    if (nextIndex != *head) nextIndex->prev = current;
                    if (prevIndex != *head) prevIndex->next = current;
                    if (nextCurrent != *head) nextCurrent->prev = index;
                    if (prevCurrent != *head) prevCurrent->next = index;
                }

                if (*head == current) *head = index;
                else if (*head == index) *head = current;

                temp = current;
                current = index;
                index = temp;
            }
            index = index->next;
        }
        current = current->next;
    } while (current->next != *head);
}

int main() {
    Node* head = NULL;
    int N, data;

    printf("Masukkan jumlah data: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        printf("Masukkan data ke-%d: ", i + 1);
        scanf("%d", &data);
        append(&head, data);
    }

    printf("List sebelum pengurutan:\n");
    printList(head);

    sortList(&head);

    printf("List setelah pengurutan:\n");
    printList(head);

    return 0;
}