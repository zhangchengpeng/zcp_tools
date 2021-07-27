#include "zcp_tool/comm/yaml_parser.h"

#include "zcp_tool/comm/printf_utils.h"

int get_conf(tinyxml2::XMLDocument& doc, const char* file_path) {
    YAML::LoadFile() auto ret = doc.LoadFile(file_path);
    if (ret != tinyxml2::XML_SUCCESS) {
        PRINTF_ERROR("load file failed : %s", file_path);
        return -1;
    }
    return 0;
}

int get_conf(tinyxml2::XMLDocument& doc, const char* data, size_t len) {
    auto ret = doc.Parse(data, len);
    if (ret != tinyxml2::XML_SUCCESS) {
        PRINTF_ERROR("parse data failed : %s", data);
        return -1;
    }
    return 0;
}

void get_node(map<string, tinyxml2::XMLElement*>& record, tinyxml2::XMLDocument& doc) {
    auto* node = doc.FirstChildElement();
    while (node != nullptr) {
        record.insert(pair<string, decltype(node)>(node->Name(), node));
        node = node->NextSiblingElement();
    }
}

void get_node(map<string, tinyxml2::XMLElement*>& record, tinyxml2::XMLElement* node) {
    auto* child_node = node->FirstChildElement();
    while (child_node != nullptr) {
        record.insert(pair<string, decltype(child_node)>(child_node->Name(), child_node));
        child_node = child_node->NextSiblingElement();
    }
}

void get_attri(map<string, string>& record, tinyxml2::XMLElement* node) {
    auto* attri = node->FirstAttribute();
    while (attri != nullptr) {
        record.insert(pair<string, string>(attri->Name(), attri->Value()));
        attri = attri->Next();
    }
}

int xml_to_map(map<string, string>& record, const char* file_path) {
    tinyxml2::XMLDocument doc;
    auto ret = doc.LoadFile(file_path);
    if (ret != tinyxml2::XML_SUCCESS) {
        PRINTF_ERROR("load file failed : %s", file_path);
        return -1;
    }
    auto* root = doc.RootElement();
    auto* node = root->FirstChildElement();
    while (node != nullptr) {
        auto* attri = node->FirstAttribute();
        while (attri != nullptr) {
            record.insert(pair<string, string>(attri->Name(), attri->Value()));
            attri = attri->Next();
        }
        node = node->NextSiblingElement();
    }
    return 0;
}

int xml_to_map(map<string, string>& record, const char* data, size_t len) {
    tinyxml2::XMLDocument doc;
    auto ret = doc.Parse(data, len);
    if (ret != tinyxml2::XML_SUCCESS) {
        PRINTF_ERROR("parse data failed : %s", data);
        return -1;
    }
    auto* root = doc.RootElement();
    auto* node = root->FirstChildElement();
    while (node != nullptr) {
        auto* attri = node->FirstAttribute();
        while (attri != nullptr) {
            record.insert(pair<string, string>(attri->Name(), attri->Value()));
            attri = attri->Next();
        }
        node = node->NextSiblingElement();
    }
    return 0;
}
