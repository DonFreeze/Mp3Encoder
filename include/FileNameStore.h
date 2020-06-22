#ifndef FILENAMESTORE_H
#define FILENAMESTORE_H

#include "FileName.h"
#include <string>
#include <vector>

namespace mp3Encoder
{
    class FileNameStore
    {
        public:
            FileNameStore( ) ;
            virtual ~FileNameStore();
            void storeFileName( FileName& fileName );
            inline int getNumberOfFiles() { return fileNameList.size(); }
            FileName& getNextFileName();
        private:
            std::vector< FileName > fileNameList;
         //   std::string directoryPath;

    };
}
#endif // FILENAMESTORE_H
