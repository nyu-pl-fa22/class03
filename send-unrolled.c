void send(int* to, int* from, int count) {
  do {
    *to++ = *from++; *to++ = *from++; 
    *to++ = *from++; *to++ = *from++; 
    *to++ = *from++; *to++ = *from++; 
    *to++ = *from++; *to++ = *from++; 
    count -= 8;
  } while (count > 0);
}
