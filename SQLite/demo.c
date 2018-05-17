#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#include "sqlite3.h"

static int calltimes = 0;

static int callback(void *notused, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		printf("%s=%s\t", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");

	return 0;
}

int Sqlite3_exec(sqlite3 *db, const char *sql,
		 int (*callback)(void *, int, char **, char **), void *p,
		 char **perrmsg)
{
	int ret = sqlite3_exec(db, sql, callback, p, perrmsg);
	if(ret != SQLITE_OK)
	{
		printf("SQL[%s] failure:%s\n", sql, *perrmsg);
		exit(0);
	}

	return ret;
}

int main(int argc, char **argv)
{
	sqlite3 *db = NULL;

	int ret;

	//1，打开/创建一个数据库：parking.db
	ret = sqlite3_open_v2("parking.db", &db,
			SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
			NULL);
	if(ret != SQLITE_OK)
	{
		printf("[%d] error: %s\n", __LINE__,
				sqlite3_errmsg(db));
		exit(0);
	}

	// 出错信息
	char *errmsg = NULL;


	// 2，在数据库中，创建一张表 carinfo
	//    并使得表中存放卡号、车牌号、照片路径和入场时间
	char *sql = NULL;
	sql = "CREATE TABLE carinfo(id      INTEGER PRIMARY KEY,"
	      "                     licence TEXT NOT NULL,"
	      "                     photo   TEXT,"
	      "                     time_in DEFAULT(datetime(CURRENT_TIMESTAMP, 'localtime')));";

	// 使用API执行以上SQL语句
	Sqlite3_exec(db, sql, NULL, NULL, &errmsg);


	// 三秒钟插入三条新的记录
	char *sql1 = "INSERT INTO carinfo(licence) VALUES('美A00911');";
	Sqlite3_exec(db, sql1, NULL, NULL, &errmsg);
	Sqlite3_exec(db, "SELECT * FROM carinfo WHERE id=last_insert_rowid();", callback, NULL, &errmsg);

	sleep(1);

	char *sql2 = "INSERT INTO carinfo(licence) VALUES('粤B9MK48');";
	Sqlite3_exec(db, sql2, NULL, NULL, &errmsg);
	Sqlite3_exec(db, "SELECT * FROM carinfo WHERE id=last_insert_rowid();", callback, NULL, &errmsg);

	sleep(1);

	char *sql3 = "INSERT INTO carinfo(licence) VALUES('京A00001');";
	Sqlite3_exec(db, sql3, NULL, NULL, &errmsg);
	Sqlite3_exec(db, "SELECT * FROM carinfo WHERE id=last_insert_rowid();", callback, NULL, &errmsg);


	// delete item



	// update item



	// close db
	char *sql5 = "DROP TABLE IF EXISTS carinfo ;";
	Sqlite3_exec(db, sql5, NULL, NULL, &errmsg);
	sqlite3_close(db);

	return 0;
}
