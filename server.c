#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msg_mycs.h"

main()
{
	int i;
	
	extern cleanup();
	for(i=0;i<20;i++)
	 signal(i,cleanup);

	msgqid = msgget(MSGKEY,0777|IPC_CREAT);

	for(;msg.opcode!='q';)
	{
 	 printf("server pid= %d is ready (msgqid=%d)... \n",getpid(),msgqid);

	 msgrcv(msgqid,&msg,msgsize,1,0);
	 printf("server: receive from pid=%d\n",msg.source_pid);
         msg.result_msg[0]='1';
         switch(msg.opcode){
	 case '+':
		msg.result=msg.a+msg.b;
		break;

	 case '-':
		msg.result=msg.a-msg.b;
		break;

	 case '*':
		msg.result=msg.a*msg.b;
		break;
	 case '/':
		if(msg.b!=0)
	 	 msg.result=msg.a/msg.b;
                else
                 strcpy(msg.result_msg,"0. divide by 0.");
		break;
	 default:
                 strcpy(msg.result_msg,"0. exit by user.") ;
		break;
	 }

         if(msg.result_msg[0]=='1')
		printf("%.2f  %c %.2f = %.2f\n",msg.a,msg.opcode,msg.b,msg.result);
         else
	    printf("%s\n",msg.result_msg);

	 msg.mtype=msg.source_pid;
	 msg.source_pid=getpid();
	 msgsnd(msgqid,&msg,msgsize,0);
	}
        printf("server eixt by client pid=%d\n",msg.mtype);
}
cleanup()
{
	msgctl(msgqid,IPC_RMID,0);
	exit(0);
}  
