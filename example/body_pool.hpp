#pragma once
/*
 * Copyright (c) 2016-20017 Max Cong <savagecm@qq.com>
 * this code can be found at https://github.com/maxcong001/CPP_test_env
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "testInclude.hpp"
#include <thread>
#include <chrono>
// name: dbw_001
// info: this field should record the case info
case_result body_0001(void *arg, unsigned long id)
{
	cout << "this is a test case body, id is : " << id << endl;

	return EXCEPT_EQ("test", "test");
}
case_result body_0002(void *arg, unsigned long id)
{
	cout << "this is a test case body 0002, id is : " << id << endl;
	return EXCEPT_EQ("test", "tes1t");
}
case_result body_0003(void *arg, unsigned long id)
{
	cout << "this is a test case body 0003, id is : " << id << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	REC_RESULT_FINAL(CASE_SUCCESS, id);

	return CASE_FAIL;
}
case_result body_0004(void *arg, unsigned long id)
{
	cout << "this is a test case body 0004, id is : " << id << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	REC_RESULT_FINAL(CASE_FAIL, id);
	return CASE_SUCCESS;
}
case_result body_0005(void *arg, unsigned long id)
{
	cout << "this is a test case body 0005, id is : " << id << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	REC_RESULT_FINAL(CASE_SUCCESS, id);
	return CASE_SUCCESS;
}