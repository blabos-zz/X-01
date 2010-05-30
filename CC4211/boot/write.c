#include <sys/types.h> /*unistd.h precisa disso*/
#include <unistd.h> /*contem rotinas de leitura/escrita*/
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(){
    char boot_buf[512];
    int sd_desc, file_desc, byte_read, byte_write;
    
    memset(boot_buf, 0, 512);
    
    file_desc = open("./boot", O_RDONLY);
    byte_read = read(file_desc, boot_buf, 510);
    printf("%d\n", byte_read);
    close(file_desc);
    
    boot_buf[510] = 0x55;
    boot_buf[511] = 0xaa;
    
    sd_desc = open("/dev/sdb1", O_RDWR);
    lseek(sd_desc, 0, SEEK_CUR);
    byte_write = write(sd_desc, boot_buf, 512);
    printf("%d\n", byte_write);
    close(sd_desc);
}
