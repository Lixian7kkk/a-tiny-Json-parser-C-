#pragma once
#include "my_json.h"
#include <string>
using namespace std;
namespace lixiang {
	namespace json {

		class Parser {
		public:
			Parser();
			void load(const string& str);//���ؼ����������ַ���

			Json parse();//����������Json���Ͷ���
		private:
			void skip_while_space();
			char get_next_token();//���ַ���ȡ
			//��������Json����Ĳ�ͬ����
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