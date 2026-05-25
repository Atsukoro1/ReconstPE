#pragma once

#include <windows.h>

#include "imgui.h"

#include "../PEParser.h"
#include "../Formatting.h"

// Tables
#include "GeneralTable.h"
#include "DOSTable.h"
#include "StringsTable.h"
#include "OptionalTable.h"
#include "ImportTable.h"
#include "SectionTable.h"
#include "FileTable.h"
#include "RelocationsTable.h"
#include "ResourcesTable.h"

// Other components
#include "TopBar.h"

enum Window 
{
    General,
    DOSHeader,
    FileHeader,
    OptionalHeader,
    SectionHeaders,
    Import,
    Resources, 
    RelocationBlocks,
    Strings
};

void RenderLoop(PEParser& parser);