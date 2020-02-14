/**
 * @date		2019 12/24 - 2020 02/14
 * @author		Takana Norimasa <j17423@kisarazu.kosen-ac.jp> 
 * @brief		self register
 * @repository		https://github.com/Takana-Norimasa/selfregi
 * @license		https://opensource.org/licenses/mit-license.php MIT License
 */ 

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include"struct_data.h"
#define DATASIZE 100

void data_read(data *database,moneys *money,int *session_id){
	int i;
	int id;
	int key=0;
	int start=0;
	FILE *fp;
	char tmp[DATASIZE];
	char *filepath="data/product_data.csv";

	if((fp=fopen(filepath,"r"))==NULL){
		printf("file open failed.\n"); exit(EXIT_FAILURE);	
	}

	fscanf(fp,"%d\n",session_id);
	fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d\n",&money->Yukichi,&money->Higuchi,&money->Noguchi,&money->coins[0],&money->coins[1],&money->coins[2],&money->coins[3],&money->coins[4],&money->coins[5]);

	for(i=0;i<DATASIZE;i++){
		fscanf(fp,"%d,%d,%d,%d,%d,%s\n",&database[i].ID,&database[i].month,&database[i].date,&database[i].price,&database[i].stock,database[i].name);
	}

	fclose(fp);
}

void welcome(int *phase){
	printf("\033[1;1H");
	printf("\033[2J");
	printf("Welcome to selfregi!!!!\n");
	//show some alias
	printf("return Enter key>");
	while(getchar()!='\n');
	(*phase)++;
}

void setup(data *database,moneys *money,int *session_id){
	data_read(database,money,session_id);
}

int select_product(int *phase,data *database,cart_data *cart){
	int i,j;
	int id;
	int key;
	int page=0;
	int count=0;
	int cart_index=0;
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

		do{
			printf("back page:1 exit:2 next page:3 add product to cart:4 show cart:5\n");
			printf("[ <-prev:1 exit:2 next:3-> ]>>>");
			scanf("%d",&key);
		}while(!(key<=5));

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
				do{
					printf("Input product ID>>>");
					scanf("%d",&id);
				}while(!(id<DATASIZE));

				cart[cart_index].product=&database[id];
				printf("How many do you buy it?>>>");
				scanf("%d",&(cart[cart_index].num));
				cart_index++;
				break;
			case 5:
				for(i=0;i<cart_index;i++){
					printf("name:%s x%d\n",cart[i].product->name,cart[i].num);
				}
				while(getchar()!='\n');
				break;
		}
		if(is_exit) break;
	}

	while(getchar()!='\n');
	(*phase)++;

	return cart_index;
}

void bill(int *phase, data *database, cart_data *cart, int cart_size, moneys *money,int *session_id){
	int i;
	int tmp_price=0;
	int sum_price=0;
	char yn;
	time_t t;
	FILE *fp;
	char date[64];
	char *sales_log="data/sales_log.csv";
	char *product_data="data/product_data.csv";

	printf("\033[1;1H");
	printf("\033[2J");

	printf("<<cart list>>\n");
	for(i=0;i<cart_size;i++){
		printf("%s %d x%d\t|%d\n",cart[i].product->name,cart[i].product->price,cart[i].num, (cart[i].product->price)*(cart[i].num));
		sum_price+=(cart[i].product->price)*(cart[i].num);
	}
	printf("----------------------------------------------------------------------\n");
	printf("\t   sum\t|%d\n",sum_price);

	printf("Will you buy it?[y/n]>>>");
	scanf("%c",&yn);

	if(yn=='y'){
		tmp_price=sum_price;

		//bill
		money->Yukichi-=tmp_price/10000;
		tmp_price-=(tmp_price/10000)*10000;
		money->Higuchi-=tmp_price/5000;
		tmp_price-=(tmp_price/5000)*5000;
		money->Noguchi-=tmp_price/1000;
		tmp_price-=(tmp_price/1000)*1000;

		//coin
		money->coins[0]-=tmp_price/500;
		tmp_price-=(tmp_price/500)*500;
		money->coins[1]-=tmp_price/100;
		tmp_price-=(tmp_price/100)*100;
		money->coins[2]-=tmp_price/50;
		tmp_price-=(tmp_price/50)*50;
		money->coins[3]-=tmp_price/10;
		tmp_price-=(tmp_price/10)*10;
		money->coins[4]-=tmp_price/5;
		tmp_price-=(tmp_price/5)*5;
		money->coins[5]-=tmp_price/1;
		tmp_price-=(tmp_price/1)*1;

		//sales_log open
		if((fp=fopen(sales_log,"a"))==NULL){
			printf("file open failed.\n");
			exit(EXIT_FAILURE);	
		}

		t=time(NULL);
		strftime(date,sizeof(date),"%Y/%m/%d %a %H:%M:%S", localtime(&t));

		fprintf(fp,"No.%d %s\n",*session_id,date);
		for(i=0;i<cart_size;i++){
			fprintf(fp,"\t%s %s x %d\n",date,cart[i].product->name,cart[i].num);
		}
		fclose(fp);

		//product_data open
		if((fp=fopen(product_data,"w+"))==NULL){
			printf("file open failed.\n");
			exit(EXIT_FAILURE);	
		}

		fprintf(fp,"%d\n",*session_id+1);
		fprintf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d\n",money->Yukichi,money->Higuchi,money->Noguchi,money->coins[0],money->coins[1],money->coins[2],money->coins[3],money->coins[4],money->coins[5]);

		for(i=0;i<DATASIZE;i++){
			fprintf(fp,"%d,%d,%d,%d,%d,%s\n",database[i].ID,database[i].month,database[i].date,database[i].price,database[i].stock,database[i].name);
		}

		fclose(fp);

		printf("Thank you!\n");
		(*phase)++;
	}else{
		(*phase)=1;
	}

}

void phase_manager(data *database,cart_data *cart,moneys *money,int *session_id){
	int phase=0;
	int cart_size;
	while(1){
		switch(phase){
			case 0:
				welcome(&phase);
				break;
			case 1:
				cart_size=select_product(&phase,database,cart);
				break;
			case 2:
				bill(&phase,database,cart,cart_size,money,session_id);
				break;
			case 3:
				return;
				break;
		}
	}
}

int main(void){
	int session_id;
	time_t now;
	moneys money;
	data database[DATASIZE];
	cart_data cart[DATASIZE];

	setup(database,&money,&session_id);
	phase_manager(database,cart,&money,&session_id);

	return 0;
}

