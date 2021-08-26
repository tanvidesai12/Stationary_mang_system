#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"implementation.h"
//login function
int login()
{
    char username[15];
    char password[12];
    int flag=0,i=0;
 
    printf("Enter your username:\n");
    scanf("%s",username);
 
    printf("Enter your password:\n");
	scanf("%s",password);
    if(strcmp(username,"admin")==0)//to check username
	{
        	if(strcmp(password,"doisy")==0)//to check password
		{
 
        		printf("\nWelcome...\nLogin Success!");
			flag=1;
		}
		else
		{
    			printf("\nWrong password");
		}
    	}
	else
	
   	 printf("\nUser doesn't exist");
	return flag;
}

//function to display products
void display_products(FILE *fp)
{
	int cnt=0;
	rewind(fp);
	products p;
	printf("\nThe product details are as follows\n");
	//printf("\n Prod_ID Prod_Name Category Sub_Category Price\n");
	while(fread(&p,sizeof(p),1,fp) == 1)
	{
		cnt++;
		printf("\n %d\t%s\t%s\t%s\t%f",p.prod_id,p.prod_name,p.category,p.sub_category,p.price);
	}
	if(cnt==0)
		printf("\nCannot display product details as the file is empty......");
}

//function for validation
int validation(char name[])
{
	int i,valid=1;
	for(i=0;name[i]!='\0';i++)
		{
			if((name[i]<97 || name[i]>122)&&(name[i]!=45 && name[i]!=95))
			{
				printf("Invalid input.Please enter in lowercase letters only.\n");
				valid=0;
				break;
			}
		}
	return valid;
}

//function for inserting products
int insert_products(FILE *fp,int pid)
{
	fseek(fp,0,SEEK_END);
	char choice;
	products p;
	int valid;
	
	do
	{
		p.prod_id=pid;
		do
		{
			printf("Enter the category:");
			scanf(" %s",p.category);
			valid=validation(p.category);
		}while(valid==0);
		do
		{
			printf("Enter the sub category:");
			scanf(" %s",p.sub_category);
			valid=validation(p.sub_category);
		}while(valid==0);
		do
		{
			printf("Enter the product name:");
			scanf(" %s",p.prod_name);
			valid=validation(p.prod_name);
		}while(valid==0);
		do
		{
			printf("Enter the price of the product:");
			scanf("%f",&p.price);
			if(p.price<=0)//check if -ve or zero
			printf("\nInvalid Input.Price should be greater than zero");
		}while(p.price<=0);
		fwrite(&p,sizeof(p),1,fp);
		printf("\nProducts added successfully!!");
		pid++;
		printf("\nDo you want to continue adding more products [Y/N]?");
		fflush(stdin);
		scanf(" %c",&choice);
		}while(choice=='Y'||choice=='y');
	return(pid);
}

//function for displaying bill
void display_bill(float total)
{	FILE *fpt;
	fpt=fopen("bill.txt","r");
	if(fpt==NULL)
	{
		printf("File does not exist.");
		exit(0);
	}
	char name[50];
	float price,ttl_price;
	int i,j,cnt=0,quantity;
	printf("\n\t ");
	for(i=0;i<50;i++)
		printf("=");
	printf("\n\t|Sr No.| Name of product | qty | price | Total-cost|");
	
	printf("\n\t|");
	for(i=0;i<50;i++)
		printf("=");
	
		while(fscanf(fpt,"%s %d %f %f",name,&quantity,&price,&ttl_price)!=EOF)
		{
			printf("\n\t|");
			printf("  %d\t %s\t\t    %d\t %.2f\t %.2f\t   ",++cnt,name,quantity,price,ttl_price);
			printf("|");
		}
	printf("\n\t ");
	for(i=0;i<50;i++)
		printf("=");
	printf("\n\t\tTotal amount:%f\n\t ",total);
	for(i=0;i<50;i++)
		printf("=");
	fclose(fpt);
}

//billing by using name		
void billing_name(FILE *fp)
{	
	FILE *fpt;
	fpt=fopen("bill.txt","w");
	char name[50];
	int quantity,found;
	rewind(fp);
	products p;
	float sum,total=0;
	char option;
	do
	{
		found=0;
		printf("\nEnter the name of the product:");
		scanf(" %s",name);
		rewind(fp);
		while(fread(&p,sizeof(p),1,fp) == 1)
		{
			if(strcmp(p.prod_name,name)==0)
			{
				found=1;
				do
				{
					printf("\nEnter the quantity:");
					scanf("%d",&quantity);
					if(quantity<=0)
					printf("\nInvalid Input.Quantity should be greater than zero\n");
				}while(quantity<=0);
				sum=p.price*quantity;
				printf("\nTotal cost of %s == %f",p.prod_name,sum);
				fprintf(fpt,"%s %d %f %f\n",p.prod_name,quantity,p.price,sum);
				total+=sum;
				break;
			}
						
		}
		if(found==0)
			printf("\nproduct not found");
		printf("\nDo you want to continue purchasing??[y/n]:");
		scanf(" %c",&option);		
	}while(option=='y'||option=='Y');
	printf("\nTotal cost==>%f\n",total);
	fclose(fpt);
	printf("The bill is :\n");
	display_bill(total);
}	

