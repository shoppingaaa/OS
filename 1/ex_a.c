#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
 
#define key 85

struct msg{
  long mtype;
  int  pid;
  char tip[128];
};
 
int mlen=sizeof(struct msg) -sizeof(long);

int main()
{

    int pid= getpid();
    struct msg m;
    int qid;

    qid=msgget(key,0777|IPC_CREAT);
    
   msgrcv(qid,&m,mlen,1,0);
   printf("A.receive:B.pid=%d,tip=%s.\n",m.pid,m.tip);
   
   m.mtype=m.pid;
   m.pid=pid;
   strcpy(m.tip,"REP from A.");

   msgsnd(qid,&m,mlen,0);

   getchar();

   msgctl(qid,IPC_RMID,0);

}
 



 


    
     

 

