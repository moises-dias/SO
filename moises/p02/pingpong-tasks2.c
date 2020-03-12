#include <stdio.h>
#include <stdlib.h>
#include "pingpong.h"

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define MAXTASK 1000

task_t task[MAXTASK+1] ;

void BodyTask (void * arg)
{
   int next ;

   printf ("Iniciei  tarefa %5d\n", task_id()) ;

   // passa o controle para a proxima tarefa
   next = (task_id() < MAXTASK) ? task_id() + 1 : 1 ;
   task_switch (&task[next]);

   printf ("Encerrei tarefa %5d\n", task_id()) ;

   task_exit (0) ;
}

int main (int argc, char *argv[])
{
   int i ;

   printf ("Main INICIO\n");

   pingpong_init () ;

   // cria MAXTASK tarefas
   for (i=1; i<=MAXTASK; i++)
      task_create (&task[i], BodyTask, NULL) ;

   // passa o controle para cada uma delas em sequencia
   for (i=1; i<=MAXTASK; i++)
      task_switch (&task[i]) ;

   printf ("Main FIM\n");

   exit (0);
}
