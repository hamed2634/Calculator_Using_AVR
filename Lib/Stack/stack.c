#include "..\stdTypes.h"
#include "stdlib.h"
#include "stack.h"

void Initialize_Stack(Stack* ps){
	ps->top = NULL;
	ps->size = 0;
}

void Push(Stack* ps, StackEntry val){
	StackNode* pn = (StackNode*) malloc(sizeof(StackNode));
	pn->entry = val;
	pn->next = ps->top;
	ps->top = pn;
	ps->size++;
}

void Pop(StackEntry *pe,Stack* ps){
	*pe = ps->top->entry;
	StackNode* pn = ps->top;
	ps->top = ps->top->next;
	free(pn);
	ps->size--;
}

int Stack_Empty(Stack* ps){
	return ps->top == NULL;
}

int Stack_Size(Stack* ps){
	return ps->size;
}

void Clear_Stack(Stack* ps){
	StackNode* pn = ps->top;
	while(pn){
		pn = pn->next;
		free(ps->top);
		ps->top = pn;
	}
	ps->size = 0;
}


StackEntry Top(Stack* ps){
	return ps->top->entry;
}

