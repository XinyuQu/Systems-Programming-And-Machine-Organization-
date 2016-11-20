#include "sh61.h"

#include <string.h>

#include <errno.h>

#include <sys/stat.h>

#include <sys/wait.h>

 

//in COMAND, have a POINTER// INT that tells me what i was doing before... and stuff....

 

 

 

// struct command

//    Data structure describing a command. Add your own stuff.

 

typedef struct command command;

struct command {

    int argc;      // number of arguments

    char** argv;   // arguments, terminated by NULL

    pid_t pid;     // process ID running this command, -1 if none

    int background; //if see &

    struct command *next;

    struct command *down;

    struct command *up;

    struct command *prev;

    int conditional_and;

    int conditional_or;

    int redirection;

    int has_pipe;

    int in_fd;

   int out_fd;

    int is_cd;

    char* redirection_info;

    char* redirection_file;

    char* cd_dir;

 

 

};

 

 

// command_alloc()

//    Allocate and return a new command structure.

 

static command* command_alloc(void) {

 

    command* c = (command*) malloc(sizeof(command));

    c->argc = 0;

    c->argv = NULL;

    c->pid = -1;

    c->background = 0; //if see &

    c->next= c->prev = c->down = c->up = NULL;

    c->conditional_and = c->conditional_or =

        c->in_fd = c->out_fd = c->redirection = c->is_cd = 0;

    c->redirection_file = c->redirection_info = c->cd_dir = NULL;

 

 

    return c;

}

 

 

// command_free(c)

//    Free command structure `c`, including all its words.

 

static void command_free(command* c) {

    for (int i = 0; i != c->argc; ++i)

        free(c->argv[i]);

    free(c->argv);

    free(c);

}

 

 

// command_append_arg(c, word)

//    Add `word` as an argument to command `c`. This increments `c->argc`

//    and augments `c->argv`.

 

 

static void command_append_arg(command* c, char* word) {

    c->argv = (char**) realloc(c->argv, sizeof(char*) * (c->argc + 2));

    c->argv[c->argc] = word;

    c->argv[c->argc + 1] = NULL;

    ++c->argc;

}

 

 

// COMMAND EVALUATION

 

// start_command(c, pgid)

//    Start the single command indicated by `c`. Sets `c->pid` to the child

//    process running the command, and returns `c->pid`.

//

//    PART 1: Fork a child process and run the command using `execvp`.

//    PART 5: Set up a pipeline if appropriate. This may require creating a

//       new pipe (`pipe` system call), and/or replacing the child process's

//       standard input/output with parts of the pipe (`dup2` and `close`).

//       Draw pictures!

//    PART 7: Handle redirections.

//    PART 8: The child process should be in the process group `pgid`, or

//       its own process group (if `pgid == 0`). To avoid race conditions,

//       this will require TWO calls to `setpgid`.

 

//fork in the child process returns 0.... if return value of fork is 0, we know we are in child

// in the parent process, it returns the child's pid

// useful as parent knows child's name

// also, we can distinguish between parent and child

 

