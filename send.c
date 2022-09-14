void send(int* to, int* from, int count) {
  do *to++ = *from++; 
  while (--count > 0);
}

/* Equivalent to:

void send(int* to, int* from, int count) {
  do {
   *to = *from;
   to = to + 1;
   from = from + 1;
   count = count - 1; 
  } while (count > 0);
}

*/
