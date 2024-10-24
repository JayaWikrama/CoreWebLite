/*
 * $Id: http-code.hpp,v 1.0.0 2024/10/24 22:31:12 Jaya Wikrama Exp $
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
 * @brief Definition of the enumeration for HTTP Status Codes.
 *
 * This enumeration includes all HTTP status codes in accordance with the
 * specifications of RFC 7231 and related standards. These status codes are used
 * to indicate the result of an HTTP request and provide information about the status
 * of the server or client request.
 *
 * @note You can use this enumeration to handle HTTP status codes in a structured
 *     manner within your application.
 *
 * @enum HttpStatusCode
 * @var HttpStatusCode::CONTINUE
 * Status 100: The request has been received and the client can continue.
 *
 * @var HttpStatusCode::SWITCHING_PROTOCOLS
 * Status 101: The client and server are switching to a different protocol.
 *
 * @var HttpStatusCode::OK
 * Status 200: The request has been successfully processed.
 *
 * @var HttpStatusCode::CREATED
 * Status 201: A new resource has been successfully created.
 *
 * @var HttpStatusCode::ACCEPTED
 * Status 202: The request has been accepted for processing, but not yet completed.
 *
 * @var HttpStatusCode::BAD_REQUEST
 * Status 400: The request could not be processed due to a client error.
 *
 * @var HttpStatusCode::UNAUTHORIZED
 * Status 401: Authentication is required and has failed or has not been provided.
 *
 * @var HttpStatusCode::FORBIDDEN
 * Status 403: Access is denied to the requested resource.
 *
 * @var HttpStatusCode::NOT_FOUND
 * Status 404: The requested resource could not be found.
 *
 * @var HttpStatusCode::INTERNAL_SERVER_ERROR
 * Status 500: An error occurred on the server while processing the request.
 *
 * @var HttpStatusCode::NOT_IMPLEMENTED
 * Status 501: The server does not recognize the request method.
 *
 * @var HttpStatusCode::SERVICE_UNAVAILABLE
 * Status 503: The service is unavailable, the server may be busy or down.
 *
 * @var HttpStatusCode::GATEWAY_TIMEOUT
 * Status 504: The server, while acting as a gateway, did not receive a timely response.
 *
 * And many more status codes are available.
 *
 * @version 1.0.0
 * @date 2024-10-24
 * @author Jaya Wikrama
 */

#ifndef __HTTP_CODE_HPP__
#define __HTTP_CODE_HPP__

#include <string>

class HttpStatus {
  public:
    typedef enum _Code_t {
      // Informational Responses (100–199)
      CONTINUE = 100,
      SWITCHING_PROTOCOLS = 101,
      PROCESSING = 102,
      EARLY_HINTS = 103,
      // Successful Responses (200–299)
      OK = 200,
      CREATED = 201,
      ACCEPTED = 202,
      NON_AUTHORITATIVE_INFORMATION = 203,
      NO_CONTENT = 204,
      RESET_CONTENT = 205,
      PARTIAL_CONTENT = 206,
      MULTI_STATUS = 207,
      ALREADY_REPORTED = 208,
      IM_USED = 226,
      // Redirection Messages (300–399)
      MULTIPLE_CHOICES = 300,
      MOVED_PERMANENTLY = 301,
      FOUND = 302,
      SEE_OTHER = 303,
      NOT_MODIFIED = 304,
      USE_PROXY = 305,
      SWITCH_PROXY = 306,
      TEMPORARY_REDIRECT = 307,
      PERMANENT_REDIRECT = 308,
      // Client Error Responses (400–499)
      BAD_REQUEST = 400,
      UNAUTHORIZED = 401,
      PAYMENT_REQUIRED = 402,
      FORBIDDEN = 403,
      NOT_FOUND = 404,
      METHOD_NOT_ALLOWED = 405,
      NOT_ACCEPTABLE = 406,
      PROXY_AUTHENTICATION_REQUIRED = 407,
      REQUEST_TIMEOUT = 408,
      CONFLICT = 409,
      GONE = 410,
      LENGTH_REQUIRED = 411,
      PRECONDITION_FAILED = 412,
      PAYLOAD_TOO_LARGE = 413,
      URI_TOO_LONG = 414,
      UNSUPPORTED_MEDIA_TYPE = 415,
      RANGE_NOT_SATISFIABLE = 416,
      EXPECTATION_FAILED = 417,
      IM_A_TEAPOT = 418,
      MISDIRECTED_REQUEST = 421,
      UNPROCESSABLE_ENTITY = 422,
      LOCKED = 423,
      FAILED_DEPENDENCY = 424,
      TOO_EARLY = 425,
      UPGRADE_REQUIRED = 426,
      PRECONDITION_REQUIRED = 428,
      TOO_MANY_REQUESTS = 429,
      REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
      UNAVAILABLE_FOR_LEGAL_REASONS = 451,
      // Server Error Responses (500–599)
      INTERNAL_SERVER_ERROR = 500,
      NOT_IMPLEMENTED = 501,
      BAD_GATEWAY = 502,
      SERVICE_UNAVAILABLE = 503,
      GATEWAY_TIMEOUT = 504,
      HTTP_VERSION_NOT_SUPPORTED = 505,
      VARIANT_ALSO_NEGOTIATES = 506,
      INSUFFICIENT_STORAGE = 507,
      LOOP_DETECTED = 508,
      NOT_EXTENDED = 510,
      NETWORK_AUTHENTICATION_REQUIRED = 511
    } Code_t;

    /**
    * @brief Set HTTP Status Code.
    *
    * This method is responsible for setting the HTTP Status Code.
    *
    * @param[in] code The HTTP Status Code.
    */
    void setHTTPStatusCode(HttpStatus::Code_t code);

    /**
    * @brief Gets the HTTP Status Code.
    *
    * This method is responsible for getting the HTTP Status Code.
    *
    * @return The HTTP Status Code.
    */
    HttpStatus::Code_t getHTTPStatusCode();

    /**
    * @brief Gets the HTTP Status Code as string.
    *
    * This method is responsible for getting the HTTP Status Code as string.
    *
    * @return The HTTP Status Code as string.
    */
    std::string getHTTPStatusCodeAsString();

    /**
    * @brief Overloading of getHTTPStatusCodeAsString method. Set the HTTP Status Code and gets the HTTP Status Code as string.
    *
    * This method is responsible for getting the HTTP Status Code as string.
    *
    * @param[in] code The HTTP Status Code.
    * @return The HTTP Status Code as string.
    */
    std::string getHTTPStatusCodeAsString(HttpStatus::Code_t code);

  protected:
    Code_t code;
};

#endif