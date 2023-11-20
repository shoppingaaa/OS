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

    qid=msgget(key,0777);
    
    m.mtype=1;
    m.pid=pid;
    strcpy(m.tip,"REQ from B.");
    
   msgsnd(qid,&m,mlen,0);    
   msgrcv(qid,&m,mlen,pid,0);
   printf("B.receive:A.pid=%d,tip=%s.\n",m.pid,m.tip);
   
   getchar();

   msgctl(qid,IPC_RMID,0);

}
 



 


    
     

 

