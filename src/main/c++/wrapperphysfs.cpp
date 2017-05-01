/*
 * This file is part of the Yildiz-Engine project, licenced under the MIT License  (MIT)
 *
 * Copyright (c) 2017 Grégory Van den Borre
 *
 * More infos available: https://www.yildiz-games.be
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without
 * limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT  HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  SOFTWARE.
 */

#include <iostream>
#include "wrapperphysfs.hpp"
#include "OpenAlException.h"
#include "stdafx.h"

/**
*@author Grégory Van den Borre
*/

yz::physfs::physfs(const char* filename){
    LOG_FUNCTION
    this->fileName = filename;
    this->file = PHYSFS_openRead(this->fileName);
    if (this->file == NULL){
        throw yz::OpenAlException("File not found");
    }
}

yz::physfs::~physfs(){
    LOG_FUNCTION
    if (PHYSFS_close(file) == 0 ){
        std::cout << PHYSFS_getLastError() << std::endl;
    }
}

int yz::physfs::read(char* data, int count){
    LOG_FUNCTION
    PHYSFS_sint64 read = PHYSFS_read(file, data, 1, count);
    if (read == -1){
        throw yz::OpenAlException("Error reading file");
    }
    return read;
}

int yz::physfs::seek(int position){
    LOG_FUNCTION
    if ( PHYSFS_seek(file, position) == 0 ){
        std::cout << PHYSFS_getLastError() << std::endl;
        return -1;
    }
    return position;
}

int yz::physfs::tell(){
    LOG_FUNCTION
    int position = PHYSFS_tell(this->file);
    if (position == -1){
        std::cout << PHYSFS_getLastError() << std::endl;
    }
    return position;
}

int yz::physfs::getSize(){
    LOG_FUNCTION
    int size = PHYSFS_fileLength(file);
    if (size == -1){
        std::cout << PHYSFS_getLastError() << std::endl;
    }
    return size;
}
