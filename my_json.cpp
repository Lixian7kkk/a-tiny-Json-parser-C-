#include "my_json.h"
#include "parse.h"
using namespace lixiang::json;


Json::Json() : m_type(json_null)
{

}
Json::Json(bool value) : m_type(json_bool)//初始化列表初始化类型
{
	m_value.m_bool = value;//计算，将Json对象的值初始化，union可视作一个特殊的类，可用.or->操作符访问其对象
}
Json::Json(int value) : m_type(json_int)
{
	m_value.m_int = value;
}
Json::Json(double value) : m_type(json_double)
{
	m_value.m_double = value;
}
Json::Json(const char* value) : m_type(json_string)//c风格字符串实际是一个带有结束符的char型数组，通过指针操作其各个字符
{
	m_value.m_string = new string(value);//此处是因为string标准库提供以c风格字符串（字符串字面值）做参数的构造函数
}
Json::Json(const string& value) : m_type(json_string)
{
	m_value.m_string = new string(value);
}
Json::Json(Type type) : m_type(type)//根据类型的构造函数，同时将对应类型的值初始化
{
	switch (m_type)
	{
	case lixiang::json::Json::json_null:
		break;
	case lixiang::json::Json::json_bool:
		m_value.m_bool = false;
		break;
	case lixiang::json::Json::json_int:
		m_value.m_int = 0;
		break;
	case lixiang::json::Json::json_double:
		m_value.m_double = 0.0;
		break;
	case lixiang::json::Json::json_string:
		m_value.m_string = new string("");
		break;
	case lixiang::json::Json::json_array:
		m_value.m_array = new std::vector<Json>();
		break;
	case lixiang::json::Json::json_object:
		m_value.m_object = new std::map<string, Json>();
		break;
	default:
		break;
	}
}
Json::Json(const Json& other)//复制构造函数
{
	copy(other);
}

Json::operator bool()
{
	if (m_type != json_bool)
	{
		throw new logic_error("type error, not bool value");
	}
	return m_value.m_bool;
}
Json::operator int()
{
	if (m_type != json_int)
	{
		throw new logic_error("type error, not int value");
	}
	return m_value.m_int;
}
Json::operator double()
{
	if (m_type != json_double)
	{
		throw new logic_error("type error, not double value");
	}
	return m_value.m_double;
}
Json::operator string()
{
	if (m_type != json_string)
	{
		throw new logic_error("type error, not string value");
	}
	return *(m_value.m_string);
}

Json& Json::operator [] (int index)
{
	if (m_type != json_array)//此处疑问，不是array类型的json对象调用该操作符是否应该报错|||当有一个空的array类型的Json对象的问题，因为初始为空，类型为json_null
	{
		m_type = json_array;
		m_value.m_array = new vector<Json>();
	}
	if (index < 0)
	{
		throw new logic_error("array[] index < 0");
	}
	int size = (m_value.m_array)->size();//m_array为vector<Json>* 类型的名字，可使用size操作
	if (index >= size)//实现简单扩容
	{
		for (int i = size; i <= index; ++i)
		{
			(m_value.m_array)->push_back(Json());
		}
	}
	return (m_value.m_array)->at(index);//at返回下标为index的元素的引用
}
void Json::append(const Json& other)
{
	if (m_type != json_array)//此处疑问，不是array类型的json对象调用该函数是否应该报错
	{
		clear();
		m_type = json_array;
		m_value.m_array = new vector<Json>();
	}
	(m_value.m_array)->push_back(other);
}

Json& Json::operator [] (const char* key)
{
	string name(key);
	return (*(this))[name];
}
Json& Json::operator [] (const string& key)
{
	if (m_type != json_object)//此处疑问，不是array类型的json对象调用该操作符是否应该报错
	{
		clear();
		m_type = json_object;
		m_value.m_object = new std::map<string, Json>();
	}
	return (*(m_value.m_object))[key];//返回与该键关联的值
}

void Json::operator= (const Json& other)
{
	clear();
	copy(other);
}

bool Json::operator== (const Json& other)
{
	if (m_type != other.m_type)
		return false;
	switch (m_type)
	{
	case lixiang::json::Json::json_null:
		return true;
		break;
	case lixiang::json::Json::json_bool:
		return m_value.m_bool == other.m_value.m_bool;
		break;
	case lixiang::json::Json::json_int:
		return m_value.m_int == other.m_value.m_int;
		break;
	case lixiang::json::Json::json_double:
		return m_value.m_double == other.m_value.m_double;
		break;
	case lixiang::json::Json::json_string:
		return *(m_value.m_string) == *(m_value.m_string);
		break;
	case lixiang::json::Json::json_array:
		return m_value.m_array == other.m_value.m_array;//此处有重大bug，只比较了指针，未比较其中的值
		break;
	case lixiang::json::Json::json_object:
		return m_value.m_object == other.m_value.m_object;//同上
		break;
	default:
		break;
	}
	return false;
}
bool Json::operator!= (const Json& other)
{
	return !((*this) == other);
}

