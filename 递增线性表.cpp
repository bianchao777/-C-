#include<stdio.h> 
#include<stdlib.h> 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0 

#define INFEASIBLE -1
#define OVERFLOW -2		//�ڴ���� 

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef int Status;		//��������ֵ���� 
typedef int ElemType;	//Ԫ������ 

Status visit(ElemType c){
	printf("%d ",c); 
	return OK; 
} 

typedef struct{
	ElemType *elem;		//�ɱ�����/���Ա� ��ʼ��ַ 
	int length;			//��ǰ���ó��� 
	int listsize;		//����̶�����	 
}SqList;

/*��ʼ��˳�����Ա�*/
Status InitList(SqList &L)
{
	//��������Ա�
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize = LIST_INIT_SIZE;
	return OK;  
} 

/*	
	��ʼ����:����˳����Ѿ�����
	�������:��LΪ�ձ�,����TRUE,���򷵻�FALSE		
*/ 
Status ListEmpty(SqList L)
{
	if(L.length==0) 
		return TRUE;
	else
		return FALSE;
}

/*	
	��ʼ����:����˳����Ѿ�����
	�������:��L����Ϊ�ձ�	
*/ 
Status ClearList(SqList &L)
{
	L.length=0;
	return OK; 

} 

/*
	��ʼ����������˳����Ѿ����� 
	�������������L������Ԫ�ظ��� 
*/
Status ListLength(SqList L)
{
	return L.length;
} 

/*
	��ʼ����������˳����Ѿ����� ,1<=i<=ListLength(L)
	�������������L�е�i������
*/
Status GetElem(SqList L,int i,ElemType &e){
	
	if(i>=1&&i<=ListLength(L)){
		e=*(L.elem+i-1);
		return OK;
	}else{
		return ERROR;
	} 
} 

/*
	��ʼ���������Ա�L�Ѿ�����
	������������L��ÿ������ 
*/
Status ListTraverse(SqList L)
{
	for(int i=0;i<L.length;i++){
		visit(*(L.elem+i));
	}
	printf("\n");
	return OK;
} 

/*
	��ʼ����������˳����Ѿ����� 
	�������������L�е�һ����e��ȵ�����Ԫ�ص�λ�� 
*/
Status LocateElem(SqList L,ElemType e)
{
	int i;

	for(i=0;i<ListLength(L);i++){
		if(e==*(L.elem+i)){
			break;
		}
	}
	if(i>=ListLength(L)){
		return 0;
	}
	
	return i+1;
}
/*
	��ʼ����������˳����Ѿ����� ,1<=i<=ListLength(L)+1
	�����������L�ĵ�i��λ��֮ǰ�����µ�Ԫ��e��L�ĳ��ȼ�1 
*/ 
Status ListInsert(SqList &L,int i,ElemType e)
{
	if(i<1||i>ListLength(L)+1){
		return ERROR;
	}
	if(L.length>=L.listsize){
		ElemType* newbase=(ElemType*)realloc(L.elem,(L.listsize+LIST_INCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
		L.elem=newbase;
		L.listsize+=LIST_INCREMENT;
	}
//	ElemType* q=L.elem+i-1;
//	for(ElemType* p=L.elem+L.length-1;p>=q;p--){
//		*(p+1)=*p;
//	}
//	*q=e;
	
	for(int j=L.length-1;j>=i-1;j--){
		L.elem[j+1]=L.elem[j];
	}
	L.elem[i-1]=e;
	L.length++;

	return OK;
	
}

/*
	��ʼ����������˳����Ѿ����� ,1<=i<=ListLength(L)
	���������ɾ��L�ĵ�i��λ�õ����ݣ�����e������ֵ 
*/ 
Status ListDelete(SqList &L,int i,ElemType &e)
{
	if(L.length==0){
		return ERROR;
	} 
	if(i<1||i>ListLength(L)){
		return ERROR;
	}
	e=L.elem[i-1];
	for(int j=i-1;j<L.length-1;j++){
		L.elem[j]=L.elem[j+1];
	}
	L.length--;
	
	return OK;
}

/*
	��ʼ����������˳���L�Ѿ����� ,�ҵ��� 
	�����������L�в���x
*/ 
Status ListInsert_(SqList &va,ElemType x)
{
	if(va.length==0){
		return ERROR;
	}
	if(va.length>=va.listsize){
		ElemType* newbase=(ElemType*)realloc(va.elem,(va.listsize+LIST_INCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
		va.elem=newbase;
		va.listsize+=LIST_INCREMENT;
	}
//	1.��ǰ�濪ʼ�� 
//	for(int i=1;i<=va.length;i++){
//		if(i==1&&x<va.elem[i-1]){
//			for(int j=va.length-1;j>=0;j--){
//				va.elem[j+1]=va.elem[j];
//			}
//			va.elem[0]=x;
//			break;
//		}
//		if(x>=va.elem[i-1]&&x<va.elem[i]){
//			for(int j=va.length-1;j>=i;j--){
//				va.elem[j+1]=va.elem[j];
//			}
//			va.elem[i]=x;
//			break;
//		}
//		if(i==va.length&&x>=va.elem[i-1]){
//			va.elem[va.length]=x;
//			break;
//		}
//	}
//2.�Ӻ��濪ʼ�� 
//	for(int i=va.length;i>=1;i--){
//		if(x>=va.elem[i-1]){
//			for(int j=va.length;j>=i;j--){
//				va.elem[j+1]=va.elem[j];
//			}
//			va.elem[i]=x;
//			break;
//		}
//	} 
//3.�Ӻ����ҵ�ͬʱ��ʼ����ƶ�
	int i=va.length-1; 
 	while(i>=0&&x<va.elem[i]){
		va.elem[i+1]=va.elem[i];
		i--;
	}				//����λ�ò���Ԫ�غ��� 
	va.elem[i+1]=x;	//����x 
	va.length++;	//��+1 
	return OK;
}
int main(){
	SqList L;
	SqList L_; 
	Status x;
	InitList(L);
	for(int i=1;i<10;i++){
		ListInsert(L,i,2*i);
	}
	ListTraverse(L);
	do{
		printf("������Ҫ���������");
		scanf("%d",&x);
		ListInsert_(L,x); 
		ListTraverse(L);
	}while(x!=-1);
	
	return 0; 
}

