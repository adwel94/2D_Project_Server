#include "Log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool Utilities::cLog::Connect(const char* _name, const char* _path)
{
	//길이 초과시 실패
	if ((strlen(_name) + strlen(_path)) >= MAX_LEN)
	{
		printf_s("Name Size Over \n");
		return false;
	}

	char mMsg[MAX_LEN] = "\0";
	
	//경로가 입력되면 경로+
	if (strlen(_path) > 0)
	{
		strcat_s(mMsg, _path);
		mMsg[strlen(_path)] = '\\';
		mMsg[strlen(_path) + 1] = '\0';

	}

	//파일 이름+
	strcat_s(mMsg, _name);	

	//파일 이어 쓰기로 연결
	if (fopen_s(&mFp, mMsg, "a") != 0)
	{
		printf_s("Log Connect Fail Name : %s \n", _name);
		return false;
	}

	printf_s("Log Connect Success Name : %s \n", _name);
	return true;
}

bool Utilities::cLog::Record(const char* _msg)
{

	if (mFp == nullptr) return false;
	if (strlen(_msg) >= MAX_LEN) return false;

	//시간 구하는 변수, 함수
	time_t timer = time(NULL);
	tm now;

	//최대길이 + 널 + 시간값 길이
	char log[MAX_LEN + 32 + 1] = "\0";


	if (localtime_s(&now, &timer) != 0)
	{
		//현재시간을 알수 없을 경우
		strcat_s(log, "Unknown Time - ");
	}
	else
	{
		//시간을 이어 붙임
		char timeinfo[32];
		sprintf_s(timeinfo, "%d-%d-%d %d:%d:%d - ", now.tm_year+1900, now.tm_mon+1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
		strcat_s(log, timeinfo);
	}

	//마지막에 줄바꿈 추가
	strcat_s(log, _msg);
	log[strlen(log) + 1] = '\0';
	log[strlen(log)] = '\n';


	fputs(log,mFp);
	return true;
}

bool Utilities::cLog::Close()
{
	//파일 닫기
	return (fclose(mFp) == 0) ? true : false;
}