void Json::copy(const Json& other)
{
	m_type = other.m_type;
	switch (m_type)
	{
	case lixiang::json::Json::json_null:
		break;
	case lixiang::json::Json::json_bool:
		m_value.m_bool = other.m_value.m_bool;
		break;
	case lixiang::json::Json::json_int:
		m_value.m_int = other.m_value.m_int;
		break;
	case lixiang::json::Json::json_double:
		m_value.m_double = other.m_value.m_double;
		break;
	case lixiang::json::Json::json_string:
		m_value.m_string = other.m_value.m_string;
		break;
	case lixiang::json::Json::json_array:
		m_value.m_array = other.m_value.m_array;//此处拷贝的是数组的指针，即让两个对象拥有相同的指针，指向同一块内存区域，管理不善可能会带来违规释放内存的行为
		break;
	case lixiang::json::Json::json_object:
		m_value.m_object = other.m_value.m_object;//此处同上
		break;
	default:
		break;
	}
}


void Json::clear()
{
	switch (m_type)
	{
	case lixiang::json::Json::json_null:
		break;
	case lixiang::json::Json::json_bool:
		m_value.m_bool = false;
		break;
	case lixiang::json::Json::json_int:
		m_value.m_int = 0;
		break;
	case lixiang::json::Json::json_double:
		m_value.m_double = 0.0;
		break;
	case lixiang::json::Json::json_string:
	{
		delete m_value.m_string;
		break;
	}
	case lixiang::json::Json::json_array:
	{
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); ++it)
			it->clear();
		delete m_value.m_array;
		break;
	}
	case lixiang::json::Json::json_object:
	{
		for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); ++it)
			(it->second).clear();
		delete m_value.m_object;
		break;
	}
	break;
	default:
		break;
	}
	m_type = json_null;
}
string Json::str() const
{
	stringstream ss;
	switch (m_type)
	{
	case lixiang::json::Json::json_null:
		ss << "null";
		break;
	case lixiang::json::Json::json_bool:
		if (m_value.m_bool)
			ss << "true";
		else
			ss << "flase";
		break;
	case lixiang::json::Json::json_int:
		ss << m_value.m_int;
		break;
	case lixiang::json::Json::json_double:
		ss << m_value.m_double;
		break;
	case lixiang::json::Json::json_string:
		ss << '\"' << *(m_value.m_string) << '\"';
		break;
	case lixiang::json::Json::json_array:
	{
		ss << '[';
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); ++it)
		{
			if (it != (m_value.m_array)->begin())//第一个元素忽略逗号的输出，换言之除了第一个元素每个元素前都有个','
			{
				ss << ',';
			}
			ss << it->str();//递归调用本函数处理数组中不同类型值
		}
		ss << ']';
	}
	break;
	case lixiang::json::Json::json_object:
	{
		ss << '{';
		for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); ++it)//auto做自动类型推导，得出迭代器类型
		{
			if (it != (m_value.m_object)->begin())
			{
				ss << ',';
			}
			ss << '\"' << it->first << '\"' << ':' << it->second.str();
		}
		ss << '}';
	}
	break;
	default:
		break;
	}
	return ss.str();//此处调用的是sstream流的str函数，返回保存在ss当中的string
}

bool Json::asBool() const
{
	if (m_type != json_bool)
		throw new std::logic_error("type error, not bool value");
	return m_value.m_bool;
}
int Json::asInt() const
{
	if (m_type != json_int)
		throw new std::logic_error("type error, not int value");
	return m_value.m_int;
}
double Json::asDouble() const
{
	if (m_type != json_double)
		throw new std::logic_error("type error, not double value");
	return m_value.m_double;
}
string Json::asString() const
{
	if (m_type != json_string)
		throw new std::logic_error("type error, not string value");
	return *(m_value.m_string);
}

bool Json::has(int index)
{
	if (m_type != json_array)
		return false;
	int size = (m_value.m_array)->size();
	return (index >= 0 && index < size);
}
bool Json::has(const char* key)
{
	string name(key);
	return has(name);
}
bool Json::has(const string& key)
{
	if (m_type != json_object)
		return false;
	return ((m_value.m_object)->find(key) != m_value.m_object->end());
}
void Json::remove(int index)
{
	if (m_type != json_array)
		return;
	int size = (m_value.m_array)->size();
	if (index < 0 || index > size)
		return;
	(m_value.m_array)->at(index).clear();
	(m_value.m_array)->erase((m_value.m_array)->begin() + index);
}
void Json::remove(const char* key)
{
	string name(key);
	remove(name);
}
void Json::remove(const string& key)
{
	auto it = m_value.m_object->find(key);
	if (it == m_value.m_object->end())
		return;
	(*(m_value.m_object))[key].clear();
	(m_value.m_object)->erase(key);
}

void Json::parse(const string& str)
{
	Parser p;
	p.load(str);
	*this = p.parse();
}