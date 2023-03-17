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
			enum Type			//ö�ٽ�json�еĲ�ͬ�������ͺ�ֵ��������
			{
				json_null = 0,
				json_bool,
				json_int,
				json_double,
				json_string,
				json_array,
				json_object
			};
			//Json���캯��	eg�� int i -��Json j��
			Json();
			Json(bool value);
			Json(int value);
			Json(double value);
			Json(const char* value);//����c����ַ���
			Json(const string& value);
			Json(Type type);
			Json(const Json& other);//���ƹ��캯��
			//���ض�Ӧ�������������Json�����ֵת��Ϊ��Ӧ���͵�ֵ	eg��Json j -��int i���˴����˼������Ū��
			operator bool();
			operator int();
			operator double();
			operator string();
			//Json����Ϊ��������ʱ�������������ֲ�����ʹ��������ͨ����һ������
			Json& operator [] (int index);
			void append(const Json& other);
			//����Json�ж������͵��±������
			Json& operator [] (const char* key);
			Json& operator [] (const string& key);
			//ΪJson�����������ظ�ֵ�����
			void operator= (const Json& other);
			//ΪJson������== and !=
			bool operator== (const Json& other);
			bool operator!= (const Json& other);
			//��string��ʽ����Json�����ֵ����Դ��ָ����������
			string str() const;

			void copy(const Json& other);
			//����ڴ�й¶���⣿����
			void clear();

			typedef std::vector<Json>::iterator it;//��������������ڱ�������
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
			union Value					//���ϣ�һ��������ࣩ���ÿ�������д��ֵ
			{
				bool m_bool;
				int m_int;
				double m_double;
				std::string* m_string;//���stringֵ��ָ��
				std::vector<Json>* m_array;//�������ָ��
				std::map<string, Json>* m_object;//��Ŷ���ָ��
			};
			Type m_type;
			Value m_value;
		};
	}
}
