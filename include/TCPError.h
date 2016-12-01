/**
 * @file TCPError.h
 *
 * @brief Exceptions for the TCP class.
 *        
 * Class responsible for error management.
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

#ifndef TCP_ERROR_H
#define TCP_ERROR_H

// C++ Headers
//---------------------------------------------------------------------------------------------
#include <stdexcept> // Standard exception.
#include <exception> // C++ exception.
#include <string>	 // C++ string.
//---------------------------------------------------------------------------------------------

class TCPError:  public std::runtime_error{
public:
	/**
	 * @brief Default constructor.
	 */
	TCPError();
	/**
	 * @brief Custom constructor.
	 * 
	 * @param msg The message to be thrown with the error.
	 */
	TCPError(std::string msg);
};

#endif // define TCP_ERROR_H