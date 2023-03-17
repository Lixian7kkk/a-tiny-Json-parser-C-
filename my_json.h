#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdexcept>
using namespace std;
namespace lixiang
{
	namespace json
	{
		class Json
		{
		public:
			enum Type			//枚举将json中的不同数据类型和值关联起来
			{
				json_null = 0,
				json_bool,
				json_int,
				json_double,
				json_string,
				json_array,
				json_object
			};
			//Json构造函数	eg： int i -》Json j；
			Json();
			Json(bool value);
			Json(int value);
			Json(double value);
			Json(const char* value);//兼容c风格字符串
			Json(const string& value);
			Json(Type type);
			Json(const Json& other);//复制构造函数
			//重载对应类型运算符，将Json对象的值转换为对应类型的值	eg：Json j -》int i；此处设计思想仍需弄懂
			operator bool();
			operator int();
			operator double();
			operator string();
			//Json对象为数组类型时，重载以下两种操作，使其能像普通数组一样操作
			Json& operator [] (int index);
			void append(const Json& other);
			//重载Json中对象类型的下标操作符
			Json& operator [] (const char* key);
			Json& operator [] (const string& key);
			//为Json对象类型重载赋值运算符
			void operator= (const Json& other);
			//为Json类重载== and !=
			bool operator== (const Json& other);
			bool operator!= (const Json& other);
			//以string形式返回Json对象的值，针对存放指针的三种情况
			string str() const;

			void copy(const Json& other);
			//解决内存泄露问题？？？
			void clear();

			typedef std::vector<Json>::iterator it;//定义迭代器，用于遍历数组
			it begin()
			{
				return m_value.m_array->begin();
			}
			it end()
			{
				return m_value.m_array->end();
			}

			bool isNull() const { return m_type == json_null; }
			bool isBool() const { return m_type == json_bool; }
			bool isInt() const { return m_type == json_int; }
			bool isDouble() const { return m_type == json_double; }
			bool isString() const { return m_type == json_string; }
			bool isArray() const { return m_type == json_array; }
			bool isObject() const { return m_type == json_object; }

			bool asBool() const;
			int asInt() const;
			double asDouble() const;
			string asString() const;

			bool has(int index);
			bool has(const char* key);
			bool has(const string& key);

			void remove(int index);
			void remove(const char* key);
			void remove(const string& key);

			void parse(const string& str);
		private:
			union Value					//联合（一个特殊的类）存放每种类型中存的值
			{
				bool m_bool;
				int m_int;
				double m_double;
				std::string* m_string;//存放string值的指针
				std::vector<Json>* m_array;//存放数组指针
				std::map<string, Json>* m_object;//存放对象指针
			};
			Type m_type;
			Value m_value;
		};
	}
}
