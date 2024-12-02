#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

// 메시지 버퍼 구조체 정의
struct msg_buffer {
    long msg_type;          // 메시지 유형
    char msg_text[100];     // 메시지 텍스트
};

void sender(int msgid) {
    struct msg_buffer message;

    while (1) {
        printf("You: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);
        message.msg_text[strcspn(message.msg_text, "\n")] = '\0'; // 개행 제거

        if (strcmp(message.msg_text, "exit") == 0) {
            message.msg_type = 1;
            msgsnd(msgid, &message, sizeof(message.msg_text), 0);
            printf("Exiting chat...\n");
            break;
        }

        message.msg_type = 1;
        msgsnd(msgid, &message, sizeof(message.msg_text), 0); // 메시지 전송
    }
}

void receiver(int msgid) {
    struct msg_buffer message;

    while (1) {
        msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0); // 메시지 수신
        if (strcmp(message.msg_text, "exit") == 0) {
            printf("\nPeer has left the chat. Exiting...\n");
            break;
        }
        printf("\nPeer: %s\n", message.msg_text);
    }
}

int main() {
    key_t key = ftok("chatfile", 65); // 키 생성
    int msgid = msgget(key, 0666 | IPC_CREAT); // 메시지 큐 생성

    if (fork() == 0) { // 자식 프로세스: 메시지 수신
        receiver(msgid);
    } else { // 부모 프로세스: 메시지 전송
        sender(msgid);
        wait(NULL); // 자식 프로세스 종료 대기
        msgctl(msgid, IPC_RMID, NULL); // 메시지 큐 삭제
    }

    return 0;
}