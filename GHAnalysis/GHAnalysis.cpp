// GHAnalysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#define STATIC_GETOPT
#define _GNU_SOURCE
#define GH_LOG_INFO
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <json/json.h>
#include <map>

using namespace std;

void Init(string path);
void Num_User_Event(string u, string e);
void Num_Event_Repo(string e, string r);
void Num_User_Event_Repo(string u, string e, string r);

int main(int argc, char** argv) {
	int opt;
	int digit_optind = 0;
	int option_index = 0;
	string user, event, repo;

	char* optstring = "i:u:e:r:";
	static struct option long_options[] = 
	{
		{"init",	  1,	NULL,	'i'},
		{"user",	  1,	NULL,	'u'},
		{"event",	  1,	NULL,	'e'},
		{"repo",	  1,	NULL,	'r'},
		{ 0,		  0,	0,		 0 }
	};

	while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
		switch (opt) {
		case 'i':
			Init(optarg);
			break;
		case 'u':
			user = optarg;
			break;
		case 'e':
			event = optarg;
			break;
		case 'r':
			repo = optarg;
			break;
		}
	}

	if (!user.empty() && !event.empty() && !repo.empty()) {
		Num_User_Event_Repo(user, event, repo);
	}
	if (user.empty() && !event.empty() && !repo.empty()) {
		Num_Event_Repo(event, repo);
	}
	if (!user.empty() && !event.empty() && repo.empty()) {
		Num_User_Event(user, event);
	}

	return 0;
}

void Init(string path) {
	//cout << "进入初始化." << endl;

	int i;
	string str;
	Json::Value value;
	Json::Value value1;
	Json::Reader reader;
	Json::StyledWriter sw;

	ifstream file(path, ios::binary);
	if (!file.is_open()) {
		cout << "Data文件打开失败." << endl;
		return;
	}
	
	i = 0;
	ofstream os;
	os.open("../Data/Temp_Json.json", std::ios::out | std::ios::app);
	if (!os.is_open()) {
		cout << "Temp_Json.json文件创建失败." << endl;
		return;
	}

	os << "[" << endl;
	while (getline(file, str)) {
			i++;
			//cout << i << endl;
			if (reader.parse(str, value)) {
				string type = value["type"].asString();
				string actor_login = value["actor"]["login"].asString();
				string repo_name = value["repo"]["name"].asString();

				value1["id"] = Json::Value(i);
				value1["user"] = Json::Value(actor_login);
				value1["event"] = Json::Value(type);
				value1["repo"] = Json::Value(repo_name);

				os << sw.write(value1);
				os << "," << endl;
				
			}
			else {
				cout << "Data文件读取失败." << endl;
				return;
			}
		}
	os << "]" << endl;
	os.close();
	file.close();
	
	cout << "0" << endl;
	//cout << "初始化完成." << endl;
	return;
}

void Num_User_Event(string u, string e) {
	//cout << u << "用户的" << e << "事件数量为:" << endl;

	int ret = 0;
	string str, user, event;
	Json::Reader reader;
	Json::Value value;

	ifstream ifile("../Data/Temp_Json.json");
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	str = buf.str();
	//cout << str << endl;

	reader.parse(str, value);
	int size = value.size();
	//cout << "size:" << size << endl;
	for (int i = 0; i < size; ++i) {
		user = value[i]["user"].asString();
		event = value[i]["event"].asString();
		//cout << user << " " << event << " " << repo << endl;
		if (u == user && e == event) {
			ret++;
		}
	}

	cout << ret << endl;
	return;
}

void Num_Event_Repo(string e, string r) {
	//cout << r << "项目的" << e << "事件数量为:" << endl;

	int ret = 0;
	string str, event, repo;
	Json::Reader reader;
	Json::Value value;

	ifstream ifile("../Data/Temp_Json.json");
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	str = buf.str();
	//cout << str << endl;

	reader.parse(str, value);
	int size = value.size();
	//cout << "size:" << size << endl;
	for (int i = 0; i < size; ++i) {
		event = value[i]["event"].asString();
		repo = value[i]["repo"].asString();
		//cout << user << " " << event << " " << repo << endl;
		if (e == event && r == repo) {
			ret++;
		}
	}

	cout << ret << endl;
	return;
}

void Num_User_Event_Repo(string u, string e, string r) {
	//cout << u << "用户在" << r << "项目的" << e << "事件数量为:" << endl;

	int ret = 0;
	string str, user, event, repo;
	Json::Reader reader;
	Json::Value value;

	ifstream ifile("../Data/Temp_Json.json");
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	str = buf.str();
	//cout << str << endl;

	reader.parse(str, value);
	int size = value.size();
	//cout << "size:" << size << endl;
	for (int i = 0; i < size; ++i) {
		user = value[i]["user"].asString();
		event = value[i]["event"].asString();
		repo = value[i]["repo"].asString();
		//cout << user << " " << event << " " << repo << endl;
		if (u == user && e == event && r == repo) {
			ret++;
		}
	}

	cout << ret << endl;
	return;
}

