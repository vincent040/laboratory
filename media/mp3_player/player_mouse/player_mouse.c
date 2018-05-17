#include "head4player.h"


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

	// 轮询事件(鼠标事件)
	SDL_Event event;
	bool quit = false;
	bool bstop=true,bplay=false,bpause=false;
	while(quit == false)
	{
		// 当鼠标抬起的时候，就退出程序
		// 注：SDL_WaitEvent()是阻塞版本
		//     SDL_PollEvent()是非阻塞版本

		SDL_WaitEvent(&event); //SDL_PollEvent(&event);
		
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			pthread_t th;  
			if(down++==0);
			printf("x=%d,y=%d\n",event.button.x,event.button.y);

			if(event.button.x<=200 && bstop == true)
			{
				int ret;  
				char *arg = argv[1];  
				int *thread_ret = NULL;  
				ret = pthread_create( &th, NULL, thread, arg);  
				if( ret != 0 ){  
					printf( "Create thread error!\n");  
					return -1;  
				}
				printf("%d\n",down);
				bplay = true;
				bstop = false;
				bpause = false;
			}	
			if(bplay==true&&(event.button.x>200&&event.button.x<=400))
			{
				printf("%d\n",down);
				pthread_kill(th,2);//pause
				bplay=false;
				bpause=true;
				bstop = false;
				//SDL_Delay(20);
			}
			if(bpause==true && event.button.x<=200)
			{
				//printf("%d\n",down);
				pthread_kill(th,1);//play
				bplay = true;
				bpause = false;
				bstop = false;
			}
			if(event.button.x>400&&event.button.x<600)
			{
				//printf("stop",down);
				pthread_kill(th,3);//stop
				bplay = false;
				bpause = false;
				bstop = true;
			}
			if(event.button.x>600&&event.button.x<800)
			{
				printf("%d\n",down);
				quit = true;
			}

		}
	}

	SDL_FreeSurface(screen);
	SDL_FreeSurface(image);
	SDL_Quit();

	return 0;
}
