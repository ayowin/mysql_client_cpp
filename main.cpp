
#include <iostream>

#include "mysql.h"

int main(int argc, char** argv)
{
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;

	const char *query = NULL;
	int t, r;

	mysql_init(&mysql);

	/* 连接 */
	if (mysql_real_connect(&mysql, "localhost", "root", "123456", "mysql", 3306, NULL, 0))
	{
		printf("connect success\n");

		/* 设置编码 */
		query = "set character set utf8";
		t = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
		if (t == 0)
		{
			printf("set character-set success\n");
		}

		/* 查询数据 */
		query = " select * from user;";
		t = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
		if (t == 0)
		{
			printf("sql: %s\n", query);
			res = mysql_store_result(&mysql);

			printf("\nquery result:\n");
			while (row = mysql_fetch_row(res))
			{
				printf("\t%s\n", row[1]);
			}
			printf("\n");

			mysql_free_result(res);
		}
		else
		{
			printf("query failed by %s\n", mysql_error(&mysql));
		}

		printf("test finished. press any key to quit.\n");
		getchar();
		mysql_close(&mysql);
	}
	else
	{
		printf("connect failed by %s\n", mysql_error(&mysql));
	}

	return 0;
}