#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"struct_data.h"
#define DATASIZE 100

void data_read(data *database){
	int i;
	int id;
	int key=0;
	int start=0;
	FILE *fp;
	char tmp[DATASIZE];
	char *filepath="data/product_data.csv";

	if((fp=fopen(filepath,"r"))==NULL){
		printf("file open failed.\n");
		exit(EXIT_FAILURE);	
	}

	for(i=0;i<DATASIZE;i++){
		fscanf(fp,"%d,%d,%d,%d,%d,%s\n",&database[i].ID,&database[i].month,&database[i].date,&database[i].price,&database[i].stock,database[i].name);
	}

	fclose(fp);
}

void data_write(data *database){
	int i;
	int id;
	int key=0;
	int start=0;
	FILE *fp;
	char tmp[DATASIZE];
	char *filepath="data/product_data.csv";

	if((fp=fopen(filepath,"w"))==NULL){
		printf("file open failed.\n");
		exit(EXIT_FAILURE);	
	}

	for(i=0;i<DATASIZE;i++){
		fprintf(fp,"%d,%d,%d,%d,%d,%s\n",database[i].ID,database[i].month,database[i].date,database[i].price,database[i].stock,database[i].name);
	}

	fclose(fp);
}

void welcome(){
	printf("\033[1;1H");
	printf("\033[2J");
	printf("Welcome to management console.\n");
	//show some alias
	printf("return Enter key>");
	while(getchar()!='\n');
}

void setup(data *database){
	data_read(database);
}


void modify(data *database,int id){
	int tmp;
	char key;
	char name_tmp[100];
	
	printf("What do you want to modify?[N:name P:price S:stock]>>>");
	getchar();
	scanf("%c",&key);

	switch(key){
		case 'N':
			printf("Enter new name[now:%s]>>>",database[id].name);
			scanf("%s",name_tmp);
			strcpy(database[id].name,name_tmp);
			break;
		case 'P':
			printf("Enter new price[now:%d]>>>",database[id].price);
			scanf("%d",&tmp);
			database[id].price=tmp;
			break;
		case 'S':
			printf("Enter new stock[now:%d]>>>",database[id].stock);
			scanf("%d",&tmp);
			database[id].stock=tmp;
			break;
	}
	printf("Modified.\n");
}

void product_management(data *database){
	int i,j;
	int id;
	int key;
	int page=0;
	int count=0;
	int discount_value=0;
	int point_x[6]={1,10,20,30,40,50};
	int point_y[5]={1,30,60,90,120};
	char is_exit=0;
	const int row=4;
	const int column=5;

	while(1){
		printf("\033[1;1H");
		printf("\033[2J");

		count=row*column*page;
		for(i=0;i<row;i++){
			for(j=0;j<column;j++){
				if(count<DATASIZE){
					printf("\033[%d;%dH",point_x[i],point_y[j]);
					printf("------Name:%s------",database[count].name);
					printf("\033[%d;%dH",point_x[i]+1,point_y[j]);
					printf("\tID:%d",database[count].ID);
					printf("\033[%d;%dH",point_x[i]+2,point_y[j]);
					printf("\tprice:%d",database[count].price);
					printf("\033[%d;%dH",point_x[i]+3,point_y[j]);
					printf("\tstock:%d",database[count].stock);
					printf("\033[%d;%dH",point_x[i]+4,point_y[j]);
					printf("\tdate:%2d/%2d",database[count].month,database[count].date);

					count++;
				}
			}
		}

		printf("\n\n");
		printf("back page:1 exit:2 next page:3 modify data:4 sale:5\n");
		printf("[ <-prev:1 exit:2 next:3-> ]>>>");
		scanf("%d",&key);

		switch(key){
			case 1:
				if(page>0) page--;
				break;
			case 2:
				is_exit=1;
				break;
			case 3:
				if(page<DATASIZE/(row*column)) page++;
				break;
			case 4:
				printf("Input product ID>>>");
				scanf("%d",&id);
				modify(database,id-1);
				break;
			case 5:
				printf("What discount[n\%OFF]>>>");
				scanf("%d",&discount_value);
				for(i=0;i<DATASIZE;i++){
					printf("before:%d\n",database[i].price);
					database[i].price*=(1-(discount_value/100));
					printf("after:%d\n",database[i].price);
				}
				break;
		}
		if(is_exit) break;
	}

	printf("Thank you.\n");
}

int main(void){
	int mode;
	time_t now;
	data database[DATASIZE];
	cart_data cart[DATASIZE];

	setup(database);
	welcome();

	product_management(database);

	data_write(database);
	return 0;
}
