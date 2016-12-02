/**
 * @file HTTP.h
 * 
 * @class HTTP
 *
 * @brief HTTP packet creator
 *        
 * This Class is responsible for handling the message buffer containing
 * a HTTP request. After parsing the request the user can ask the class
 * to process the message with the file selected under the HTTP Header
 * for GET. A JSON message telling if the file was successfully added or 
 * removed for POST, PUT and DELETE.
 *
 * @license MIT License
 * 
 * Copyright (c) 2016 Caio Marcelo Campoy Guedes
 * 					  Nycholas de Sousa
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author Caio Marcelo Campoy Guedes <caiomcg@gmail.com>
 * @author Nycholas de Sousa <nycholas@live.com>
 */

#ifndef HTTP_H
#define HTTP_H

// C++ Headers
//---------------------------------------------------------------------------------------------
#include <iostream>   		  // C++ standard I/O.
#include <regex> 	  		  // Regular expressions.
#include <functional> 		  // std::function.
#include <fstream> 	  		  // File Read/Write.
#include <string> 	  		  // std::string.
//---------------------------------------------------------------------------------------------

// C Headers
//---------------------------------------------------------------------------------------------
#include <ctime> 	  		  // System time.
#include <cstdio> 	  		  // C standard I/O.
#include <cstring> 	  		  // memcpy.
//---------------------------------------------------------------------------------------------

// Custom Headers
//---------------------------------------------------------------------------------------------
#include "../include/Utils.h" // Utility class.
//---------------------------------------------------------------------------------------------


// Macros
//---------------------------------------------------------------------------------------------
#define MAX_SIZE 1024000 	  // Maximum buffer size.
//---------------------------------------------------------------------------------------------

/**
 * @brief HTTP status.
 *
 * A set of possible status for the server.
 */
enum HTTPStatus{
	OK=200,
	PARTIAL_CONTENT=206,
	FOUND = 302,
	NOT_MODIFIED = 304,
	TEMPORARY_REDIRECT = 307,
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTD = 501,
	SERVICE_UNAVEILABLE = 503,
	PERMISSION_DENIED = 550
};

class HTTP {
private:
	size_t   _packetBytes;   		// Packet bytes size.
	uint8_t*  _packetBuffer; 		// Paket buffer.

	size_t   _fileBytes;	 		// File bytes size.
	uint8_t* _fileBuffer;		    // File buffer.

	std::string _httpType;  		// Type of HTTP request.

	std::string _requestedFile; 	// The requested file.
	std::string _requestedFileType; // The requested file type.

	std::string _response; 			// Header response.

	/**
	 * @brief Find the path of the requested file.
	 * @details Parse the HTTP request header and
	 * fetch the path to the file the user requested.
	 * 
	 * @param in The header.
	 * @param message The delimiter.
	 * 
	 * @return The path to the location.
	 */
	std::string findPath(std::string& in, std::string message);

	/**
	 * @brief Returns the formatted system date.
	 * @details Returns the formatted system date
	 * required by HTTP headers.
	 * 
	 * @return The date as a string.
	 */
	std::string httpDate() const;

public:
	/**
	 * @brief Default Constructor.
	 */
	HTTP();

	/**
	 * @brief Default destructor.
	 */
	~HTTP();

	/**
	 * @brief Check if a file exist.
	 * @details Check if a file exist and fetch it to the memory.
	 * 
	 * @param filePath The path to the file.
	 * @return True if successfuly added.
	 */
	bool fileExistsAndAd(const std::string filePath);

	/**
	 * @brief Check if a file exists.
	 * @details Simple check for the PUT and DELETE requests.
	 * 
	 * @param filePath Path to the file.
	 * @return True if the file exists.
	 */
	bool onlyFileExists(const std::string filePath);

	/**
	 * @brief Process the request.
	 * @details Process the request and generates 
	 * the response packet.
	 * 
	 * @param buffer The buffer to be processed.
	 * @param function The calback to handle the request types.
	 * 
	 * @return The packet or nullptr if an error occured.
	 */
	uint8_t* processMessage(const uint8_t* buffer, std::function<uint8_t* (const std::string&, const std::string, std::string&)> function);
	
	/**
	 * @brief Create the response header.
	 * @details Create a HTTP response header with the desired status code.
	 * 
	 * @param statusCode The status code to be used.
	 */
	void createResponseHeader(const int statusCode);

	/**
	 * @brief Prepare the packet.
	 * @details Prepare the packet with the 
	 * generated HTTP header and a file if
	 * the request is GET.
	 * 
	 * @return The generated packet.
	 */
	uint8_t* preparePacket();

	/**
	 * @brief Returns the packet size.
	 * @details Returns the packet size in bytes.
	 * 
	 * @return The total of bytes for the packet.
	 */
	size_t getPacketSize() const;

	/**
	 * @brief Returns the HTTP header.
	 * @details Returns the HTTP header as a std::string.
	 * 
	 * @return The header.
	 */
	std::string getHTTPHeader() const;
};

#endif // Define HTTP_H