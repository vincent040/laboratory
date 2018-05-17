#include "head4player.h"

struct tsdev *init_ts(void)
{
	struct tsdev *ts = ts_open("/dev/event0", 0);
	ts_config(ts);

	return ts;
}

void my_play()
{
	printf("play\n");
}

void my_pause()
{
	printf("pause\n");
	pause();	
}

void my_stop()
{
	int sfd = getsfd();
	close(sfd);
	printf("stop\n");
	pthread_exit(0);
}

void* thread( void *arg )  
{  
 	signal(1,my_play);
 	signal(2,my_pause);
 	signal(3,my_stop);
	
	struct stat stat;     
    void *fdm;     
    char const *file;     
    int fd;     
    file = (char*)arg;     
    fd = open(file, O_RDONLY);     

    if (fstat(fd, &stat) == -1 || stat.st_size == 0)     
		goto openerr;
    fdm = mmap(0, stat.st_size, PROT_READ, MAP_SHARED, fd, 0);     

    if (fdm == MAP_FAILED)     
		goto maperr;

	decode(fdm, stat.st_size);     

	if (munmap(fdm, stat.st_size) == -1)     
		goto unmaperr;
	close(fd);
	printf("play end\n");
    return arg;  
openerr:
	perror("openerr ");
	exit(1);
maperr:
	perror("maperr ");
	exit(1);
unmaperr:
	perror("unmaperr ");
	exit(1);
} 


SDL_Surface *load_image(const char *filename)
{
	return SDL_DisplayFormat(SDL_LoadBMP(filename));	
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <*.mp3>\n", argv[0]);
		exit(0);
	}
	int down=0;	

	SDL_Surface *screen = NULL;
	SDL_Surface *image  = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
	image  = load_image("cover.bmp");

	// 将image blit到screen上
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_BlitSurface(image, NULL, screen, &rect);

	SDL_Flip(screen);

	struct tsdev *ts = init_ts();
	struct ts_sample samp;

	bool quit = false;
	bool bstop=true,bplay=false,bpause=false;

	while(quit == true)
	{
		ts_read(ts, &samp, 1);

		pthread_t th;

		if(samp.x<=200 && bstop == true)
		{
			int ret;  
			char const *arg = argv[1];  
			int *thread_ret = NULL;  
			ret = pthread_create( &th, NULL, thread, arg);  
			if( ret != 0 )
			{  
				printf( "Create thread error!\n");  
				return -1;  
			}
			printf("%d\n",down);
			bplay = true;
			bstop = false;
			bpause = false;
		}	
		if(bplay==true && (samp.x>200 && samp.x<=400))
		{
			pthread_kill(th,2);//pause
			bplay=false;
			bpause=true;
			bstop = false;
		}
		if(bpause==true && samp.x<=200)
		{
			pthread_kill(th,1);//play
			bplay = true;
			bpause = false;
			bstop = false;
		}
		if(samp.x>400 && samp.x<600)
		{
			pthread_kill(th,3);//stop
			bplay = false;
			bpause = false;
			bstop = true;
		}
		if(samp.x>600 && samp.x<800)
		{
			printf("%d\n",down);
			quit = true;
		}

	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(image);
	SDL_Quit();

	return 0;
}
