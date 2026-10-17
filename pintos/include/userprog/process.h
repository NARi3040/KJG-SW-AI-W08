#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

tid_t process_create_initd (const char *file_name);
tid_t process_fork (const char *name, struct intr_frame *if_);
int process_exec (void *f_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (struct thread *next);

/**
 * 사용자 프로그램이 exit(status)로 전달한 종료 상태 보관
 * 현재는 종료 메시지 출력(process.c의 process_exit())에 사용중이고
 */
struct exit_info {      
    int status;
};


#endif /* userprog/process.h */
