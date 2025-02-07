/*
 * $Id: http-header.cpp,v 1.0.0 2024/10/31 22:31:12 Jaya Wikrama Exp $
 *
 * Copyright (c) 2024 Jaya Wikrama
 * jayawikrama89@gmail.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *  claim that you wrote the original software. If you use this software
 *  in a product, an acknowledgment in the product documentation would be
 *  appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *  misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <ctime>
#include <iostream>
#include "http-header.hpp"

#define MAX_HEAD_ROW 2048


long convertToUnixEpoch(const std::string &dateStr) {
  std::tm timeStruct = {};
  std::istringstream ss(dateStr);
  ss >> std::get_time(&timeStruct, "%a, %d %b %Y %H:%M:%S GMT");
  if (ss.fail()) {
    std::cerr << "Failed to parse date string." << std::endl;
    return -1;
  }
  // Set timezone to GMT
  timeStruct.tm_isdst = -1;
  return std::mktime(&timeStruct);
}

std::unordered_map<std::string, std::string> __parse(const std::string &input) {
  std::unordered_map<std::string, std::string> dataMap;
  std::istringstream stream(input);
  std::string line;
  while (std::getline(stream, line)) {
    if (line.length() > 512) break;
    size_t pos = line.find(": ");
    if (pos != std::string::npos) {
      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + 2);
      if (!value.empty() && value.back() == '\r') {
          value.pop_back();
      }
      dataMap[key] = value;
    }
    else if (line.find("HTTP") == 0) {
      if (!line.empty() && line.back() == '\r') {
          line.pop_back();
      }
      dataMap["Protocol"] = line;
    }
  }
  return dataMap;
}

/**
 * @brief Default constructor for NULL node.
 *
 * This method is responsible for create blank HTTP Header.
 */
HTTPHeader::HTTPHeader(){
  this->version = "1.1";
  this->code = HttpStatus::OK;
  this->node = nullptr;
}

/**
 * @brief Custom constructor for Integer data.
 *
 * This method is responsible for create new HTTP Header wich automatically create one node with integer data value.
 */
HTTPHeader::HTTPHeader(HeaderNode::headerField_t field, int data) : HTTPHeader::HTTPHeader() {
  this->node = new HeaderNode(field, data);
}

/**
 * @brief Custom constructor for boolean data.
 *
 * This method is responsible for create new HTTP Header wich automatically create one node with boolean data value.
 */
HTTPHeader::HTTPHeader(HeaderNode::headerField_t field, bool data) : HTTPHeader::HTTPHeader() {
  this->node = new HeaderNode(field, data);
}

/**
 * @brief Custom constructor for cstring data.
 *
 * This method is responsible for create new HTTP Header wich automatically create one node with cstring data value.
 */
HTTPHeader::HTTPHeader(HeaderNode::headerField_t field, const char *data) : HTTPHeader::HTTPHeader() {
  this->node = new HeaderNode(field, data);
}

/**
 * @brief Custom constructor for string data.
 *
 * This method is responsible for create new HTTP Header wich automatically create one node with string data value.
 */
HTTPHeader::HTTPHeader(HeaderNode::headerField_t field, const std::string data) : HTTPHeader::HTTPHeader() {
  this->node = new HeaderNode(field, data);
}

/**
 * @brief Custom constructor for Complete HTTP Header Payload.
 *
 * This method is responsible for create new HTTP Header wich automatically parse the input to linked list form.
 */
HTTPHeader::HTTPHeader(const std::string httpHeaderPayload){
  std::unordered_map<std::string, std::string> parsed = __parse(httpHeaderPayload);
  for (const auto &pair : parsed) {
    HeaderNode *next = nullptr;
    long tmp = 0;
    if (pair.first.compare("Protocol") == 0){
      /* Continue parsing protocol */
    }
    else if (pair.first.compare(fieldName[HeaderNode::DATE]) == 0){
      tmp = convertToUnixEpoch(pair.second);
      if (tmp == -1){
        throw std::runtime_error(std::string(__func__) + ": unknown time format");
      }
      next = new HeaderNode(pair.first, std::to_string(tmp));
    }
    else if (pair.first.compare(fieldName[HeaderNode::CONTENT_LENGTH]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::MAX_FORWARDS]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::AGE]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::RETRY_AFTER]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::ACCESS_CONTROL_MAX_AGE]) == 0
    ){
      next = new HeaderNode(pair.first, stoi(pair.second));
    }
    else if (pair.first.compare(fieldName[HeaderNode::EXPECT]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::IF_MODIFIED_SINCE]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::IF_UNMODIFIED_SINCE]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::STRICT_TRANSPORT_SECURITY]) == 0 ||
             pair.first.compare(fieldName[HeaderNode::X_XSS_PROTECTION]) == 0
    ){
      next = new HeaderNode(pair.first, (!pair.second.compare("true") || !pair.second.compare("True") || !pair.second.compare("TRUE")));
    }
    else {
      next = new HeaderNode(pair.first, pair.second);
    }
    if (next == nullptr) throw std::runtime_error(std::string(__func__) + ": fail to create next node");
    if (this->node == nullptr){
      this->node = next;
    }
    else {
      next->next = this->node;
      this->node = next;
    }
  }
}

/**
 * @brief Overloaded custom constructor for Complete HTTP Header Payload.
 *
 * This method is responsible for create new HTTP Header wich automatically parse the input to linked list form.
 */
HTTPHeader::HTTPHeader(const char *httpHeaderPayload){
  HTTPHeader(std::string(httpHeaderPayload));
}

/**
 * @brief Destructor for HTTP Header class.
 *
 * Release all available nodes.
 */
HTTPHeader::~HTTPHeader(){
  if (this->node == nullptr) return;
  HeaderNode *next = nullptr;
  while (this->node->next != nullptr){
    next = this->node->next;
    delete this->node;
    this->node = next;
  }
  delete this->node;
}