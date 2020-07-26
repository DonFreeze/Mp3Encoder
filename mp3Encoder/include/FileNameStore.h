/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#pragma once

#include <vector>
#include "FileName.h"

namespace mp3encoder
{
    class FileNameStore
    {
        public:
            void storeFileName( FileName& name );
            inline int getNumberOfFiles() { return names.size(); }
            FileName* pullNextNamePtr();

        private:
            std::vector<FileName*> names;
    };
}
