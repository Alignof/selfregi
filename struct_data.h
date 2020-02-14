#ifndef HEADERFILE
#define HEADERFILE

typedef struct{
	int ID;
	int month;
	int date;
	int price;
	int stock;
	char name[30];
}data;

typedef struct{
	int Noguchi;
	int Higuchi;
	int Yukichi;
	//coins[6]={500,100,50,10,5,1};
	int coins[6];
}moneys;

typedef struct{
	int num;
	data *product;
}cart_data;

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

#endif
