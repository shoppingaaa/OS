#define MSGKEY 1183

struct msgform {
	long mtype;
	int source_pid;	
	double a,b;
	char opcode;
	double result;
	char result_msg[128];
}msg;
int msgsize=sizeof(struct msgform)-sizeof(long);
int msgqid;