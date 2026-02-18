#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char special[] = "\"\\";

int main(int argc, char **argv) {
  char cmdline[1000], outfile[1000];
  /* write_line needs 3× the space of read_line: each character may be
   * escaped (adding a backslash), plus the surrounding quotes, \n marker,
   * newline, and null terminator. */
  char read_line[1000], *p, write_line[3000], *pw;
  FILE *i, *o;

  if (argc != 2) {
    puts("Usage: conv progname");
    return -1;
  }
  sprintf(cmdline, "gcc -S -O4 %s.c -o tmp.s", argv[1]);
  fprintf(stderr, "%s\n", cmdline);
  if (system(cmdline)) {
    puts("conv: gcc reported a compilation error. Stopping...");
    return -1;
  }
  i = fopen("tmp.s", "rt");
  if (i == NULL) {
    puts("Error reading the tmp.s file");
    return -1;
  }
  sprintf(outfile, "%s_asm.c", argv[1]);
  o = fopen(outfile, "wt");
  if (o == NULL) {
    printf("Error opening %s for writing", outfile);
    return -1;
  }
  fprintf(o, "/* @JUDGE_ID: ______ %s C */\n\n__asm__ (", argv[1]);
  while (NULL != fgets(read_line, 999, i)) {
    p = read_line;
    pw = write_line;
    *pw++ = '\"';
    while (*p != '\n') {
      if (strchr(special, *p)) *pw++ = '\\';
      *pw++ = *p;
      p++;
    }
    *pw++ = '\\';
    *pw++ = 'n';
    *pw++ = '\"';
    *pw++ = '\n';
    *pw++ = '\0';
    fputs(write_line, o);
  }
  fputs(");\n", o);
  fclose(i);
  unlink("tmp.s");
  fclose(o);
  return 0;
}
