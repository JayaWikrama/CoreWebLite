/*
 * $Id: http-header.hpp,v 1.0.0 2024/10/31 22:31:12 Jaya Wikrama Exp $
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
 * @brief This file defines the HttpHeader class, which provides functionalities
 *        for constructing and parsing HTTP headers element (multiple row).
 *
 * @version 1.0.0
 * @date 2024-10-31
 * @author Jaya Wikrama
 */

#ifndef __HTTP_HEADER_HPP__
#define __HTTP_HEADER_HPP__

#include <string> 
#include "http-header-node.hpp"

class HTTPHeader {
  public:
    HeaderNode *node;

    /**
    * @brief Default constructor for NULL node.
    *
    * This method is responsible for create blank HTTP Header.
    */
    HTTPHeader();

    /**
    * @brief Custom constructor for Integer data.
    *
    * This method is responsible for create new HTTP Header wich automatically create one node with integer data value.
    */
    HTTPHeader(HeaderNode::headerField_t field, int data);

    /**
    * @brief Custom constructor for boolean data.
    *
    * This method is responsible for create new HTTP Header wich automatically create one node with boolean data value.
    */
    HTTPHeader(HeaderNode::headerField_t field, bool data);

    /**
    * @brief Custom constructor for cstring data.
    *
    * This method is responsible for create new HTTP Header wich automatically create one node with cstring data value.
    */
    HTTPHeader(HeaderNode::headerField_t field, const char *data);

    /**
    * @brief Custom constructor for string data.
    *
    * This method is responsible for create new HTTP Header wich automatically create one node with string data value.
    */
    HTTPHeader(HeaderNode::headerField_t field, const std::string data);

    /**
    * @brief Custom constructor for Complete HTTP Header Payload.
    *
    * This method is responsible for create new HTTP Header wich automatically parse the input to linked list form.
    */
    HTTPHeader(const std::string httpHeaderPayload);

    /**
    * @brief Destructor for HTTP Header class.
    *
    * Release all available nodes.
    */
    ~HTTPHeader();

    /**
    * @brief Append new node with Integer data.
    *
    * This method is responsible to append one node with integer data value.
    *
    * @return `true` in success.
    * @return `false` on fail.
    */
    bool append(HeaderNode::headerField_t field, int data);

    /**
    * @brief Append new node with boolean data.
    *
    * This method is responsible to append one node with boolean data value.
    *
    * @return `true` in success.
    * @return `false` on fail.
    */
    bool append(HeaderNode::headerField_t field, bool data);

    /**
    * @brief Append new node with cstring data.
    *
    * This method is responsible to append one node with cstring data value.
    *
    * @return `true` in success.
    * @return `false` on fail.
    */
    bool append(HeaderNode::headerField_t field, const char *data);

    /**
    * @brief Append new node with string data.
    *
    * This method is responsible to append one node with string data value.
    *
    * @return `true` in success.
    * @return `false` on fail.
    */
    bool append(HeaderNode::headerField_t field, const std::string data);

    /**
    * @brief Gets HTTP Header as String.
    *
    * This method is responsible to create HTTP Header Payload form all available nodes.
    *
    * @return HTTP Header payload as string
    */
    std::string getPayload();

  private:
    valueType_t vType;
    void *data;
    headerField_t field;
};

#endif