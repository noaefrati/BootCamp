
#ifndef __TEST_UTILLS_H_YIFAT_OL97_ILRD__
#define __TEST_UTILLS_H_YIFAT_OL97_ILRD__

#include <stdio.h>/*printf*/

#define RED     "\033[31m"       /* Red         */
#define GREEN   "\033[32m"      /* Green       */
#define YELLOW  "\033[33m"     /* Yellow      */
#define MAGENTA "\033[35m"      /* Magenta */
#define DEF   "\033[0m"       /*  Reset color*/

int success_counter = 0;

#define TEST(name, real, expected) (real == expected) ? \
++success_counter :printf(RED "%s, FAILED on line %d.\n" DEF, name, __LINE__)

#define CHECK(name, real, expected) (real == expected) ? \
printf(GREEN "%s, SUCESS all tests.\n" DEF, name) :\
printf(YELLOW"%s, FAILED in %d tests.\n" DEF, name, (expected - real))

 
#define RESET() (success_counter = 0)


#endif   /* __TEST_UTILLS_H_YIFAT_OL97_ILRD__ */



