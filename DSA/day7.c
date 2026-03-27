#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* newNode(int value) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = value;
    node->prev = node->next = NULL;
    return node;
}

void printList(struct Node* head) {
    if (!head) {
        printf("List is empty!\n");
        return;
    }
    struct Node* temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Node* insertFirst(struct Node* head, int value) {
    struct Node* node = newNode(value);
    if (head) {
        node->next = head;
        head->prev = node;
    }
    printf("Inserted %d at first\n", value);
    return node;
}

struct Node* insertLast(struct Node* head, int value) {
    struct Node* node = newNode(value);
    if (!head) {
        printf("Inserted %d at last\n", value);
        return node;
    }
    struct Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = node;
    node->prev = temp;
    printf("Inserted %d at last\n", value);
    return head;
}

struct Node* insertAt(struct Node* head, int value, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return head;
    }
    if (position == 1) return insertFirst(head, value);
    struct Node* temp = head;
    for (int i = 1; temp && i < position - 1; i++) temp = temp->next;
    if (!temp) {
        printf("Position out of range!\n");
        return head;
    }
    struct Node* node = newNode(value);
    node->next = temp->next;
    if (temp->next) temp->next->prev = node;
    temp->next = node;
    node->prev = temp;
    printf("Inserted %d at position %d\n", value, position);
    return head;
}

struct Node* insertAfter(struct Node* head, int value, int after) {
    struct Node* temp = head;
    while (temp && temp->data != after) temp = temp->next;
    if (!temp) {
        printf("Data %d not found!\n", after);
        return head;
    }
    struct Node* node = newNode(value);
    node->next = temp->next;
    if (temp->next) temp->next->prev = node;
    temp->next = node;
    node->prev = temp;
    printf("Inserted %d after %d\n", value, after);
    return head;
}

struct Node* deleteFirst(struct Node* head) {
    if (!head) {
        printf("List is empty!\n");
        return NULL;
    }
    struct Node* temp = head;
    head = head->next;
    if (head) head->prev = NULL;
    printf("Deleted %d\n", temp->data);
    free(temp);
    return head;
}

struct Node* deleteLast(struct Node* head) {
    if (!head) {
        printf("List is empty!\n");
        return NULL;
    }
    if (!head->next) {
        printf("Deleted %d\n", head->data);
        free(head);
        return NULL;
    }
    struct Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->prev->next = NULL;
    printf("Deleted %d\n", temp->data);
    free(temp);
    return head;
}

struct Node* deleteAt(struct Node* head, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return head;
    }
    if (position == 1) return deleteFirst(head);
    struct Node* temp = head;
    for (int i = 1; temp && i < position; i++) temp = temp->next;
    if (!temp) {
        printf("Position out of range!\n");
        return head;
    }
    if (temp->next) temp->next->prev = temp->prev;
    if (temp->prev) temp->prev->next = temp->next;
    printf("Deleted %d at pos %d\n", temp->data, position);
    free(temp);
    return head;
}

struct Node* deleteData(struct Node* head, int value) {
    struct Node* temp = head;
    while (temp && temp->data != value) temp = temp->next;
    if (!temp) {
        printf("Data %d not found!\n", value);
        return head;
    }
    if (temp == head) return deleteFirst(head);
    if (temp->next) temp->next->prev = temp->prev;
    if (temp->prev) temp->prev->next = temp->next;
    printf("Deleted %d\n", temp->data);
    free(temp);
    return head;
}

int count(struct Node* head) {
    int c = 0;
    while (head) { c++; head = head->next; }
    return c;
}

int searchPos(struct Node* head, int value) {
    for (int pos = 1; head; head = head->next, pos++)
        if (head->data == value) return pos;
    return -1;
}

int frequency(struct Node* head, int value) {
    int freq = 0;
    while (head) {
        if (head->data == value) freq++;
        head = head->next;
    }
    return freq;
}

struct Node* sortList(struct Node* head) {
    if (!head || !head->next) return head;
    int swapped;
    struct Node *p, *lastSorted = NULL;
    do {
        swapped = 0;
        p = head;
        while (p->next != lastSorted) {
            if (p->data > p->next->data) {
                int tmp = p->data;
                p->data = p->next->data;
                p->next->data = tmp;
                swapped = 1;
            }
            p = p->next;
        }
        lastSorted = p;
    } while (swapped);
    return head;
}

struct Node* reverseList(struct Node* head) {
    struct Node *curr = head, *temp = NULL;
    while (curr) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if (temp) head = temp->prev;
    return head;
}

void freeList(struct Node* head) {
    while (head) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int mainChoice, subChoice, data, pos, after;
    while (1) {
        printf("\n1.Create  2.Print  3.Insert  4.Delete  5.Count  6.Search  7.Sort  8.Reverse  9.Exit\nChoice: ");
        scanf("%d", &mainChoice);
        if (mainChoice == 9) {
            freeList(head);
            break;
        }
        switch (mainChoice) {
            case 1:
                freeList(head);
                head = NULL;
                printf("Enter no. of elements: ");
                int n;
                scanf("%d", &n);
                while (n--) {
                    scanf("%d", &data);
                    head = insertLast(head, data);
                }
                break;
            case 2:
                printList(head);
                break;
            case 3:
                printf("1.First  2.Last  3.Position  4.AfterData: ");
                scanf("%d", &subChoice);
                printf("Enter data: ");
                scanf("%d", &data);
                if (subChoice == 1) head = insertFirst(head, data);
                else if (subChoice == 2) head = insertLast(head, data);
                else if (subChoice == 3) {
                    printf("Pos: ");
                    scanf("%d", &pos);
                    head = insertAt(head, data, pos);
                } else if (subChoice == 4) {
                    printf("After: ");
                    scanf("%d", &after);
                    head = insertAfter(head, data, after);
                }
                break;
            case 4:
                printf("1.First  2.Last  3.Position  4.Data: ");
                scanf("%d", &subChoice);
                if (subChoice == 1) head = deleteFirst(head);
                else if (subChoice == 2) head = deleteLast(head);
                else if (subChoice == 3) {
                    printf("Pos: ");
                    scanf("%d", &pos);
                    head = deleteAt(head, pos);
                } else if (subChoice == 4) {
                    printf("Data: ");
                    scanf("%d", &data);
                    head = deleteData(head, data);
                }
                break;
            case 5:
                printf("Count: %d\n", count(head));
                break;
            case 6:
                printf("1.Presence  2.Position  3.Frequency: ");
                scanf("%d", &subChoice);
                printf("Data: ");
                scanf("%d", &data);
                if (subChoice == 1)
                    printf("%s\n", searchPos(head, data) != -1 ? "Present" : "Not found");
                else if (subChoice == 2) {
                    pos = searchPos(head, data);
                    printf(pos == -1 ? "Not found\n" : "At pos %d\n", pos);
                } else if (subChoice == 3)
                    printf("Freq: %d\n", frequency(head, data));
                break;
            case 7:
                head = sortList(head);
                printf("Sorted!\n");
                break;
            case 8:
                head = reverseList(head);
                printf("Reversed!\n");
                break;
        }
    }
}
