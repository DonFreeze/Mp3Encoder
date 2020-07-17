/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#pragma once

#include <vector>
#include "FileName.h"

using namespace std;

namespace mp3encoder
{
    class FileNameStore
    {
        public:
            void storeFileName( FileName& fileName );
            inline int getNumberOfFiles() { return this->fileNameList.size(); }
            FileName* getNextFileNamePtr();
        private:
            vector< FileName* > fileNameList;
    };
}
