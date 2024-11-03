/*
 * $Id: http-header-node.hpp,v 1.0.0 2024/10/24 22:31:12 Jaya Wikrama Exp $
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

/**
 * @file
 * @brief This file defines the HttpHeader Nodes class (Nodes for Linked List of Header), which provides functionalities
 *        for constructing and parsing HTTP headers element (single row).
 *
 * @version 1.0.0
 * @date 2024-10-24
 * @author Jaya Wikrama
 */

#ifndef __HTTP_HEADER_NODE_HPP__
#define __HTTP_HEADER_NODE_HPP__

#include <string>

class HeaderNode {
  public:
    typedef enum _valueType_t {
      VALUE_TYPE_NUMBER,
      VALUE_TYPE_BOOLEAN,
      VALUE_TYPE_TEXT
    } valueType_t;

    typedef enum _headerField_t {
      UNKNOWN = 0,
      // General Request Headers
      ACCEPT,
      ACCEPT_CHARSET,
      ACCEPT_ENCODING,
      ACCEPT_LANGUAGE,
      AUTHORIZATION,
      CACHE_CONTROL,
      CONNECTION,
      COOKIE,
      EXPECT,
      FROM,
      HOST,
      IF_MATCH,
      IF_MODIFIED_SINCE,
      IF_NONE_MATCH,
      IF_UNMODIFIED_SINCE,
      MAX_FORWARDS,
      ORIGIN,
      PRAGMA,
      PROXY_AUTHORIZATION,
      RANGE,
      REFERER,
      TE,
      USER_AGENT,
      // General Response Headers
      DATE,
      SERVER,
      CONTENT_LENGTH,
      CONTENT_TYPE,
      CONTENT_ENCODING,
      CONTENT_LANGUAGE,
      CONTENT_DISPOSITION,
      LAST_MODIFIED,
      ETAG,
      ACCEPT_RANGES,
      CONTENT_LOCATION,
      CONTENT_RANGE,
      VARY,
      // Caching Headers
      CACHE_CONTROL_H,
      EXPIRES,
      PRAGMA_H,
      AGE,
      // Security Headers
      STRICT_TRANSPORT_SECURITY,
      CONTENT_SECURITY_POLICY,
      X_CONTENT_TYPE_OPTIONS,
      X_FRAME_OPTIONS,
      X_XSS_PROTECTION,
      REFERRER_POLICY,
      PUBLIC_KEY_PINS,
      EXPECT_CT,
      X_CONTENT_SECURITY_POLICY,
      X_DOWNLOAD_OPTIONS,
      X_PERMITTED_CROSS_DOMAIN_POLICIES,
      // Redirection Headers
      LOCATION,
      PROXY_AUTHENTICATE,
      // Cookies
      SET_COOKIE,
      SET_COOKIE2,
      // Multi-Status Header (WebDAV)
      MULTI_STATUS,
      // Other Headers
      LINK,
      ALLOW,
      RETRY_AFTER,
      ACCESS_CONTROL_ALLOW_ORIGIN,
      ACCESS_CONTROL_ALLOW_METHODS,
      ACCESS_CONTROL_ALLOW_HEADERS,
      ACCESS_CONTROL_EXPOSE_HEADERS,
      ACCESS_CONTROL_MAX_AGE,
      X_FORWARDED_FOR,
      X_FORWARDED_PROTO,
      X_REAL_IP,
      SZ_TOTAL
    } headerField_t;

    HeaderNode *next;

    /**
    * @brief Node constructor for Integer data.
    *
    * This method is responsible for create new node with integer data value.
    */
    HeaderNode(HeaderNode::headerField_t field, int data);

    /**
    * @brief Node constructor for boolean data.
    *
    * This method is responsible for create new node with boolean data value.
    */
    HeaderNode(HeaderNode::headerField_t field, bool data);

    /**
    * @brief Node constructor for cstring data.
    *
    * This method is responsible for create new node with cstring data value.
    */
    HeaderNode(HeaderNode::headerField_t field, const char *data);

    /**
    * @brief Node constructor for string data.
    *
    * This method is responsible for create new node with string data value.
    */
    HeaderNode(HeaderNode::headerField_t field, const std::string data);

    /**
    * @brief Node constructor for string field and string data.
    *
    * This method is responsible for create new node with string field and string data value.
    * This method will throw an error if input field is not match with available field list.
    */
    HeaderNode(const std::string field, const std::string data);

    /**
    * @brief Node destructor.
    *
    * Release data pointer.
    */
    ~HeaderNode();

    /**
    * @brief Gets the HTTP Header field name.
    *
    * This method is responsible for getting the HTTP Header field name as string.
    *
    * @return The HTTP Header field name as string.
    */
    std::string getFieldName() const;

    /**
    * @brief Gets the HTTP Header field value.
    *
    * This method is responsible for getting the HTTP Header field value as string.
    *
    * @return The HTTP Header field value as string.
    */
    std::string getValue();

    /**
    * @brief Parse the HTTP Header node (single row).
    *
    * This method is responsible for getting parse the HTTP Header node (single row) to separate field name and field value.
    *
    * @return `true` in success.
    * @return `false` on fail.
    */
    bool parseRow(const char *headerRow, HeaderNode::headerField_t &field, std::string &data);

    /**
    * @brief Overloading of `parseRow` method.
    *
    * This method is responsible for getting parse the HTTP Header node (single row) to separate field name and field value.
    *
    * @return `true` in success.
    * @return `false` on fail.
    */
    bool parseRow(const std::string headerRow, HeaderNode::headerField_t &field, std::string &data);

  private:
    valueType_t vType;
    void *data;
    headerField_t field;
};

#endif