pid_t start_command(command* c, pid_t pgid) {

    (void) pgid;

    int pipefd[2];

    int fd;

 

    /*if(c->is_cd == 1){

        chdir(c->cd_dir);

    }*/

 

    if (c->has_pipe == 1){

        int ret = pipe(pipefd);

        if(ret == -1){

            _exit(1);

        }

 

        c->out_fd=pipefd[1];

        c->down->in_fd=pipefd[0];

 

    }

        pid_t fork_return = fork();

        if(fork_return == -1){

            _exit(1);

        }

 

        else if (fork_return == 0) {

           

            /*if(c->is_cd == 1){

                chdir(c->cd_dir);

            }*/

            if(c->has_pipe ==1){

                dup2(pipefd[1],STDOUT_FILENO);

               

            }

             if(c->in_fd != 0){

                dup2(c->in_fd, STDIN_FILENO);

               

 

            }

             if(c->redirection == 1){

                    //filename = (int)c->redirection_file;

                    if (strcmp(c->redirection_info,">") == 0){

                        fd = open(c->redirection_file,O_WRONLY | O_CREAT | O_TRUNC, 0666);

                        if(fd == -1){

                            fprintf(stderr, "No such file or directory\n");

                            _exit(1);

                        }

                        else{

                        //fprintf(stderr, "!");

                        int child = dup2(STDOUT_FILENO, fd);

                        if(child == -1){

                            _exit(1);

                        }

                        //fdopen(filename,'wb');

                        //c->redin = fd;

                        close(fd);

 

 

                        }

                    }

                    else if (strcmp(c->redirection_info,"<") == 0){

                        fd = open(c->redirection_file,O_RDONLY);

                         if(fd == -1){

                            fprintf(stderr, "No such file or directory\n");

                            _exit(1);

                        }

                        else{

                        int child = dup2(fd,STDIN_FILENO);

                        if(child == -1){

                            _exit(1);

                            //fprintf(stderr, "err\n");

                        }

                        close(fd);

                       } 

                    }

                    else if (strcmp(c->redirection_info,"2>") == 0){

                        fd = open(c->redirection_file,O_WRONLY|O_CREAT|O_TRUNC, 0666);

                         if(fd == -1){

                            fprintf(stderr, "No such file or directory\n");

                            _exit(1);

                        }

                        else{          

                         int child = dup2(STDERR_FILENO,fd);

                         if(child == -1){

                           fprintf(stderr, "err\n");

                            _exit(1);

                        }

                         close(fd);

                        }

                    }

 

 

            }

          

                        setpgid(0, pgid);

                        int ret_val = execvp(c->argv[0], c->argv);

                        if (ret_val == -1)

                        {

                            _exit(1);

                        }

                       

               

        }

        else //parent setting pgid. If child stalls and parent runs, we need to take care of the child

        if(setpgid(fork_return, pgid) == -1)

       

        {

            _exit(1);

        }

                       

 

       

        

 

     //book-keeping  

        c->pid = fork_return;

        if(c->has_pipe == 1){

 

            close(pipefd[1]);

 

        }

        if(c->in_fd != 0){

            close(c->in_fd);

 

        }

        //if(c->redirection == 1)

        //waitpid(fork_return, NULL, 0);

        //close(fd);

       

    

 

    return c->pid;

}

 

 

// run_list(c)

//    Run the command list starting at `c`.

//

//    PART 1: Start the single command `c` with `start_command`,

//        and wait for it to finish using `waitpid`.

//    The remaining parts may require that you change `struct command`

//    (e.g., to track whether a command is in the background)

//    and write code in run_list (or in helper functions!).

//    PART 2: Treat background commands differently.

//    PART 3: Introduce a loop to run all commands in the list.

//    PART 4: Change the loop to handle conditionals.

//    PART 5: Change the loop to handle pipelines. Start all processes in

//       the pipeline in parallel. The status of a pipeline is the status of

//       its LAST command.

//    PART 8: - Choose a process group for each pipeline.

//       - Call `set_foreground(pgid)` before waiting for the pipeline.

//       - Call `set_foreground(0)` once the pipeline is complete.

//       - Cancel the list when you detect interruption.

 

void run_list_vertical(command* c){

    while (c != NULL) {

          pid_t child_pid =  start_command(c, 0);

           int status;

           waitpid(child_pid, &status, 0);

 

 

        if (WIFEXITED(status))

        {

            if (WEXITSTATUS(status) != 0)   

              {

                  if (c->conditional_and == 1) {

                    while (c != NULL && c->conditional_and == 1)

                    {

                         c = c->down;

                          //fprintf(stderr, "Check1");

                    }

 

                    c = c->down;

                    continue;

                    }

               }

 

            if (WEXITSTATUS(status) == 0)   

              {

                  if (c->conditional_or == 1) {

                    while (c != NULL && c->conditional_or == 1)

                    {

                        //fprintf(stderr, "Check2");

                          c = c->down;

                    }

 

                    c = c->down;

                    continue;

                }

            }

            c=c->down;

        }

    }

}

 

 

void run_list(command* c) {

    // have a while loop

    // and then go to next c-> next

    // in struct, have a ponter to next one

    // want to be able to run processes in the background

    //sleep; echo foo..... terminal will sleep for one second but we want foo to run immediately while another process sleeps

 

  

    while (c != NULL) {

 

        if (c->background == 1) {

            

            if (fork() == 0) {

              

                run_list_vertical(c);

 

                _exit(0);

            }

            else {

               

                c=c->next;

            }

        }

 

        else {

            run_list_vertical(c);

            c=c->next;

        }

 

    }

}

 

 

 

 

 

 

 

 

