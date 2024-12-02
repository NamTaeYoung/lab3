#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("msgqueue", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    pid_t pid = fork();

    if (pid == 0) { // 자식 프로세스
        struct msg_buffer message;
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0); // 메시지 받기
        printf("Child: Received Message: %s\n", message.msg_text);
    } else if (pid > 0) { // 부모 프로세스
        struct msg_buffer message;
        message.msg_type = 1; // 메시지 유형
        strcpy(message.msg_text, "Hello from Parent Process!");
        msgsnd(msgid, &message, sizeof(message.msg_text), 0); // 메시지 전송
        printf("Parent: Sent Message: %s\n", message.msg_text);

        wait(NULL); // 자식 프로세스 종료 대기

        msgctl(msgid, IPC_RMID, NULL); // 메시지 큐 삭제
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}