/*
Aim
To write a program to implement readers and writers problem

Algorithm
1.Start
2.Initialize two semaphore mutex=1 and db=1 and rc,(Mutex controls the access to read count rc)
3.Create two threads one as Reader() another as Writer()
4.Reader Process:
Step 1: Get exclusive access to rc(lock Mutex)
Step 2: Increment rc by 1
Step 3: Get the exclusive access bd(lock bd)
Step 4: Release exclusive access to rc(unlock Mutex)
Step 5: Release exclusive access to rc(unlock Mutex)
Step 6: Read the data from database Step 7: Get the exclusive access to rc(lock mutex)
Step 8: Decrement rc by 1, if rc =0 this is the last reader.
Step 9: Release exclusive access to database(unlock mutex)
Step 10: Release exclusive access to rc(unlock mutex)
5.Stop
*/

#include<stdio.h>
int x=1,rc=0,readcount=1;
void p(int *a) {
    while(*a==0) {
        printf("busy wait");
    }
    *a=*a-1;
}
void v(int*b) {
    *b=*b+1;
}
void p1(int*c) {
    while(*c==0) {
        printf("busy wait");
    }
    *c=*c-1;
}

void v1(int*d) {
    *d=*d+1;
}

void reader() {
    int flag=1;
    while(flag==1) {
        p(&readcount);
        rc=rc+1;
        if(rc==1)
			p1(&x);
		v(&readcount);
		printf("\n reader is reading");
		p(&readcount);
		rc=rc-1;
		if(rc==0)
			v1(&x);
		v(&readcount);
		flag=0;
	}
}

void writer() {
	p1(&x);
	printf("\n writer is writing");
	v1(&x);
}

void main() {
	reader();
	writer();
	reader();
	writer();
}

/*
Output
 reader is reading
 writer is writing
 reader is reading
 writer is writing
*/