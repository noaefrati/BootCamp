/******************************************************************************* 
 * Description:                                                                *
 * Author: Noa Efrati                                                          *
 * Reviewer: Galit Vaknin                                                      *
 * Date: 26.01,2021                                                            *
 * Infinity Labs OL97                                                          *
 ******************************************************************************/
#include <signal.h>
#include <stdio.h>        /*   printf  */
#include <unistd.h>	      /*   sleep   */
#include "watchdog.h"     /*   WD API  */

#define UNUSED(X) (void)(X)

int main(int argc, char *argv[])
{
	int count = 0;
	watch_dog_params_t client = {0};
	
	UNUSED(argc);
	
	client.user_program_full_name = argv[0];
	client.wd_program_full_name = "./watchdog_exe.out" ;
	client.args = argv;
	client.init_wait_time = 8;
	client.user_signal_wait_time = 5;
	client.wd_signal_wait_time = 9;
	client.signal_missed_amt = 3;
	
	WatchDogStart(&client);
	printf("WD client after call start\n");
	
	while (count < 15)
	{
		printf("\nI'm Alive. iter (%d) \n", count);
		sleep(5);
		++count;
	}
	
	WatchDogStop(&client);
	printf("WD Ends \n");
	
	return 0;									
}

                              
