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