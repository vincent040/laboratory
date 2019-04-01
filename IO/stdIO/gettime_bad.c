#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 64
#define STRSIZE 4

void itoa(int num, char num_str[])
{
	umask(0755);
	/**************************************************
	   从倒数第二个位置num_str[STRSIZE-2]开始存储数据
	   而倒数第一个位置num_str[STRSIZE-1]存储'\0'
	***************************************************/
	char i;
	int j = STRSIZE-2;
	num_str[STRSIZE-1] = '\0';

	/*********************************************
	   将整数num转换成字符串存储进数组中。例如：
	   整数235将放在数组里的情况是：(STRSIZE=5)
	   {' ','2','3','5','\0'}
	**********************************************/
	while((num%10) != num){
		i = num%10 + '0';
		num_str[j--] = i;
		num = num/10;
	}
	num_str[j--] = num + '0'; //计算数值的ASCII码值并填入数组

	while(j >= 0)
		num_str[j--] = ' '; //前面没写入数据的位置填充空格

	return;
}

int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BUFSIZE];
	int line_num=0;

	/**********************************************************
	   以追加读写"a+"模式打开文件times，以便在文件不存在的时
	   候可以创建之，而当文件存在的时候追加，而且可以读文件以
	   便确定当前要写进文件字符串的序号。
	***********************************************************/
	if((fp=fopen("times", "a+")) == NULL){
		perror("fopen times failed");
		return -1;
	}

	//把该流设置为无缓冲的，则在写入的时候可不必调用fflush函数
	setvbuf(fp, NULL, _IONBF, 0);

	/*********************************************************************
	   读取times文件内容，并确定行号（即序号）。
	   此处的BUFSIZE一定要比文件中最长的一行长，否则算出来的行数将不准确。
	**********************************************************************/
	while((fgets(buf, BUFSIZE, fp)) != NULL)
		line_num++;

	if(ferror(fp)){ //因为fgets出错和遇到文件尾都返回NULL，所以必须加以判断。
		perror("fgets error");
		return -1;
	}

	//最多记录1,000条信息，加上BUFSIZE的原因是要把时间字符串strcat到数组里面
	char num_str[STRSIZE+BUFSIZE]; 

	/*********************************************************************
	   原型：time_t time(time_t *tloc); (tloc: time var location)

	   time函数接受一个指向time_t类型的指针变量，把得到的从1970年1月1日起
	   的秒数储存到指针tloc所指向的内存里，而此值又被作为time函数的返回值
	   返回。
	**********************************************************************/
	time_t *tloc=(time_t *)malloc(sizeof(time_t));

	/**************************************************************************
	   原型：struct tm *localtime(const time_t *);
	   原型：char *asctime(const struct tm *tloc);
	   原型：char *ctime(const time_t *tloc);

	   1、localtime接受一个指向time_t结构的指针，并把time_t结构中的信息转换成
	   真实世界所使用的时间日期表示方法，然后将结果由结构tm返回。

	   2、asctime接受一个指向结构体tm的指针，并把tm结构中的信息转换成真实世界
	   所使用的时间日期表示方法，然后结果以字符串形式返回。

	   3、ctime接受一个指向time_t结构的指针，并把time_t结构中的信息转换成真实
	   世界所使用的时间日期表示方法，然后结果以字符串形式返回。

	   tm结构体信息具体如下：
	   struct tm{
		int tm_sec;     //目前的秒数，正常为0-59，但允许为61
		int tm_min;     //目前的分数，范围为0-59
		int tm_hour;    //从零点起的时数，范围为0-23
		int tm_mday;    //目前月份的日数，范围为01-31
		int tm_mon;     //目前月份，从一月算起，范围为0-11
		int tm_year;    //自1970年起到目前的年数
		int tm_wday;    //一星期的日数，从星期一算起，范围为0-6
		int tm_yday;    //从今年1月1日起至今的天数，范围为0-365
		int tm_isdst;   //日光节约时间的旗标
	   }
	*****************************************************************************/

	//循环把当前时间写入times文件
	while(1){

		itoa(++line_num, num_str); //从line_num+1开始算起
		time(tloc);
		strcat(num_str, "	");

		/* 方法一：把指向time_t结构的指针直接转换成字符串 */
		strcat(num_str, ctime(tloc)); 

		/* 方法二：先把指向time_t结构的指针转成指向tm的指针，再将其转成字符串 */
		//strcat(num_str, asctime(localtime(tloc)));

		fputs(num_str, fp);
		fputs(num_str, stdout);

		//除非流引用终端设备，否则系统默认流是全缓冲的，可以调用fflush冲洗流
		//fflush(fp);
		sleep(1);

	}

	return 0;
}
