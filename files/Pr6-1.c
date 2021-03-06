/* ハッシュ法によるデータ管理（チェイン法版） */

#include <stdio.h>
#include<stdlib.h>

#define ERROR    -1
#define HASH_SIZE  9
typedef struct character {
	int no;					/* キー */
	char name[16];			/* 名前 */
	struct character *next_addr;	/* 次のデータのアドレス */
} CHARACTER;
CHARACTER *HashTable[HASH_SIZE];

/* 数値の入力用関数 */
int get_num(void)
{
	int i;
	int d=0;
	int c=0;
	rewind(stdin);
	for(i=0;i<5&&c!='\n';i++){
		/* 5ケタまで */
		c=getchar();
		if(c=='\n')	break;
		d=d*10+c-'0';
	}
	rewind(stdin);
	return d;
}

/* ハッシュ表からリスト構造で並んでいる様子を表示する */
void disp(void)
{
	int i=0;
	struct character *current_addr;
	for(i=0;i<HASH_SIZE;i++){
		printf("-|%d|",i);
		printf("%2d|-",HashTable[i]);
		if(HashTable[i]!=NULL){
			/* リスト構造で連結しているデータを表示 */
			current_addr=HashTable[i];
			do{
				printf("-|%d|%d:%d:%s:%d|-",i,current_addr,current_addr->no,current_addr->name,current_addr->next_addr);
				current_addr=current_addr->next_addr;
			}while(current_addr!=NULL);
		}
		printf("\n");
	}
}

/* ハッシュ値の計算 */
int hash(int h)
{
	return h%HASH_SIZE;
}

/* データの追加 */
void add(void)
{
	struct character *p;	/* 入力 */
	struct character *q;	/* current */
	int i,j;
	int h;
	p=(struct character*)malloc(sizeof(*p));	/* 追加データのためのメモリを確保 */
	printf("NO＝");
	p->no=get_num();
	printf("名前＝");
	fgets(p->name,16,stdin);
	for(j=0;p->name[j]!='\n'&&j!=15;j++);
	p->name[j]='\0';	/* 改行コードを削除するための処理 */
	p->next_addr=NULL;	h=hash(p->no);
	if(HashTable[h]==NULL){
		/* HashTable[h]にまだデータが存在してなかったときの処理 */
		HashTable[h]=p;
	} else {
		/* HashTable[h]に既にデータが存在していたときの処理 */
		q=HashTable[h];
		while(q->next_addr!=NULL) {
			q=q->next_addr;
		}
		q->next_addr=p;
	}
	disp();
}

/* データの削除 */
int del(void)
{
	int i,h;
	struct character *current_addr,*before_addr,*head,*target;
	int point;
	disp();
	printf("NO＝");
	point=get_num();
	h=hash(point);
	if(HashTable[h]==NULL){
		printf("NOT FOUND.\n");
		return ERROR;
	}
	current_addr=HashTable[h]->next_addr;
	before_addr=HashTable[h];
	while(1){
		if(current_addr->no==point){
			if(before_addr==HashTable[h] && current_addr->next_addr==NULL){
				HashTable[h]=NULL;
			}else if(current_addr->next_addr==NULL){
				before_addr->next_addr=NULL;
			}else{
				before_addr->next_addr=current_addr->next_addr;
			}
			//printf("Found.\n");
			disp();
			return 0;
		}
		if(current_addr->next_addr==NULL)	break;
		before_addr=current_addr;
		current_addr=current_addr->next_addr;
	}
	printf("NOT FOUND.\n");
	return ERROR;
}

/* データの探索 */
int search(void)
{
	int i=0,h;
	struct character *current_addr,*head,*target;
	int point;
	printf("NO＝");
	point=get_num();
	h=hash(point);
	current_addr=HashTable[h];
	if((current_addr=HashTable[h])==NULL){
		printf("NOT FOUND.\n");
		return ERROR;
	}
	while(1){
		if(current_addr->no==point){
			printf("探索キー%dに対応するデータは%sです。\n",current_addr->no,current_addr->name);
			printf("-|%d|%d:%d:%s:%d|-\n",i,current_addr,current_addr->no,current_addr->name,current_addr->next_addr);
			printf("********************************************\n");
			disp();
			return 0;
		}
		if(current_addr->next_addr==NULL)	break;
		current_addr=current_addr->next_addr;
	}
	printf("NOT FOUND.\n");
	return ERROR;
}

/* メニュー */
int menu(void)
{
	int c;
	while(1){
		printf("1.表\示\n");	// 課題5と同様の理由で，"表"と"示"の間に"\"を挿入
		printf("2.追加\n");
		printf("3.削除\n");
		printf("4.探索\n");
		printf("5.終了\n");
		c=get_num();
		if(c>=1&&c<=5)	break;
		else	printf("1?5までの数字を入力してください\n");
	}
	switch(c){
		case 1:
			disp();
			break;
		case 2:
			add();
			break;
		case 3:
			del();
			break;
		case 4:
			search();
			break;
		case 5:
			return 1;
	}
	return 0;
}

int main(void)
{
	int i,end=0;
	/* ハッシュ表を初期化 */
	for(i=0;i<HASH_SIZE;i++)
		HashTable[i]=NULL;
	while(!end){
		end=menu();
	}
	return 0;
}
