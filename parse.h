#pragma once
#include "my_json.h"
#include <string>
using namespace std;
namespace lixiang {
	namespace json {

		class Parser {
		public:
			Parser();
			void load(const string& str);//加载即将解析的字符串

			Json parse();//解析并返回Json类型对象
		private:
			void skip_while_space();
			char get_next_token();//逐字符读取
			//解析各种Json对象的不同类型
			Json parse_null();
			Json parse_bool();
			Json parse_number();
			string parse_string();
			Json parse_array();
			Json parse_object();
		private:
			string m_str;
			int m_idx;
		};
	}
}