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

void set_disp(data *database){
	printf("\033[1;1H");
	printf("\033[2J");
}

#endif
