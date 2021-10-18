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
	
	if(i>=1&&i<=L.length){
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



//做题总结

/*
	初始条件：线性顺序表已经存在 ,1<=i<=ListLength(L),0<=k<=ListLength(L)-1;
	操作结果：删除L的第i个位置起的k个数据
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

//就地逆置
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
		printf("初始化L成功\n");	
	}
	i=ListEmpty(L);
	if(i==1){
		printf("L为空表\n");	
	}
	
	printf("在表头一次插入1，2，3，4，5，结果为"); 
	for(int i=1;i<=5;i++){
		ListInsert(L,1,i);
	}
	ListTraverse(L);
//	ListDelete(L,L.length,e);
//	printf("删除最后一个位置的数据,删除的数据为%d，结果为",e);
//	ListTraverse(L);

	printf("在表尾一次插入0，1，2，3，4，5的三倍，结果为"); 
	for(int i=0;i<=5;i++){
		ListInsert(L,L.length+1,3*i);
	}
	ListTraverse(L);

//	
//	GetElem(L,2,e);
//	printf("第二个位置的数据为%d\n",e) ;
	
	ListDelete(L,7,e);
	printf("删除第七个位置的数据,删除的数据为%d\n",e);
	ListTraverse(L);
	printf("就地逆置，结果为：")
	f(L);
	ListTraverse(L);
//	ListDelete(L,L.length,e);
//	printf("删除最后一个位置的数据,删除的数据为%d\n",e);
//	ListTraverse(L);
//	ListDelete(L,L.length,e);
//	printf("删除最后一个位置的数据,删除的数据为%d\n",e);
//	ListTraverse(L);
//	
//	printf("在第二个位置插入100，结果为"); 
//	ListInsert(L,2,100);
//	ListInsert(L,2,99);
//	ListTraverse(L);

//	i=LocateElem(L,2);
//	printf("第%d个位置的值为2\n",i);
	i=5;int j=L.length-i+1;
	if(DeleteK(L,i,j)==INFEASIBLE){
		printf("参数错误"); 
	}
	else{
		printf("删除第%d的位置起的%d个元素，结果为",i,j);
		ListTraverse(L);
	} 
	
	return 0; 
}

