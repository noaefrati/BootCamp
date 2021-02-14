int is_angram(char *s1, char *s2)
{
    int lut[ASCII] = {0};
   ab
    while (*s1 != '\0')
    {
        int ind = (int) *s1;
        ++lut[ind];
        ++s1;
    }
   aa
    while (*s2 != '\0')
    {
        int ind = (int) *s2;
        if (lut[ind] == 0)
        {
            return 0;
        }
      
        --lut[ind];
      
        ++s2;
    }
    
    return 1;
}    
    "abs" , "sba"
    1. int lut[ascii]
    2. loop over first string mark with "1" each char as the match place in lut
    3. loop over second loop if the current char in the lut is zero - then break and return 0.
    4. return 1 
}

#define WORD 8


void *memcpy(void *dest, const void *src, size_t n)
{
    int res = 0;
    
    assert(src);
    
    // size_t i = 300;
    // void *src = & i;
    //
    // src -> void * | address on the stack
    // (size_t *)src -> size_t * | address on the stack
    // *(size_t*)src -> size_t * | 300
    
    res = src % WORD;
  
    for (; res > 0; --res)
    {
        *(char *)dest++ = *(char *)src++;
    }
   
    while (n >= WORD)
    {
         *(size_t *)dest++ = *(size_t *)src++;
         n -= WORD;
    }
    
    
     for (; n > 0; --n)
     {
         *(char *)dest++ = *(char *)src++;
     }
   
    
    return dest;
   
}o
