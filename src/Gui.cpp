#include "Gui.h"

const char *EXE_PATH = "C:\\Users\\Jakub\\AppData\\Local\\exodus\\Exodus.exe";

void RenderLoop()
{
    if (ImGui::Button("Parse PE"))
    {
        PEParser parser = PEParser();

        DWORD parsing_res = parser.from_disk((char *)EXE_PATH);
        if (parsing_res != PE_FILE_SUCCESS)
        {
            std::cerr << "[!] Failed to parse, error code: " << parsing_res << std::endl;
        }
    }
}