/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#pragma once

#include <string>


namespace mp3encoder
{
    class FileName
    {
        public:
            FileName( const std::string path, const std::string name) : path(path), name(name) {}
            std::string getWavWithPath();
            std::string getMp3WithPath();
            std::string getWav();
            std::string getMp3();
        private:
            const std::string path;
            const std::string name;
    };

}
