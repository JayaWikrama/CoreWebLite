/*
 * $Id: http-code.cpp,v 1.0.0 2024/10/24 22:31:12 Jaya Wikrama Exp $
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

#include "http-code.hpp"

/**
* @brief Set HTTP Status Code.
*
* This method is responsible for setting the HTTP Status Code.
*
* @param[in] code The HTTP Status Code.
*/
void HttpStatus::setHTTPStatusCode(HttpStatus::Code_t code){
  this->code = code;
}

/**
* @brief Gets the HTTP Status Code.
*
* This method is responsible for getting the HTTP Status Code.
*
* @return The HTTP Status Code.
*/
HttpStatus::Code_t HttpStatus::getHTTPStatusCode(){
  return this->code;
}

/**
* @brief Gets the HTTP Status Code as string.
*
* This method is responsible for getting the HTTP Status Code as string.
*
* @return The HTTP Status Code as string.
*/
std::string HttpStatus::getHTTPStatusCodeAsString(){
  switch (this->code) {
    // Informational Responses (100–199)
    case HttpStatus::CONTINUE: return "Continue";
    case HttpStatus::SWITCHING_PROTOCOLS: return "Switching Protocols";
    case HttpStatus::PROCESSING: return "Processing";
    case HttpStatus::EARLY_HINTS: return "Early Hints";
    // Successful Responses (200–299)
    case HttpStatus::OK: return "OK";
    case HttpStatus::CREATED: return "Created";
    case HttpStatus::ACCEPTED: return "Accepted";
    case HttpStatus::NON_AUTHORITATIVE_INFORMATION: return "Non-Authoritative Information";
    case HttpStatus::NO_CONTENT: return "No Content";
    case HttpStatus::RESET_CONTENT: return "Reset Content";
    case HttpStatus::PARTIAL_CONTENT: return "Partial Content";
    case HttpStatus::MULTI_STATUS: return "Multi-Status";
    case HttpStatus::ALREADY_REPORTED: return "Already Reported";
    case HttpStatus::IM_USED: return "IM Used";
    // Redirection Messages (300–399)
    case HttpStatus::MULTIPLE_CHOICES: return "Multiple Choices";
    case HttpStatus::MOVED_PERMANENTLY: return "Moved Permanently";
    case HttpStatus::FOUND: return "Found";
    case HttpStatus::SEE_OTHER: return "See Other";
    case HttpStatus::NOT_MODIFIED: return "Not Modified";
    case HttpStatus::USE_PROXY: return "Use Proxy";
    case HttpStatus::SWITCH_PROXY: return "Switch Proxy";
    case HttpStatus::TEMPORARY_REDIRECT: return "Temporary Redirect";
    case HttpStatus::PERMANENT_REDIRECT: return "Permanent Redirect";
    // Client Error Responses (400–499)
    case HttpStatus::BAD_REQUEST: return "Bad Request";
    case HttpStatus::UNAUTHORIZED: return "Unauthorized";
    case HttpStatus::PAYMENT_REQUIRED: return "Payment Required";
    case HttpStatus::FORBIDDEN: return "Forbidden";
    case HttpStatus::NOT_FOUND: return "Not Found";
    case HttpStatus::METHOD_NOT_ALLOWED: return "Method Not Allowed";
    case HttpStatus::NOT_ACCEPTABLE: return "Not Acceptable";
    case HttpStatus::PROXY_AUTHENTICATION_REQUIRED: return "Proxy Authentication Required";
    case HttpStatus::REQUEST_TIMEOUT: return "Request Timeout";
    case HttpStatus::CONFLICT: return "Conflict";
    case HttpStatus::GONE: return "Gone";
    case HttpStatus::LENGTH_REQUIRED: return "Length Required";
    case HttpStatus::PRECONDITION_FAILED: return "Precondition Failed";
    case HttpStatus::PAYLOAD_TOO_LARGE: return "Payload Too Large";
    case HttpStatus::URI_TOO_LONG: return "URI Too Long";
    case HttpStatus::UNSUPPORTED_MEDIA_TYPE: return "Unsupported Media Type";
    case HttpStatus::RANGE_NOT_SATISFIABLE: return "Range Not Satisfiable";
    case HttpStatus::EXPECTATION_FAILED: return "Expectation Failed";
    case HttpStatus::IM_A_TEAPOT: return "I'm a teapot";
    case HttpStatus::MISDIRECTED_REQUEST: return "Misdirected Request";
    case HttpStatus::UNPROCESSABLE_ENTITY: return "Unprocessable Entity";
    case HttpStatus::LOCKED: return "Locked";
    case HttpStatus::FAILED_DEPENDENCY: return "Failed Dependency";
    case HttpStatus::TOO_EARLY: return "Too Early";
    case HttpStatus::UPGRADE_REQUIRED: return "Upgrade Required";
    case HttpStatus::PRECONDITION_REQUIRED: return "Precondition Required";
    case HttpStatus::TOO_MANY_REQUESTS: return "Too Many Requests";
    case HttpStatus::REQUEST_HEADER_FIELDS_TOO_LARGE: return "Request Header Fields Too Large";
    case HttpStatus::UNAVAILABLE_FOR_LEGAL_REASONS: return "Unavailable For Legal Reasons";
    // Server Error Responses (500–599)
    case HttpStatus::INTERNAL_SERVER_ERROR: return "Internal Server Error";
    case HttpStatus::NOT_IMPLEMENTED: return "Not Implemented";
    case HttpStatus::BAD_GATEWAY: return "Bad Gateway";
    case HttpStatus::SERVICE_UNAVAILABLE: return "Service Unavailable";
    case HttpStatus::GATEWAY_TIMEOUT: return "Gateway Timeout";
    case HttpStatus::HTTP_VERSION_NOT_SUPPORTED: return "HTTP Version Not Supported";
    case HttpStatus::VARIANT_ALSO_NEGOTIATES: return "Variant Also Negotiates";
    case HttpStatus::INSUFFICIENT_STORAGE: return "Insufficient Storage";
    case HttpStatus::LOOP_DETECTED: return "Loop Detected";
    case HttpStatus::NOT_EXTENDED: return "Not Extended";
    case HttpStatus::NETWORK_AUTHENTICATION_REQUIRED: return "Network Authentication Required";
  }
  return "Unknown Status Code";
}

/**
* @brief Overloading of getHTTPStatusCodeAsString method. Set the HTTP Status Code and gets the HTTP Status Code as string.
*
* This method is responsible for getting the HTTP Status Code as string.
*
* @param[in] code The HTTP Status Code.
* @return The HTTP Status Code as string.
*/
std::string HttpStatus::getHTTPStatusCodeAsString(HttpStatus::Code_t code){
  this->code = code;
  return this->getHTTPStatusCodeAsString();
}