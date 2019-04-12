#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	if(!access("lock", F_OK))
		fd = open("lock", O_RDWR);
	else{
		fd = open("lock", O_RDWR | O_CREAT, 0644);
		write(fd, "abcde_12345", 12);
	}

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 1;
	lock.l_len = 5;

	fcntl(fd, F_GETLK, &lock);

	if(lock.l_type != F_UNLCK){
		fprintf(stderr, "lock is bussy!\n");
		fprintf(stderr, "%d is holding the lock.\n", lock.l_pid);
		fprintf(stderr, "lock type: %s\n",
				lock.l_type == F_WRLCK ? "F_WRLCK":
			       (lock.l_type == F_RDLCK ? "F_RDLCK" : "unknown"));
		fprintf(stderr, "lock range: %ld ~ %ld (totally %d bytes)\n",
				lock.l_whence + lock.l_start,
				lock.l_whence + lock.l_start + lock.l_len,
				(int)lock.l_len);
		exit(0);
	}
	else{
		lock.l_type = F_WRLCK;
		fcntl(fd, F_SETLK, &lock);
		pause();
	}

	return 0;
}
