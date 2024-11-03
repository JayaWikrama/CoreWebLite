/*
 * $Id: http-header.hpp,v 1.0.0 2024/10/24 22:31:12 Jaya Wikrama Exp $
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
#include <iomanip>
#include "http-header-node.hpp"

const char *fieldName[] = {
  "Unknown",
  "Accept",
  "Accept-Charset",
  "Accept-Encoding",
  "Accept-Language",
  "Authorization",
  "Cache-Control",
  "Connection",
  "Cookie",
  "Expect",
  "From",
  "Host",
  "If-Match",
  "If-Modified-Since",
  "If-None-Match",
  "If-Unmodified-Since",
  "Max-Forwards",
  "Origin",
  "Pragma",
  "Proxy-Authorization",
  "Range",
  "Referer",
  "TE",
  "User-Agent",
  "Date",
  "Server",
  "Content-Length",
  "Content-Type",
  "Content-Encoding",
  "Content-Language",
  "Content-Disposition",
  "Last-Modified",
  "ETag",
  "Accept-Ranges",
  "Content-Location",
  "Content-Range",
  "Vary",
  "Age",
  "Expires",
  "Strict-Transport-Security",
  "Content-Security-Policy",
  "X-Content-Type-Options",
  "X-Frame-Options",
  "X-XSS-Protection",
  "Referrer-Policy",
  "Public-Key-Pins",
  "Expect-CT",
  "X-Content-Security-Policy",
  "X-Download-Options",
  "X-Permitted-Cross-Domain-Policies",
  "Location",
  "Proxy-Authenticate",
  "Set-Cookie",
  "Set-Cookie2",
  "Multi-Status",
  "Link",
  "Allow",
  "Retry-After",
  "Access-Control-Allow-Origin",
  "Access-Control-Allow-Methods",
  "Access-Control-Allow-Headers",
  "Access-Control-Expose-Headers",
  "Access-Control-Max-Age",
  "X-Forwarded-For",
  "X-Forwarded-Proto",
  "X-Real-IP",
  "Unknown"
};

/**
 * @brief Node constructor for Integer data.
 *
 * This method is responsible for create new node with integer data value.
 */
HeaderNode::HeaderNode(HeaderNode::headerField_t field, int data){
  this->field = field;
  this->vType = HeaderNode::VALUE_TYPE_NUMBER;
  this->data = (void *) (size_t) data;
  this->next = nullptr;
}

/**
 * @brief Node constructor for boolean data.
 *
 * This method is responsible for create new node with boolean data value.
 */
HeaderNode::HeaderNode(HeaderNode::headerField_t field, bool data){
  this->field = field;
  this->vType = HeaderNode::VALUE_TYPE_BOOLEAN;
  this->data = (data == 0 ? nullptr : (void *) 1);
  this->next = nullptr;
}

/**
 * @brief Node constructor for cstring data.
 *
 * This method is responsible for create new node with cstring data value.
 */
HeaderNode::HeaderNode(HeaderNode::headerField_t field, const char *data){
  this->field = field;
  this->vType = HeaderNode::VALUE_TYPE_TEXT;
  char *tmp = new char[strlen(data) + 1];
  if (tmp){
    strcpy(tmp, data);
    tmp[strlen(data)] = 0x00;
  }
  this->data = (void *) tmp;
  this->next = nullptr;
}

/**
 * @brief Node constructor for string data.
 *
 * This method is responsible for create new node with string data value.
 */
HeaderNode::HeaderNode(HeaderNode::headerField_t field, const std::string data){
  HeaderNode(field, data.c_str());
}

/**
 * @brief Node constructor for string field and string data.
 *
 * This method is responsible for create new node with string field and string data value.
 * This method will throw an error if input field is not match with available field list.
 */
HeaderNode::HeaderNode(const std::string field, const std::string data){
  int i = 0;
  for (i = 0; i < static_cast<int>(HeaderNode::SZ_TOTAL); i++){
    if (field.compare(fieldName[i]) == 0){
      HeaderNode(static_cast<HeaderNode::headerField_t>(i), data);
    }
  }
  if (i == static_cast<int>(HeaderNode::SZ_TOTAL)) throw std::runtime_error(std::string(__func__) + ": fail to create next node");
}

/**
 * @brief Node destructor.
 *
 * Release data pointer.
 */
HeaderNode::~HeaderNode(){
  if (this->vType == HeaderNode::VALUE_TYPE_TEXT){
    if (this->data != nullptr){
      char *tmp = (char *) (this->data);
      delete[] tmp;
      this->data = nullptr;
    }
  }
}

/**
 * @brief Gets the HTTP Header field name.
 *
 * This method is responsible for getting the HTTP Header field name as string.
 *
 * @return The HTTP Header field name as string.
 */
std::string HeaderNode::getFieldName() const {
  return std::string(fieldName[static_cast<int>(this->field)]);
}

/**
 * @brief Gets the HTTP Header field value.
 *
 * This method is responsible for getting the HTTP Header field value as string.
 *
 * @return The HTTP Header field value as string.
 */
std::string HeaderNode::getValue(){
  if (this->vType == HeaderNode::VALUE_TYPE_TEXT){
    return std::string((const char *) (this->data));
  }
  if (this->vType == HeaderNode::VALUE_TYPE_NUMBER){
    char tmp[16];
    memset(tmp, 0x00, sizeof(tmp));
    sprintf(tmp, "%lli", (long long) (this->data));
    return std::string(tmp);
  }
  if (this->data == 0) return std::string("false");
  return std::string("true");
}

/**
 * @brief Parse the HTTP Header node (single row).
 *
 * This method is responsible for getting parse the HTTP Header node (single row) to separate field name and field value.
 *
 * @return `true` in success.
 * @return `false` on fail.
 */
bool HeaderNode::parseRow(const char *headerRow, HeaderNode::headerField_t &field, std::string &data){
  char fieldX[64];
  int idx = 0;
  size_t length = strlen(headerRow);
  field = HeaderNode::UNKNOWN;
  /* parse field */
  if (headerRow[0] >= 'a' && headerRow[0] <= 'z'){
    fieldX[0] = (headerRow[0] - 'a') + 'A';
  }
  else {
    fieldX[0] = headerRow[0];
  }
  for (idx = 1; idx < length; idx++){
    if (headerRow[idx] == ':' || headerRow[idx] == ' ') break;
    if (headerRow[idx - 1] == '-'){
      if (headerRow[idx] >= 'a' && headerRow[idx] <= 'z'){
        fieldX[idx] = (headerRow[idx] - 'a') + 'A';
      }
      else {
        fieldX[idx] = headerRow[idx];
      }
    }
    else {
      fieldX[idx] = headerRow[idx];
    }
  }
  for (int i = 0; i < static_cast<int>(HeaderNode::SZ_TOTAL); i++){
    if (strcmp(fieldX, fieldName[i]) == 0){
      field = static_cast<HeaderNode::headerField_t>(i);
      break;
    }
  }
  /* get start position of value */
  do {
    idx++;
  } while (headerRow[idx] == ':' || headerRow[idx] == ' ');
  data = std::string(headerRow + idx);
  if (field == HeaderNode::UNKNOWN) return false;
  return true;
}

/**
 * @brief Overloading of `parseRow` method.
 *
 * This method is responsible for getting parse the HTTP Header node (single row) to separate field name and field value.
 *
 * @return `true` in success.
 * @return `false` on fail.
 */
bool HeaderNode::parseRow(const std::string headerRow, HeaderNode::headerField_t &field, std::string &data){
  return this->parseRow(headerRow.c_str(), field, data);
}