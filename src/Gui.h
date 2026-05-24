#pragma once

#include "imgui.h"
#include "PEParser.h"
#include "Formatting.h"

enum Window 
{
    General,
    DOSHeader,
    FileHeader,
    OptionalHeader,
    SectionHeaders,
    Import,
    Resources, 
    RelocationBlocks
};

void RenderGeneralTable(PEParser &parser);
void RenderDOSHeaderTable(PEParser &parser);
void RenderFileHeaderTable(PEParser &parser);
void RenderOptionalHeaderTable(PEParser &parser);
void RenderSectionHeadersTable(PEParser &parser);
void RenderImportTable(PEParser &parser);
void RenderResourcesTable(PEParser &parser);
void RenderRelocationsTable(PEParser &parser);

void RenderLoop(PEParser& parser);