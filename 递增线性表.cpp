#include<stdio.h> 
#include<stdlib.h> 

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0 

#define INFEASIBLE -1
#define OVERFLOW -2		//内存溢出 

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

typedef int Status;		//函数返回值类型 
typedef int ElemType;	//元素类型 

Status visit(ElemType c){
	printf("%d ",c); 
	return OK; 
} 

typedef struct{
	ElemType *elem;		//可变数组/线性表 起始地址 
	int length;			//当前利用长度 
	int listsize;		//分配固定长度	 
}SqList;

/*初始化顺序线性表*/
Status InitList(SqList &L)
{
	//构造空线性表
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize = LIST_INIT_SIZE;
	return OK;  
} 

/*	
	初始条件:线性顺序表已经存在
	操作结果:若L为空表,返回TRUE,否则返回FALSE		
*/ 
Status ListEmpty(SqList L)
{
	if(L.length==0) 
		return TRUE;
	else
		return FALSE;
}

/*	
	初始条件:线性顺序表已经存在
	操作结果:将L重置为空表	
*/ 
Status ClearList(SqList &L)
{
	L.length=0;
	return OK; 

} 

/*
	初始条件：线性顺序表已经存在 
	操作结果：返回L中数据元素个数 
*/
Status ListLength(SqList L)
{
	return L.length;
} 

/*
	初始条件：线性顺序表已经存在 ,1<=i<=ListLength(L)
	操作结果：返回L中第i个数据
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
	初始条件：线性表L已经存在
	操作结果：输出L的每个数据 
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
	初始条件：线性顺序表已经存在 
	操作结果：返回L中第一个与e相等的数据元素的位序 
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
	初始条件：线性顺序表已经存在 ,1<=i<=ListLength(L)+1
	操作结果：在L的第i个位置之前插入新的元素e，L的长度加1 
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
	初始条件：线性顺序表已经存在 ,1<=i<=ListLength(L)
	操作结果：删除L的第i个位置的数据，并用e返回其值 
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
	初始条件：线性顺序表L已经存在 ,且递增 
	操作结果：在L中插入x
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
//	1.从前面开始找 
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
//2.从后面开始找 
//	for(int i=va.length;i>=1;i--){
//		if(x>=va.elem[i-1]){
//			for(int j=va.length;j>=i;j--){
//				va.elem[j+1]=va.elem[j];
//			}
//			va.elem[i]=x;
//			break;
//		}
//	} 
//3.从后面找的同时开始向后移动
	int i=va.length-1; 
 	while(i>=0&&x<va.elem[i]){
		va.elem[i+1]=va.elem[i];
		i--;
	}				//查找位置并且元素后移 
	va.elem[i+1]=x;	//插入x 
	va.length++;	//表长+1 
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
		printf("请输入要插入的数字");
		scanf("%d",&x);
		ListInsert_(L,x); 
		ListTraverse(L);
	}while(x!=-1);
	
	return 0; 
}

