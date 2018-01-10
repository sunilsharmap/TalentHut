#include "msg_queue.h"

void die(char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char *argv[])
{
	int status = 0;
	int msgqid = 0;
	size_t buflen = 0;
	msgqbuf mbuf = { 0 };
	int msgflg = IPC_CREAT | 0666;
	key_t key = 12345;

	msgqid = msgget(key, msgflg);
	if (msgqid < 0) {
		die("msgget");
	}
	while (1) {
		/* Request client for username */
		memset(&mbuf, 0, sizeof(mbuf));
		status =
		    msgrcv(msgqid, &mbuf, MAXBUFSIZE, MTYPE_FROM_SERVER,
			   MSG_NOERROR);
		if (status < 0) {
			die("msgrcv failed");
		}

		if (mbuf.mcmd == CMD_SEND_USERNAME) {
			memset(&mbuf, 0, MAXBUFSIZE);
			printf("Enter the Username:");
			scanf("%s", mbuf.mtext);
			mbuf.mtype = MTYPE_FROM_CLIENT;
			mbuf.mcmd = CMD_USERNAME_ACK;
			buflen = (strlen(mbuf.mtext) + 1) + sizeof(mbuf.mcmd);
			status = msgsnd(msgqid, &mbuf, buflen, IPC_NOWAIT);
			if (status < 0) {
				die("msgsnd failed");
			}
		} else if (mbuf.mcmd == CMD_SEND_PASSWORD) {
			memset(&mbuf, 0, MAXBUFSIZE);
			printf("Enter the Password:");
			scanf("%s", mbuf.mtext);
			mbuf.mtype = MTYPE_FROM_CLIENT;
			mbuf.mcmd = CMD_PASSWORD_ACK;
			buflen = (strlen(mbuf.mtext) + 1) + sizeof(mbuf.mcmd);
			status = msgsnd(msgqid, &mbuf, buflen, IPC_NOWAIT);
			if (status < 0) {
				die("msgsnd failed");
			}
		}
	}
	return 0;
}
