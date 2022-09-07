#include <stdio.h>
#include <stdlib.h>

typedef struct {
   int age;
   void (*setAge)(void *, int);
   int (*getAge)(void *);
} Fish;

void setAge(void *self, int X) {
   ((Fish *)self)->age = X;
}

int getAge(void *self) {
   return ((Fish *)self)->age;
}

Fish NEW_Fish() {
   Fish X;
   X.setAge = &setAge;
   X.getAge = &getAge;
   return X;
}

int main(int argc, char *argv[]) {
   Fish f = NEW_Fish();
   f.setAge(&f, 3);
   int X = f.getAge(&f);

   printf("%d\n", f.age);
   printf("%d\n", X);
   printf("%lu\n", sizeof(f));

   return 0;
}

