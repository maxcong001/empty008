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
class test_suit_base : NonCopyable,
					   public std::enable_shared_from_this<test_suit_base>
{
  public:
	test_suit_base() = delete;
	test_suit_base(string name) { suit_name = name; }
	void addCase(std::shared_ptr<test_case_base> test_case)
	{
		_cases[test_case->get_case_name()] = test_case;
		test_case->set_suit_name(get_suit_name());
		test_case->set_project_name(get_project_name());
	}
	std::shared_ptr<test_suit_base> getSelf() { return shared_from_this(); }
	void run()
	{
		std::unordered_map<TEST_PREPARE_FUNCTION,
						   std::vector<std::shared_ptr<test_case_base>>>
			fun_cases_map;
		for (auto i : _cases)
		{
			(fun_cases_map[(i.second)->get_prepare_func()]).push_back(i.second);
		}
		for (auto j : fun_cases_map)
		{
			// prepare the env
			void *tmp_arg = (j.first)();
			TEST_DESTROY_FUNCTION to_destroy;
			for (auto k : (j.second))
			{
				cout << k->_case_info << endl;
				k->set_arg(tmp_arg);
				std::string sig = k->get_signature();
				REC_RESULT(k->run_body(sig), sig);
				// this will called every time. can optimise
				// Humm, do it later, this will not cost much time
				to_destroy = k->get_destroy_func();
			}
			// destroy the env
			to_destroy(tmp_arg);
		}
	}
	string get_suit_name() { return suit_name; }
	void set_suit_name()
	{
		for (auto i : _cases)
		{
			(i.second)->set_suit_name(get_suit_name());
		}
	}
	std::string get_project_name()
	{
		return _project_name;
	}
	void set_project_name(std::string name)
	{
		_project_name = name;
		for (auto i : _cases)
		{
			(i.second)->set_project_name(_project_name);
		}
	}
	std::string suit_name;
	std::string _project_name;

	std::unordered_map<std::string, std::shared_ptr<test_case_base>> _cases;
};