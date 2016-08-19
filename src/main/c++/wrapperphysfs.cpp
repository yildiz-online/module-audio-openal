//        This file is part of the Yildiz-Online project, licenced under the MIT License
//        (MIT)
//
//        Copyright (c) 2016 Grégory Van den Borre
//
//        More infos available: http://yildiz.bitbucket.org
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.

#include <iostream>
#include "../includes/wrapperphysfs.hpp"

/**
*@author Grégory Van den Borre
*/

YZ::physfs::physfs(const char *filename){
    file = PHYSFS_openRead(filename);
    error = false;
    if (file == NULL){
        std::cout << "Physfs file: " << filename <<" - "<< PHYSFS_getLastError() << std::endl;
        error = true;
    }
}

YZ::physfs::~physfs(){
    if (error){
        return;}
    if (PHYSFS_close(file) == 0 ){
        std::cout << PHYSFS_getLastError() << std::endl;
    }
}

int YZ::physfs::read(char *data, int size){
    if (error){
        return 0;
    }
    int readed = PHYSFS_read(file, data, 1, size);
    if (readed == -1){
        std::cout << PHYSFS_getLastError() << std::endl;
        return 0;
    }
    return readed;
}

int YZ::physfs::seek(int position){
    if (error){
        return -1;}
    if ( PHYSFS_seek(file, position) == 0 ){
        std::cout << PHYSFS_getLastError() << std::endl;
        return -1;
    }
    return position;
}

int YZ::physfs::tell(){
    if (error){
        return -1;}
    int position = PHYSFS_tell(file);
    if (position == -1){
        std::cout << PHYSFS_getLastError() << std::endl;
    }
    return position;
}

int YZ::physfs::getSize(){
    if (error){
        return -1;}
    int size = PHYSFS_fileLength(file);
    if (size == -1){
        std::cout << PHYSFS_getLastError() << std::endl;
    }
    return size;
}
