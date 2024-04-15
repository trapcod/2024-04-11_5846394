#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 5

typedef int element;
typedef struct {
	element* data;
	int top;
	int capacity;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
	s->capacity = MAX_STACK_SIZE;
	s->data = (element*)malloc(s->capacity * sizeof(element));
	if (s->data == NULL) {
		fprintf(stderr, "메모리 할당 에러\n");
		exit(1);
	}
}

void resize_stack(StackType* s) {
	s->capacity *= 2;
	s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	if (s->data == NULL) {
		fprintf(stderr, "메모리 재할당 에러\n");
		exit(1);
	}
}

void push(StackType* s, element item) {
	if (s->top == s->capacity - 1) {
		resize_stack(s);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (s->top == -1) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	return s->data[(s->top)--];
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int main(void) {
	StackType s;
	init_stack(&s);
	srand(time(NULL));

	for (int i = 0; i < 30; i++) {
		int rand_num = rand() % 100 + 1;
		if (rand_num % 2 == 0) {
			printf("Push : %d\n", rand_num);
			push(&s, rand_num);
		}
		else {
			printf("Pop : ",rand_num);
			if (!is_empty(&s)) {
				printf("%d\n", pop(&s));
			}
			else {
				printf("Stack is empty\n");
			}
		}
	}

	// 스택 사용 후 메모리 해제
	free(s.data);
	return 0;
}