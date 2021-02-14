#include <stdio.h>

void foo(int, int i =3, float = 4);
int main()
{
	foo(3);
	foo(6,5);
	foo(4, 7, 8.7);
	
	return 0;
}
void foo(int a, int b, float c)
{
	printf("a = %d\n",a);
	printf("b = %d\n", b);
	printf("c = %f\n", c);
}
//main:
//       push    rbp
//       mov     rbp, rsp
//       movss   xmm0, DWORD PTR .LC0[rip]
//       mov     esi, 3
//       mov     edi, 3
//       call    foo(int, int, float)
//       movss   xmm0, DWORD PTR .LC0[rip]
//       mov     esi, 5
//       mov     edi, 6
//       call    foo(int, int, float)
//       movss   xmm0, DWORD PTR .LC1[rip]
//       mov     esi, 7
//       mov     edi, 4
//       call    foo(int, int, float)
//       mov     eax, 0
//       pop     rbp
//		 ret
//.LC2:
// 	     .string "hi!"
//foo(int, int, float):
//	      push    rbp
//        mov     rbp, rsp
//		  sub     rsp, 16
// 	      mov     DWORD PTR [rbp-4], edi
// 	      mov     DWORD PTR [rbp-8], esi
//        movss   DWORD PTR [rbp-12], xmm0
//        mov     edi, OFFSET FLAT:.LC2
//        call    puts
//        nop
//        leave
//        ret
//.LC0:
//		  .long   1082130432
//.LC1:
//        .long   1091253043
 
