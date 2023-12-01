#ifndef STACK_H
#define STACK_H
	
	typedef char StackEntry ;

	typedef struct StackNode{
		StackEntry entry;
		struct StackNode* next;
	}StackNode;

	
	typedef struct Stack{
		StackNode* top;
		int size;
	}Stack;
	
	void Initialize_Stack(Stack* ps);
	void Push(Stack* ps, StackEntry val);
	void Pop(StackEntry *e,Stack* ps);
	int Stack_Empty(Stack* ps);
	int Stack_Size(Stack* ps);
	StackEntry Top(Stack* ps);
	void Clear_Stack(Stack* ps);
	
#endif
