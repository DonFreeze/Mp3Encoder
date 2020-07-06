/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#pragma once

#include <string>

using namespace std;
namespace mp3encoder
{
    class FileName
    {
        public:
            FileName( string path, string name) : path(path), name(name) {}
            inline string getNameWav() { return this->name; }
            string getNameWavWithPath();
            string getNameMp3WithPath();
        private:
            string path;
            string name;
    };

}
