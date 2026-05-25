#pragma once

#include <windows.h>
#include <string>

#include "imgui.h"

#include "../PEParser.h"

std::string OpenExeFileDialog(char* file_name);
void RenderTopBar(PEParser& parser, char* pe_file_buffer);