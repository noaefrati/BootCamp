/*******************************************************************************
  Description: explore memory mapping
  Auther: Noa
  Reviewer: 

  SP - memory mapping
  
  Inbfinity Labs OL97
*******************************************************************************/

#include <stdlib.h>
/*text*/
static void stat_fun1() /*401196*/
{

}
static void stat_fun2() /*4011a1*/
{

}
static void stat_fun3() /*4011ac*/
{

}
static void stat_fun4() /*4011b7*/
{

}
static void stat_fun5() /*4011c2*/
{

}
void extern_fun1() /*4011f9*/
{

}
void extern_fun2() /*4011ee*/
{

}
void extern_fun3() /*4011e3*/
{

}
void extern_fun4() /*4011d8*/
{

}
void extern_fun5() /*4011cd*/
{

}

/*data*/
int global_1 = 1; /*404048*/
int global_2 = 1; /*40404c*/
int global_3 = 1; /*404050*/
int global_4 = 1; /*404054*/
int global_5 = 1; /*404058*/

int const global_const_1 = 1; /*402004*/
int const global_const_2 = global_const_1; /*402008*/
int const global_const_3 = 3; /*40200c*/
int const global_const_4 = 4; /*402010*/
int const global_const_5 = 5; /*402014*/

static int static_global_1 = 1; /*40205c*/
static int static_global_2 = 2; /*402060*/
static int static_global_3 = 3; /*402064*/
static int static_global_4 = 4; /*402068*/
static int static_global_5 = 5; /*40206c*/

 /*BSS*/
int global_zero_1 = 0; /*404088*/
int global_zero_2 = 0; /*40408c*/
int global_zero_3 = 0; /*404090*/
int global_zero_4 = 0; /*404094*/
int global_zero_5 = 0; /*404098*/

int global_not_init_1; /*4040a0*/
int global_not_init_2; /*4040ac*/
int global_not_init_3; /*40409c*/
int global_not_init_4; /*4040a8*/
int global_not_init_5; /*4040a4*/



int main(int argc, char **argv, char **envp)
{
	/*data*/
	static int static_local_1 = 1; /*&static_local_1 = (int *) 0x555555558038*/
	static int static_local_2 = 1; /*&static_local_2 = (int *) 0x55555555803c*/
	static int static_local_3 = 1; /*&static_local_3 = (int *) 0x555555558040*/
	static int static_local_4 = 1; /*&static_local_4 = (int *) 0x555555558044*/
	static int static_local_5 = 1; /*&static_local_5 = (int *) 0x555555558048*/
	
	/*heap*/			      /*lvalue*/	     /*rvalue*/
	void *heap1 = malloc(10);         /*7fffffffdf30*/         /*4052a0*/
	void *heap2 = malloc(10);         /*7fffffffdf38*/         /*4052c0*/
	void *heap3 = malloc(10);    	   /*7fffffffdf40*/         /*4052e0*/
	void *heap4 = calloc(10, 1);	   /*7fffffffdf48*/         /*405300*/
	void *heap5 = calloc(10, 1);      /*7fffffffdf50*/         /*405320*/
	
	/*stack*/                                      
	
	int const const_local1 = 1;             /*7fffffffdf14*/    
	int const const_local2 = const_local1;  /*7fffffffdf18*/
	int const const_local3 = 3; 		 /*7fffffffdf1c*/    
	int const const_local4 = 4;            /*7fffffffdf20*/     
	int const const_local5 = 5;            /*7fffffffdf24*/   
	
	
	int local1 = 1;       /*7fffffffdf10*/
	int local2 = local1;  /*7fffffffdf28*/
	char local3 = 2;      /*7fffffffdf0f*/
	float local4 = 4.4;   /*7fffffffdf2c*/
	int *local5 = &local1; /*7fffffffdf58*/
	
	int local_uninit1;
	int local_uninit2;
	int local_uninit3;
	int local_uninit4;
	int local_uninit5;
	
	int local_const_uninit1;
	int local_const_uninit2;
	int local_const_uninit3;
	int local_const_uninit4;
	int local_const_uninit5;
	
				 /*lvalue*/	     /*rvalue*/	
	char *str1 = "1";    /*7fffffffdf60*/      /*402018*/
	char *str2 = "1";    /*7fffffffdf68*/      /*402018*/
	char *str3 = "2";    /*7fffffffdf70*/      /*40201a*/
	char *str4 = "2";    /*7fffffffdf78*/      /*40201a*/
	char *str5 = "3";    /*7fffffffdf80*/      /*40201c*/
	
	/* ??? Kernel ??? */        /*rvalue*/
	/*argv[0]*/              /*7fffffffe3dd*/
	/*argv[1]*/              /*7fffffffe3ff*/
	/*argv[2]*/              /*7fffffffe404*/
	/*argv[3]*/              /*7fffffffe409*/
	/*argv[4]*/              /*7fffffffe40e*/
	
	/* envp[0]*/             /*7fffffffe413*/
	/* envp[1]*/             /*7fffffffe423*/
	/* envp[2]*/             /*7fffffffe47d*/
	/* envp[3]*/             /*7fffffffe490*/
	/* envp[4]*/             /*7fffffffe4a4*/
	
	free(heap1);
	free(heap2);
	free(heap3);
	free(heap4);
	free(heap5);
}