//billing by using product id	
void billing_id(FILE *fp)
{
	FILE *fpt;
	fpt=fopen("bill.txt","w");
	int id,found,quantity;
	products p;
	char option;
	float total=0,sum;
	display_products(fp);
	rewind(fp);
	do
	{
		found=0;
		printf("\nEnter the id of the product you want to purchase:");
		scanf("%d",&id);
		rewind(fp);
		while(fread(&p,sizeof(p),1,fp) == 1)
		{
			if(id==p.prod_id)
			{
				found=1;
				do
				{
					printf("\nEnter the quantity:");
					scanf("%d",&quantity);
					if(quantity<=0)
					printf("\nInvalid Input.Price should be greater than zero");
				}while(quantity<=0);
				sum=p.price*quantity;
				printf("Total cost of %s == %f",p.prod_name,sum);
				fprintf(fpt,"%s %d %f %f\n",p.prod_name,quantity,p.price,sum);
				total+=sum;
				break;
			}
						
		}
		if(found==0)
			printf("\nproduct not found");
		printf("\nDo you want to continue purchasing??[y/n]:");
		scanf(" %c",&option);		
	}while(option=='y'||option=='Y');
	fclose(fpt);
	printf("The bill is :\n");
	display_bill(total);					
}

//function for deleting products				
FILE * delete_products(FILE *fp,int *pid)
{
	products p;
	int id,found,last_id;
	FILE *ft;
	char option;
	do
	{	
		display_products(fp);
		printf("\nEnter the product id you want to delete.");
		scanf("%d",&id);
		fseek(fp,-sizeof(p),SEEK_END);
		fread(&p,sizeof(p),1,fp);
		last_id=p.prod_id;
		ft=fopen("TEMP.dat","wb");
		found=0;
		rewind(fp);
		while(fread(&p,sizeof(p),1,fp)==1)
		{
			if(p.prod_id != id)
			{
				fwrite(&p,sizeof(p),1,ft);
			}
			else
			{
				found=1;
				if(id==last_id)
				*pid=last_id;
			}
		}
		if(found==0)
		{
			printf("\n Product id  %d not found",id);
			break;
		}
		fclose(fp);
		fclose(ft);
		remove("details.dat");
		rename("TEMP.dat","details.dat");
		fp=fopen("details.dat","rb+");
		printf("\nProduct was deleted successfully!!");
		printf("\nDo you wish to delete another record?[Y/N]");
		fflush(stdin);
		scanf(" %c",&option);
	}while(option!='N' && option!='n');
	return fp;
}

//function for upating products
void update_products(FILE *fp)
{
	products p;
	int id,found,choice,valid;
	char option,new_name[40];
	float new_price;
	do
	{
		display_products(fp);
		printf("\nPlease enter the product id you want to modify");
		scanf("%d",&id);
		found=0;
		rewind(fp);
		while(fread(&p,sizeof(p),1,fp) == 1)
		{
			if(p.prod_id == id)
			{
				found = 1;
				printf("\nWhat do you want to update?\n1)Product Name\n2)Product Rate\n3)BOTH");
				scanf("%d",&choice);
				if(choice == 1)
				{
					do
					{
						printf("Enter the product name:");
						scanf(" %s",new_name);
						valid=validation(new_name);
					}while(valid==0);
					fseek(fp,-sizeof(p),SEEK_CUR);
					strcpy(p.prod_name,new_name);
					fwrite(&p,sizeof(p),1,fp);
					printf("\nrecord updated successfully!!");
					break;
				}
				else if(choice == 2)
				{
					do
					{
						printf("Enter the price of the product:");
						scanf("%f",&new_price);
						if(new_price<=0)
						printf("\nInvalid Input.Price should be greater than zero");
						
					}while(new_price<=0);
					fseek(fp,-sizeof(p),SEEK_CUR);
					p.price=new_price;
					fwrite(&p,sizeof(p),1,fp);
					printf("\nrecord updated successfully!!");
					break;
				}
				else if(choice==3)
				{
					do
					{
						printf("Enter the product name:");
						scanf(" %s",new_name);
						valid=validation(new_name);
					}while(valid==0);
					do
					{
						printf("Enter the price of the product:");
						scanf("%f",&new_price);
						if(new_price<=0)
						printf("\nInvalid Input.Price should be greater than zero");
					}while(new_price<=0);
					fseek(fp,-sizeof(p),SEEK_CUR);
					strcpy(p.prod_name,new_name);
					p.price=new_price;
					fwrite(&p,sizeof(p),1,fp);
					printf("\nrecord updated successfully!!");
					break;
				}
				else
					printf("\nYou have entered an invalid choice.");
			
			}

		}
		if(found == 0)
		printf("\nThe product id %d could not be found",id);
		printf("\nDo you wish to modifiy another product?[Y/N]\n");
		scanf(" %c",&option);

	}while(option!='N' && option!='n');
}

		





















