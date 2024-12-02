#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 테스트 문장 배열
const char *sentences[] = {
    "The quick brown fox jumps over the lazy dog.",
    "Practice makes perfect.",
    "Hello, world!",
    "Typing speed matters.",
    "C programming is fun!"
};

int main() {
    int num_sentences = sizeof(sentences) / sizeof(sentences[0]);
    int total_characters = 0; // 총 타이핑한 문자 수
    int total_errors = 0;     // 총 오타 수
    char input[256];          // 사용자 입력 저장
    time_t start_time, end_time;

    printf("타자 연습 프로그램에 오신 것을 환영합니다!\n");
    printf("총 %d개의 문장을 입력해야 합니다.\n", num_sentences);

    // 타이핑 연습 시작
    time(&start_time); // 시작 시간 기록

    for (int i = 0; i < num_sentences; i++) {
        printf("\n문장을 입력하세요:\n%s\n", sentences[i]);

        // 사용자 입력
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // 개행 문자 제거

        // 비교 및 오타 확인
        int sentence_length = strlen(sentences[i]);
        total_characters += sentence_length;

        int errors = 0;
        for (int j = 0; j < sentence_length; j++) {
            if (j >= strlen(input) || input[j] != sentences[i][j]) {
                errors++;
            }
        }
        total_errors += errors;

        printf("오타 개수: %d\n", errors);
    }

    time(&end_time); // 종료 시간 기록

    // 총 소요 시간 계산
    double elapsed_time = difftime(end_time, start_time) / 60.0; // 분 단위 시간

    // WPM 계산
    double wpm = (total_characters / 5.0) / elapsed_time;

    printf("\n--- 결과 ---\n");
    printf("총 오타 수: %d\n", total_errors);
    printf("평균 분당 타자수(WPM): %.2f\n", wpm);

    return 0;
}
