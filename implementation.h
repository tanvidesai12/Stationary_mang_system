struct product_details
{
	char category[50],sub_category[50],prod_name[50];
	int prod_id;
	float  price;
};
typedef struct product_details products;

int login();
void display_products(FILE *fp);
int validation(char name[]);
int insert_products(FILE *fp,int pid);
void billing_name(FILE *fp);
void display_bill(float);
void billing_id(FILE *fp);
FILE * delete_products(FILE *fp,int *pid);
void update_products(FILE *fp);