// eval_line(c)

//    Parse the command list in `s` and run it via `run_list`.

 

void eval_line(const char* s) {

    int type;

    char* token;

 

    // Your code here!

 

    // build the command

    command* c = command_alloc();

   struct command* head = c;

   struct command* head2 = c;

    while ((s = parse_shell_token(s, &type, &token)) != NULL) {

        c->conditional_and=0;

        c->conditional_or=0;

           

        

        if (type == TOKEN_AND) {

            command* e = command_alloc();

            c->conditional_and = 1;

            c->down= e;

            e->up = c;

            c = e;

        }

        else if (type == TOKEN_OR) {

            command* e = command_alloc();

            c->down= e;

            c->conditional_or=1;

            e->up = c;

            c = e;

        }

        else if (type == TOKEN_BACKGROUND) {

            head2->background = 1;

            command* d = command_alloc();

            head2->next = d;

            d->prev = head2;

            c = d;

            head2=d;

        }

        else if (type == TOKEN_SEQUENCE) {

            command* d = command_alloc();

            head2->next = d;

            d->prev = head2;

            c = d;

            head2 =d;

        }

        else if (type == TOKEN_REDIRECTION){

            command* e = command_alloc();

            c->down= e;

            c->redirection = 1;

            c->redirection_info = token;

            parse_shell_token(s, &type, &token);

            c->redirection_file = token;

            e->up = c;

            c = e;

        }

 

        else if (type == TOKEN_PIPE){

            command* e = command_alloc();

            c->down= e;

            c->has_pipe=1;

            e->up = c;

            c = e;

        }

        /*else if(type == TOKEN_NORMAL){

            command* e = command_alloc();

            c->down= e;

            c->is_cd=1;

            parse_shell_token(s, &type, &token);

            c->cd_dir = token;

            e->up = c;

            c = e;

 

        } */

        else {

            command_append_arg(c, token);

          /*  if(strcmp(token, "cd")){

 

           } */

        }

    }

 

    if (!c->argc)

    {

    c->prev->next= NULL;

    command_free(c);

    c = NULL;

 

    }

    run_list(head);

    while (head != NULL) {

        command_free(head);

        head = head->next;

}

}

 

 

int main(int argc, char* argv[]) {

    FILE* command_file = stdin;

    int quiet = 0;

 

    // Check for '-q' option: be quiet (print no prompts)

    if (argc > 1 && strcmp(argv[1], "-q") == 0) {

        quiet = 1;

        --argc, ++argv;

    }

 

    // Check for filename option: read commands from file

    if (argc > 1) {

        command_file = fopen(argv[1], "rb");

        if (!command_file) {

            perror(argv[1]);

            exit(1);

        }

    }

 

    // - Put the shell into the foreground

    // - Ignore the SIGTTOU signal, which is sent when the shell is put back

    //   into the foreground

    set_foreground(0);

    handle_signal(SIGTTOU, SIG_IGN);

 

    char buf[BUFSIZ];

    int bufpos = 0;

    int needprompt = 1;

 

    while (!feof(command_file)) {

        // Print the prompt at the beginning of the line

        if (needprompt && !quiet) {

            printf("sh61[%d]$ ", getpid());

            fflush(stdout);

            needprompt = 0;

        }

 

        // Read a string, checking for error or EOF

        if (fgets(&buf[bufpos], BUFSIZ - bufpos, command_file) == NULL) {

            if (ferror(command_file) && errno == EINTR) {

                // ignore EINTR errors

                clearerr(command_file);

                buf[bufpos] = 0;

            } else {

                if (ferror(command_file))

                    perror("sh61");

                break;

            }

        }

 

        // If a complete command line has been provided, run it

        bufpos = strlen(buf);

        if (bufpos == BUFSIZ - 1 || (bufpos > 0 && buf[bufpos - 1] == '\n')) {

            eval_line(buf);

            bufpos = 0;

            needprompt = 1;

        }

 

        // Handle zombie processes and/or interrupt requests

        // Your code here!

        waitpid(-1, NULL, WNOHANG);

        waitpid(-1, NULL, WNOHANG);

        waitpid(-1, NULL, WNOHANG);

        waitpid(-1, NULL, WNOHANG);

 

        //while (waitpid(-1, NULL, WNOHANG) == 0);

 

       

        

    }

 

 

    return 0;

}

 