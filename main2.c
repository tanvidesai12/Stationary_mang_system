#include<stdio.h>
#include<stdlib.h>
#include"implementation.h"
void main()
{
	int pid,ch;
	FILE *fp;
	products p;
	printf("\033[1;35m");	
	printf("\n***********************************************************************************************************\n");
	printf("\n							WELCOME TO STATIONARY STORE		       			\n");
	printf("\n*******************************************************************************************************\n");
	printf("\033[0m");
	fp=fopen("details.dat","rb+");
	if(fp==NULL)
	{	
		pid=1;
		fp=fopen("details.dat","wb+");
		
		
		if(fp==NULL)
		{
			printf("error");
			exit(0);
		}
	}
	else
	{
		fseek(fp,-sizeof(p),SEEK_END);
		fread(&p,sizeof(p),1,fp);
		pid=p.prod_id;
		pid++;
	}
	int option;
	if(login()==1)
	{
		do
		{
			printf("\033[1;35m");
			printf("\n\nKindly choose any option from below:\n1.Display Products.\n2.Add a product.\n3.Billing.\n4.Update a product.\n5.Delete a product.\n6.Exit\nEnter your option:");printf("\033[0m");
			scanf("%d",&option);
			switch(option)
			{
				case 1: display_products(fp);
					break;
				case 2: pid=insert_products(fp,pid);
					
					break;

				case 3:printf("\n1.Search by product name\n2.Search by product id\nEnter your choice");
					scanf("%d",&ch);
					if(ch==1)
						billing_name(fp);
					else if(ch==2)
						billing_id(fp);
					else printf("\nInvalid option.Kindly enter a number either 1 or 2");
					break;
				
				
				case 4: update_products(fp);
					
					break;

				case 5: fp = delete_products(fp,&pid);
					break;
		
				case 6: fclose(fp);
					
					break;
				default: printf("\nOops!!You have entered invalid option.Kindly enter a number between 1 to 6.");
			}
		}while(option!=6);
	}
}
