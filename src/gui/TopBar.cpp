#include "TopBar.h"

std::string OpenExeFileDialog(char* file_name)
{
    OPENFILENAMEA ofn{};

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = file_name;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "Executable files (*.exe)\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = "Open file";
    ofn.Flags =
        OFN_PATHMUSTEXIST |
        OFN_FILEMUSTEXIST |
        OFN_NOCHANGEDIR |
        OFN_EXPLORER;

    if (GetOpenFileNameA(&ofn))
    {
        return file_name;
    }

    return {};
}


void RenderTopBar(PEParser& parser, char* pe_file_buffer)
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open"))
            {
                OpenExeFileDialog(pe_file_buffer);

                DWORD parsing_res = parser.from_disk(pe_file_buffer);

                if (parsing_res != PE_FILE_SUCCESS)
                {
                    std::cerr << "[!] Failed to parse, error code: " << parsing_res << std::endl;
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Close file", nullptr, false, parser.parsed))
            {
                parser.parsed = false;
                pe_file_buffer[0] = '\0';
                // selected_window = Window::General;
            }

            if (ImGui::MenuItem("Exit"))
            {
                PostQuitMessage(0);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}