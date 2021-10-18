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
	
	if(i>=1&&i<=L.length){
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

	for(i=0;i<L.length;i++){
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



//�����ܽ�

/*
	��ʼ����������˳����Ѿ����� ,1<=i<=ListLength(L),0<=k<=ListLength(L)-1;
	���������ɾ��L�ĵ�i��λ�����k������
*/ 
Status DeleteK(SqList &L,int i,int k)
{
	if(i<1||i>ListLength(L)||k<0||k>ListLength(L)-i+1){
		return INFEASIBLE;
	}
	else{
		for(int count=0;count<k;count++){
			for(int j=i-1;j<L.length-1;j++){
				L.elem[j]=L.elem[j+1];
			}
			L.length--;
		}
		return OK;
	}
} 

//�͵�����
Status f(SqList &L)
{
	ElemType temp;
	for(int i=0;i<L.length/2;i++){
		temp=L.elem[i];
		L.elem[i]=L.elem[L.length-1-i];
		L.elem[L.length-1-i]=temp;
	}
} 
int main(){
	SqList L;
	SqList L_; 
	ElemType e;
	Status i;
	i=InitList(L);
	if(i==1){
		printf("��ʼ��L�ɹ�\n");	
	}
	i=ListEmpty(L);
	if(i==1){
		printf("LΪ�ձ�\n");	
	}
	
	printf("�ڱ�ͷһ�β���1��2��3��4��5�����Ϊ"); 
	for(int i=1;i<=5;i++){
		ListInsert(L,1,i);
	}
	ListTraverse(L);
//	ListDelete(L,L.length,e);
//	printf("ɾ�����һ��λ�õ�����,ɾ��������Ϊ%d�����Ϊ",e);
//	ListTraverse(L);

	printf("�ڱ�βһ�β���0��1��2��3��4��5�����������Ϊ"); 
	for(int i=0;i<=5;i++){
		ListInsert(L,L.length+1,3*i);
	}
	ListTraverse(L);

//	
//	GetElem(L,2,e);
//	printf("�ڶ���λ�õ�����Ϊ%d\n",e) ;
	
	ListDelete(L,7,e);
	printf("ɾ�����߸�λ�õ�����,ɾ��������Ϊ%d\n",e);
	ListTraverse(L);
	printf("�͵����ã����Ϊ��")
	f(L);
	ListTraverse(L);
//	ListDelete(L,L.length,e);
//	printf("ɾ�����һ��λ�õ�����,ɾ��������Ϊ%d\n",e);
//	ListTraverse(L);
//	ListDelete(L,L.length,e);
//	printf("ɾ�����һ��λ�õ�����,ɾ��������Ϊ%d\n",e);
//	ListTraverse(L);
//	
//	printf("�ڵڶ���λ�ò���100�����Ϊ"); 
//	ListInsert(L,2,100);
//	ListInsert(L,2,99);
//	ListTraverse(L);

//	i=LocateElem(L,2);
//	printf("��%d��λ�õ�ֵΪ2\n",i);
	i=5;int j=L.length-i+1;
	if(DeleteK(L,i,j)==INFEASIBLE){
		printf("��������"); 
	}
	else{
		printf("ɾ����%d��λ�����%d��Ԫ�أ����Ϊ",i,j);
		ListTraverse(L);
	} 
	
	return 0; 
}

