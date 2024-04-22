#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    int top;        
    int* stackArray; 
} Stack;


void init_stack(Stack* s, int size) {
    s->top = -1;
    s->stackArray = (int*)malloc(size * sizeof(int)); 
    if (s->stackArray == NULL) { 
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }
}


int is_empty(Stack* s) {
    return (s->top == -1);
}


void push(Stack* s, int item) {
    s->stackArray[++(s->top)] = item;
}


int pop(Stack* s) {
    if (is_empty(s)) { 
        fprintf(stderr, "���� ����÷ο�\n");
        exit(EXIT_FAILURE);
    }
    return s->stackArray[(s->top)--];
}


int eval(char* expression) {
    Stack stack;
    init_stack(&stack, MAX_SIZE); 


    for (int i = 0; expression[i] != '\0'; i++) {
        printf("expression : %c\n", expression[i]); 
        if (isdigit(expression[i])) { 
            push(&stack, expression[i] - '0'); 
        }
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            if (!is_empty(&stack)) {
                int operand2 = pop(&stack);
                int operand1 = pop(&stack);
                switch (expression[i]) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        fprintf(stderr, "����: 0���� ���� �� �����ϴ�\n");
                        exit(EXIT_FAILURE);
                    }
                    push(&stack, operand1 / operand2);
                    break;
                }
            }
            else {
                fprintf(stderr, "����: ������ �ǿ�����\n");
                exit(EXIT_FAILURE);
            }
        }
    }


    printf("\n");

    if (!is_empty(&stack)) {
        int result = pop(&stack);
        if (is_empty(&stack)) {
            free(stack.stackArray); 
            return result;
        }
        else {
            fprintf(stderr, "����: �ʹ� ���� �ǿ�����\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        fprintf(stderr, "����: �ǿ����ڰ� �����ϴ�\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char expression[MAX_SIZE]; 
    int result;

    printf("���� ǥ����� �Է��ϼ���: ");
    fgets(expression, sizeof(expression), stdin); 

    result = eval(expression); 
    printf("���: %d\n", result);

    return 0;
}