/**
 * microbit-game-controller-client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF_SZ 1024
#define BUF_RD_SZ 19

int main(int argc, char *argv[]) {
  int fd;
  char buf[MAX_BUF_SZ];
  bool valid = false;
  char *end_x = &buf[6];
  char *end_y = &buf[12];
  char *end_z = &buf[18];

  if ((fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC)) < 0) {
    fprintf(stderr, "Cannot open serial port\n");
    exit(1);
  }

  // read one byte per iteration
  while ((read(fd, buf, BUF_RD_SZ)) == BUF_RD_SZ) {
    buf[BUF_RD_SZ] = '\0';
  
    valid  = buf[0]  == 'x';
    valid &= buf[6]  == 'y';
    valid &= buf[12] == 'z';

    long x = strtol((const char *) &buf[1],  &end_x, 10);
    long y = strtol((const char *) &buf[7],  &end_y, 10);
    long z = strtol((const char *) &buf[13], &end_z, 10);
    
    // make sure nothing wrong happended during parsing data
    valid &= errno == 0; 
    
    if (valid) {
      printf("buf = %s\n", buf);
      printf("x = %5ld\n", x);
      printf("y = %5ld\n", y);
      printf("z = %5ld\n", z);
    }
  }

  return 0;
}
