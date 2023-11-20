#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_mycs.h"
main()
{
	struct msgform msg;
	int pid;
	
	msgqid = msgget(MSGKEY,0777);
        
        pid=getpid();
	for(;msg.opcode!='q';){
         printf("a=");
	 scanf("%lf",&msg.a);
   
         printf("b=");
	 scanf("%lf",&msg.b);
   
         printf("opcode=(+,-,*,/,q for EXIT)");

	msg.opcode=getchar();
	while(msg.opcode=='\n')msg.opcode=getchar();
         
        if(msg.opcode=='+'||msg.opcode=='-'||'*'==msg.opcode ||
                '/'==msg.opcode||'q'==msg.opcode)
         { 
          msg.source_pid=pid;
          msg.mtype=1;
	 
	  msg.result_msg[0]=0;
	  msgsnd(msgqid,&msg,msgsize,0);
	  msgrcv(msgqid,&msg,msgsize,pid,0);
	  
	  printf("client: receive from pid=%d\n",msg.source_pid);
         
          if(msg.result_msg[0]=='1')
		printf("%.2f  %c %.2f = %.2f\n",msg.a,msg.opcode,msg.b,msg.result);
	  else
	    printf("%s\n",msg.result_msg);
         

         }
        }
}
  
