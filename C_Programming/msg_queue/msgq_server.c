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
	msgqbuf mbuf = { 0 };
	size_t buflen = 0;
	int msgflg = IPC_CREAT | 0666;
	key_t key = 12345;

	msgqid = msgget(key, msgflg);
	if (msgqid < 0) {
		die("msgget");
	}

	/* Request client for username */
	memset(&mbuf, 0, sizeof(mbuf));
	mbuf.mtype = MTYPE_FROM_SERVER;
	mbuf.mcmd = CMD_SEND_USERNAME;
	buflen = sizeof(mbuf.mcmd);
	status = msgsnd(msgqid, &mbuf, buflen, IPC_NOWAIT);
	if (status < 0) {
		die("msgsnd CMD_SEND_USERNAME failed");
	}

	memset(&mbuf, 0, sizeof(mbuf));
	status =
	    msgrcv(msgqid, &mbuf, (MAXBUFSIZE + sizeof(mbuf.mcmd)),
		   MTYPE_FROM_CLIENT, MSG_NOERROR);
	if (status < 0) {
		die("msgrcv failed");
	}

	if (mbuf.mcmd == CMD_USERNAME_ACK) {
		printf("Client Username: %s\n", mbuf.mtext);
	}

	/* Request client for password */
	memset(&mbuf, 0, sizeof(mbuf));
	mbuf.mtype = MTYPE_FROM_SERVER;
	mbuf.mcmd = CMD_SEND_PASSWORD;
	buflen = sizeof(mbuf.mcmd);
	status = msgsnd(msgqid, &mbuf, buflen, IPC_NOWAIT);
	if (status < 0) {
		die("msgsnd CMD_SEND_PASSWORD failed");
	}

	memset(&mbuf, 0, sizeof(mbuf));
	status =
	    msgrcv(msgqid, &mbuf, (MAXBUFSIZE + sizeof(mbuf.mcmd)),
		   MTYPE_FROM_CLIENT, MSG_NOERROR);
	if (status < 0) {
		die("msgrcv failed");
	}

	if (mbuf.mcmd == CMD_PASSWORD_ACK) {
		printf("Client Password: %s\n", mbuf.mtext);
	}

	/* Terminate the client */
	printf("\'CMD_CLIENT_EXIT\' command sending to client\n");
	memset(&mbuf, 0, sizeof(mbuf));
	mbuf.mtype = MTYPE_FROM_SERVER;
	mbuf.mcmd = CMD_CLIENT_EXIT;
	buflen = sizeof(mbuf.mcmd);
	status = msgsnd(msgqid, &mbuf, buflen, IPC_NOWAIT);
	if (status < 0) {
		die("msgsnd CMD_CLIENT_EXIT failed");
	}

	return 0;
}
