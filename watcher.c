#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

#define DEFAULT_COMMAND "killall -USR1 reader"

int main(int argc, char** argv)
{
  int   len, i = 0;
  int   fd;
  int   wd;
  char  buffer[EVENT_BUF_LEN];
  char* dir;
  char* cmd;
  if(argc < 2) {
    printf("%s needs a file to watch as argument.\n", argv[0]);
    exit(1);
  }

  if(argc > 2)
	cmd = argv[2];
  else
    cmd = DEFAULT_COMMAND;

  fd  = inotify_init();
  dir = realpath(argv[1], NULL);
  if(fd < 0) {
    printf("%s: error while starting inotify.\n", argv[0]);
	close(fd);
    free(dir);
    free(cmd);
    exit(1);
  }

  if((wd = inotify_add_watch( fd, dirname(dir), IN_CREATE | IN_DELETE | IN_MODIFY)) < 0) {
	close(fd);
    free(dir);
    free(cmd);
    exit(1);
  }
  while(1) {
    if((len = read(fd, buffer, EVENT_BUF_LEN)) < 0) {
      printf("%s: error while reading.\n", argv[0]);
      inotify_rm_watch(fd, wd);
      close(fd);
      free(dir);
      free(cmd);
      exit(1);
    }
    i = 0;
    while(i < len) {
      struct inotify_event *event = (struct inotify_event*) &buffer[i];
      if(!strcmp(argv[1], event->name))
	        system(cmd);
	      i += EVENT_SIZE + event->len;
    }
  }
  inotify_rm_watch(fd, wd);
  close(fd);
  free(dir);
  free(cmd);
  return 0;
}
