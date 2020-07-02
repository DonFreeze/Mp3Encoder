#pragma once

#include <string>
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
