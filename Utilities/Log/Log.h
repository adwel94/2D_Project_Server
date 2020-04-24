#pragma once
#ifndef _LOG_H_
#define _LOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace Utilities
{
	class cLog
	{
	public:

		enum
		{
			NAME_LEN = 32,//파일 최대 이름
			MAX_LEN=128//최대로 기록할수 있는 글자 길이
		};

	protected:
		FILE* mFp;//파일 포인터
		char mName[NAME_LEN] = "\0";//파일 이름	
	public:

		cLog()
		{
			mFp = nullptr;
		}

		//파일이름,경로
		bool Connect(const char* _name, const char* _path = "\0");
		//기록
		bool Record(const char* _msg);
		//해제
		bool Close();


	};

}


#endif // !_LOG_H_
