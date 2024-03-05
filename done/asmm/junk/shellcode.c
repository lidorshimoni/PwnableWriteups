#include <unistd.h>
#include <fcntl.h>

int main()
{
    // int fd = open("this_is_pwnable.kr_flag_file_please_read_this_file.sorry_the_file_name_is_very_loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo0000000000000000000000000ooooooooooooooooooooooo000000000000o0o0o0o0o0o0ong", 0, 0);
    int fd = open("flag", 0, 0);
    char buf[100];
    read(3, buf, 100);
    write(1, buf, 100); 
    return 0;
}

