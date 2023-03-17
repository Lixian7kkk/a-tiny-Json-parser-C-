#include <iostream>
#include <fstream>
using namespace std;

#include "my_json.h"
using namespace lixiang::json;

int main()
{
	/*Json v1;
	Json v2 = true;
	Json v3 = 7;
	Json v4 = 7.7;
	Json v5 = "Lixiang";//对于构造函数的测试
	bool b = v2;
	int i = v3;
	double f = v4;
	const string & s = v5;//对于类型转换的测试*/

	/*Json arr;
	arr[0] = true;
	arr[1] = 123;
	arr.append(1.23);
	arr.append("lixiang777");
	std::cout << arr.str() << std::endl;
	bool b = arr[0];
	int i = arr[1];
	double f = arr[2];
	const string & s = arr[3];*/

	//Json obj;
	//obj["bool"] = true;
	//obj["int"] = 123;
	//obj["double"] = 1.23;
	//obj["str"] = "lixiang";
	//std::cout << obj.str() << std::endl;

	//Json arr;
	//arr[0] = true;
	//arr[1] = 1;
	//arr[2] = 2.1;
	//arr[3] = "lixiang";
	/*for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		std::cout << (*it).str() << std::endl;
	}*/

	/*std::cout << arr.has(0) << std::endl;
	std::cout << arr.has(4) << std::endl;
	arr.remove(0);
	std::cout << arr.str() << std::endl;*/

	//std::cout << "my c++ json" << std::endl;

	/*const string& str = "-123.456";
	Json v;
	v.parse(str);*/


	ifstream fin("test.json");
	stringstream ss;
	ss << fin.rdbuf();//rdbuf()使文件流对象指向的内容用ss流对象输出
	const string& str = ss.str();
	std::cout << ss.str() << std::endl;
	Json v;
	v.parse(str);

	bool isLogin = v["data"]["isLogin"];
	bool flag = v.has("isLogin");
	int mid = v["data"]["mid"];
	std::cout << mid << std::endl;

	std::cout << v.str() << std::endl;
	system("pause");
	return 0;
}