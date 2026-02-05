#include <stdio.h>
#include <stdlib.h>

void copy_to_clipboard(const char *text) {
  char command[512];

#ifdef _WIN32
  snprintf(command, sizeof(command), "echo %s | clip", text);
#elif __APPLE__
  snprintf(command, sizeof(command), "echo '%s' | pbcopy", text);
#else  // Linux
  snprintf(command, sizeof(command), "echo '%s' | xclip -selection clipboard", text);
#endif

  system(command);
  printf("Copied password to clipboard\n");
}
