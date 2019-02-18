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
#include "testUtil.hpp"
//#include "testCasesBody.hpp"
class test_case_base : NonCopyable,
					   public std::enable_shared_from_this<test_case_base>
{
  public:
	test_case_base(TEST_PREPARE_FUNCTION prepare_env_arg, TEST_BODY_FUNCTION body,
				   TEST_DESTROY_FUNCTION destroy_env, string case_name,
				   string case_info)
	{
		_prepare_env = prepare_env_arg;
		_body = body;
		_destroy_env = destroy_env;
		_case_info = case_info;
		_case_name = case_name;
		/*
            if (_prepare_env)
            {
                arg = prepare_env();
            }
    */
	}
	~test_case_base()
	{
		// in the test case, this is a smart pointer, so the destroy function will
		// called when exit.
		// this is called in the suit class, delete it here
		/*
            if (_destroy_env)
            {
                _destroy_env(arg);
            }
    */
	}
	TEST_PREPARE_FUNCTION get_prepare_func() { return _prepare_env; }
	TEST_DESTROY_FUNCTION get_destroy_func() { return _destroy_env; }

	virtual void *get_arg() { return arg; }
	virtual void set_arg(void *inArg) { arg = inArg; }

	void set_case_name(std::string name)
	{
		_case_name = name;
	}
	std::string get_case_name()
	{
		return _case_name;
	}
	void set_suit_name(std::string name)
	{
		_suit_name = name;
	}
	std::string get_suit_name()
	{
		return _suit_name;
	}
	void set_project_name(std::string name)
	{
		_project_name = name;
	}
	std::string get_project_name()
	{
		return _project_name;
	}
	std::string get_signature()
	{
		return _project_name + ":" + _suit_name + ":" + _case_name;
	}
	virtual case_result run()
	{
		if (_prepare_env)
		{
			arg = _prepare_env();
		}
		if (_body)
		{
			return _body(arg, get_signature());
		}
		else
		{
			return case_result::CASE_FAIL;
		}
	}
	virtual void prepare_env()
	{
		if (_prepare_env)
		{
			arg = _prepare_env();
		}
	}
	virtual void destroy_env()
	{
		if (_destroy_env)
		{
			_destroy_env(arg);
		}
	}
	virtual case_result run_body(std::string sig)
	{
		if (_body)
		{
			return _body(arg, sig);
		}
		else
		{
			return case_result::CASE_FAIL;
		}
	}
	std::shared_ptr<test_case_base> getSelf() { return shared_from_this(); }

	TEST_PREPARE_FUNCTION _prepare_env;
	TEST_BODY_FUNCTION _body;
	TEST_DESTROY_FUNCTION _destroy_env;
	void *arg;
	std::string _case_name;
	std::string _suit_name;
	std::string _project_name;
	std::string _case_info;
};