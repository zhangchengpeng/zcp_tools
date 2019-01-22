#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include <string>
#include <map>
using namespace std;

int file_to_json(string &data, const char *file_path);
int json_to_map(map<string, string> &record, string &data);

#endif