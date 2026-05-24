#include "Gui.h"

template <typename T>
char *Hex(T value)
{
    static thread_local char buffer[32];

    if constexpr (sizeof(T) <= 1)
    {
        std::snprintf(buffer, sizeof(buffer), "0x%02X", static_cast<unsigned int>(value));
    }
    else if constexpr (sizeof(T) <= 2)
    {
        std::snprintf(buffer, sizeof(buffer), "0x%04X", static_cast<unsigned int>(value));
    }
    else if constexpr (sizeof(T) <= 4)
    {
        std::snprintf(buffer, sizeof(buffer), "0x%08X", static_cast<unsigned int>(value));
    }
    else
    {
        std::snprintf(buffer, sizeof(buffer), "0x%016llX", static_cast<unsigned long long>(value));
    }

    return buffer;
}

static void SidebarItem(const char *label, Window page, Window &selected_window)
{
    if (ImGui::Selectable(label, selected_window == page))
    {
        selected_window = page;
    }
}

void PrintTableRow2(char *key, char *value)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(key);
    ImGui::TableNextColumn();
    ImGui::Text(value);
}

void RenderGeneralTable(PEParser &parser)
{
    ImGui::BeginTable("General", 2);
    PrintTableRow2("Is 64 bit", (char *)(parser.is_64bit ? "true" : "false"));
    PrintTableRow2("File path", parser.path);
    ImGui::EndTable();
}

void RenderDOSHeaderTable(PEParser &parser)
{
    ImGui::BeginTable("DosHeaderTable", 2);
    PrintTableRow2("e_cblp", Hex(parser.pe_dos_header->e_cblp));
    PrintTableRow2("e_cp", Hex(parser.pe_dos_header->e_cp));
    PrintTableRow2("e_cparhdr", Hex(parser.pe_dos_header->e_cparhdr));
    PrintTableRow2("e_crlc", Hex(parser.pe_dos_header->e_crlc));
    PrintTableRow2("e_cs", Hex(parser.pe_dos_header->e_cs));
    PrintTableRow2("e_csum", Hex(parser.pe_dos_header->e_csum));
    PrintTableRow2("e_ip", Hex(parser.pe_dos_header->e_ip));
    PrintTableRow2("e_lfanew", Hex(parser.pe_dos_header->e_lfanew));
    PrintTableRow2("e_lfarlc", Hex(parser.pe_dos_header->e_lfarlc));
    PrintTableRow2("e_magic", Hex(parser.pe_dos_header->e_magic));
    PrintTableRow2("e_maxalloc", Hex(parser.pe_dos_header->e_maxalloc));
    PrintTableRow2("e_minalloc", Hex(parser.pe_dos_header->e_minalloc));
    PrintTableRow2("e_oemid", Hex(parser.pe_dos_header->e_oemid));
    PrintTableRow2("e_oeminfo", Hex(parser.pe_dos_header->e_oeminfo));
    PrintTableRow2("e_ovno", Hex(parser.pe_dos_header->e_ovno));
    PrintTableRow2("e_sp", Hex(parser.pe_dos_header->e_sp));
    PrintTableRow2("e_ss", Hex(parser.pe_dos_header->e_ss));
    ImGui::EndTable();
}

void RenderFileHeaderTable(PEParser &parser)
{
    ImGui::BeginTable("FileHeaderTable", 2);
    ImGui::EndTable();
}

void RenderOptionalHeaderTable(PEParser &parser)
{
    ImGui::BeginTable("OptionalHeaderTable", 2);
    ImGui::EndTable();
}

void RenderSectionHeadersTable(PEParser &parser)
{
    ImGui::Text("Section Headers");
}

void RenderImportTable(PEParser &parser)
{
    ImGui::Text("Import table");
}

void RenderResourcesTable(PEParser &parser)
{
    ImGui::Text("Resources table");
}

void RenderRelocationsTable(PEParser &parser)
{
    ImGui::Text("Relocations table");
}

static void RenderSelectedTable(Window selected_window, PEParser &parser)
{
    switch (selected_window)
    {
    case Window::General:
        RenderGeneralTable(parser);
        break;

    case Window::DOSHeader:
        RenderDOSHeaderTable(parser);
        break;

    case Window::FileHeader:
        RenderFileHeaderTable(parser);
        break;

    case Window::OptionalHeader:
        RenderOptionalHeaderTable(parser);
        break;

    case Window::SectionHeaders:
        RenderSectionHeadersTable(parser);
        break;

    case Window::Import:
        RenderImportTable(parser);
        break;

    case Window::Resources:
        RenderResourcesTable(parser);
        break;

    case Window::RelocationBlocks:
        RenderRelocationsTable(parser);
        break;

    default:
        ImGui::Text("Unknown view");
        break;
    }
}

void RenderLoop(PEParser &parser)
{
    static char pe_file_buffer[1024] = "";
    static Window selected_window = Window::General;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open"))
            {
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Close file", nullptr, false, parser.parsed))
            {
                parser.parsed = false;
                pe_file_buffer[0] = '\0';
                selected_window = Window::General;
            }

            if (ImGui::MenuItem("Exit"))
            {
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    if (!parser.parsed)
    {
        ImGui::InputText("Location of the file", pe_file_buffer, sizeof(pe_file_buffer));

        if (ImGui::Button("Parse PE"))
        {
            DWORD parsing_res = parser.from_disk(pe_file_buffer);

            if (parsing_res != PE_FILE_SUCCESS)
            {
                std::cerr << "[!] Failed to parse, error code: " << parsing_res << std::endl;
            }
        }

        return;
    }

    ImGui::BeginChild("Sidebar", ImVec2(180, 0), true);

    SidebarItem("General", Window::General, selected_window);
    SidebarItem("DOS Header", Window::DOSHeader, selected_window);
    SidebarItem("File Header", Window::FileHeader, selected_window);
    SidebarItem("Optional Header", Window::OptionalHeader, selected_window);
    SidebarItem("Section Headers", Window::SectionHeaders, selected_window);
    SidebarItem("Imports", Window::Import, selected_window);
    SidebarItem("Resources", Window::Resources, selected_window);
    SidebarItem("Relocation blocks", Window::RelocationBlocks, selected_window);

    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("TableView", ImVec2(0, 0), true);

    RenderSelectedTable(selected_window, parser);

    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("HexView", ImVec2(200, 0), true);

    ImGui::EndChild();
}