#include "Gui.h"

std::string OpenExeFileDialog()
{
    OPENFILENAMEA ofn{};
    char file_name[MAX_PATH] = "";

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

static void SidebarItem(const char *label, Window page, Window &selected_window)
{
    if (ImGui::Selectable(label, selected_window == page))
    {
        selected_window = page;
    }
}

static void CenterText(const char *text)
{
    float window_width = ImGui::GetWindowSize().x;
    float text_width = ImGui::CalcTextSize(text).x;

    ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
    ImGui::TextUnformatted(text);
}

void PrintIntro()
{
    const char *lines[] =
        {
            "-------------------------------------",
            " _____     _         _____ _____ ",
            "| __  |___| |___ ___|  _  |   __|",
            "|    -| -_| | . |  _|   __|   __|",
            "|__|__|___|_|___|___|__|  |_____|",
            "         Made by Atsukoro         ",
            "-------------------------------------"};

    for (const char *line : lines)
    {
        CenterText(line);
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

static bool BeginPEFieldTable(const char *id, int columns)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    if (!ImGui::BeginTable(id, columns, flags, ImVec2(0, 0)))
        return false;

    ImGui::TableSetupColumn("Field", ImGuiTableColumnFlags_WidthFixed, 180.0f);
    ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 160.0f);

    ImGui::TableHeadersRow();

    return true;
}

static void EndPEFieldTable()
{
    ImGui::EndTable();
}

void RenderGeneralTable(PEParser &parser)
{
    BeginPEFieldTable("General", 2);
    PrintTableRow2("Is 64 bit", (char *)(parser.is_64bit ? "true" : "false"));
    PrintTableRow2("File path", parser.path);
    EndPEFieldTable();
}

void RenderDOSHeaderTable(PEParser &parser)
{
    BeginPEFieldTable("DosHeaderTable", 2);
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
    EndPEFieldTable();
}

void RenderFileHeaderTable(PEParser &parser)
{
    BeginPEFieldTable("FileHeaderTable", 2);
    PrintTableRow2("Characteristics", Hex(parser.pe_nt_headers->FileHeader.Characteristics));
    PrintTableRow2("Machine", Hex(parser.pe_nt_headers->FileHeader.Machine));
    PrintTableRow2("Number of sections", Decimal(parser.pe_nt_headers->FileHeader.NumberOfSections));
    PrintTableRow2("Number of symbols", Decimal(parser.pe_nt_headers->FileHeader.NumberOfSymbols));
    PrintTableRow2("Pointer to symbol table", Hex(parser.pe_nt_headers->FileHeader.PointerToSymbolTable));
    PrintTableRow2("Time Date stamp", Decimal(parser.pe_nt_headers->FileHeader.TimeDateStamp));
    EndPEFieldTable();
}

void RenderOptionalHeaderTable(PEParser &parser)
{
    BeginPEFieldTable("OptionalHeaderTable", 2);
    PrintTableRow2("Entry point address", Hex(parser.pe_nt_headers->OptionalHeader.AddressOfEntryPoint));
    PrintTableRow2("Base of code", Hex(parser.pe_nt_headers->OptionalHeader.BaseOfCode));
    PrintTableRow2("Checksum", Hex(parser.pe_nt_headers->OptionalHeader.CheckSum));
    PrintTableRow2("DLL characteristics", Hex(parser.pe_nt_headers->OptionalHeader.DllCharacteristics));
    PrintTableRow2("File alignment", Hex(parser.pe_nt_headers->OptionalHeader.FileAlignment));
    PrintTableRow2("Image base", Hex(parser.pe_nt_headers->OptionalHeader.ImageBase));
    PrintTableRow2("Loader flags", Hex(parser.pe_nt_headers->OptionalHeader.LoaderFlags));
    PrintTableRow2("Magic", Hex(parser.pe_nt_headers->OptionalHeader.Magic));
    PrintTableRow2("Major image version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorImageVersion));
    PrintTableRow2("Major linker version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorLinkerVersion));
    PrintTableRow2("Major OS version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorOperatingSystemVersion));
    PrintTableRow2("Major subsystem version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorSubsystemVersion));
    PrintTableRow2("Miner image version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorImageVersion));
    PrintTableRow2("Minor linker version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorLinkerVersion));
    PrintTableRow2("Minor operating system version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorOperatingSystemVersion));
    PrintTableRow2("Minor subsystem version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorSubsystemVersion));
    PrintTableRow2("Number of RVA and sizes", Decimal(parser.pe_nt_headers->OptionalHeader.NumberOfRvaAndSizes));
    PrintTableRow2("Section alignment", Hex(parser.pe_nt_headers->OptionalHeader.SectionAlignment));
    PrintTableRow2("Size of code", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfCode));
    PrintTableRow2("Size of headers", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfHeaders));
    PrintTableRow2("Size of heap commit", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfHeapCommit));
    PrintTableRow2("Size of heap reserve", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfHeapReserve));
    PrintTableRow2("Size of image", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfImage));
    PrintTableRow2("Size of initialized data", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfInitializedData));
    PrintTableRow2("Size of stack commit", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfStackCommit));
    PrintTableRow2("Size of stack reserve", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfStackReserve));
    PrintTableRow2("Size of uninitialized data", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfUninitializedData));
    PrintTableRow2("Subsystem", Hex(parser.pe_nt_headers->OptionalHeader.Subsystem));
    PrintTableRow2("Win32 version value", Hex(parser.pe_nt_headers->OptionalHeader.Win32VersionValue));
    EndPEFieldTable();
}

void RenderSectionHeadersTable(PEParser &parser)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    ImGui::BeginTable("SectionHeadersTable", 8, flags, ImVec2(0, 0));

    ImGui::TableSetupColumn("Characteristics", ImGuiTableColumnFlags_WidthFixed, 180.0f);
    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 90.0f);
    ImGui::TableSetupColumn("Linenumbers count", ImGuiTableColumnFlags_WidthFixed, 140.0f);
    ImGui::TableSetupColumn("Relocations count", ImGuiTableColumnFlags_WidthFixed, 140.0f);
    ImGui::TableSetupColumn("Raw data pointer", ImGuiTableColumnFlags_WidthFixed, 160.0f);
    ImGui::TableSetupColumn("Relocations pointer", ImGuiTableColumnFlags_WidthFixed, 160.0f);
    ImGui::TableSetupColumn("Size of raw data", ImGuiTableColumnFlags_WidthFixed, 160.0f);
    ImGui::TableSetupColumn("Virtual address", ImGuiTableColumnFlags_WidthFixed, 160.0f);

    ImGui::TableHeadersRow();

    for (size_t i = 0; parser.pe_section_headers[i].Characteristics != 0; i++)
    {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        ImGui::Text(Hex(parser.pe_section_headers[i].Characteristics));
        ImGui::TableNextColumn();
        ImGui::Text((char *)(parser.pe_section_headers[i].Name));
        ImGui::TableNextColumn();
        ImGui::Text(Decimal(parser.pe_section_headers[i].NumberOfLinenumbers));
        ImGui::TableNextColumn();
        ImGui::Text(Decimal(parser.pe_section_headers[i].NumberOfRelocations));
        ImGui::TableNextColumn();
        ImGui::Text(Hex(parser.pe_section_headers[i].PointerToRawData));
        ImGui::TableNextColumn();
        ImGui::Text(Hex(parser.pe_section_headers[i].PointerToRelocations));
        ImGui::TableNextColumn();
        ImGui::Text(Decimal(parser.pe_section_headers[i].SizeOfRawData));
        ImGui::TableNextColumn();
        ImGui::Text(Hex(parser.pe_section_headers[i].VirtualAddress));
    }

    EndPEFieldTable();
}

void RenderThunkTable(ImportedLibrary &library)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_BordersInnerV |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp;

    std::string table_id = "ThunkTable_" + library.dll_name;

    if (!ImGui::BeginTable(table_id.c_str(), 5, flags))
        return;

    ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("Hint", ImGuiTableColumnFlags_WidthFixed, 120.0f);
    ImGui::TableSetupColumn("RVA", ImGuiTableColumnFlags_WidthFixed, 140.0f);

    ImGui::TableHeadersRow();

    for (size_t i = 0; i < library.functions.size(); i++)
    {
        const auto &thunk = library.functions[i];

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        if (thunk.is_ordinal)
            ImGui::TextDisabled("<ordinal import>");
        else
            ImGui::Text(thunk.name.c_str());

        ImGui::TableSetColumnIndex(1);

        if (thunk.is_ordinal)
            ImGui::TextDisabled("-");
        else
            ImGui::Text(Hex(thunk.hint));

        ImGui::TableSetColumnIndex(2);

        ImGui::Text(Hex(thunk.address));
    }

    ImGui::EndTable();
}

void RenderImportTable(PEParser &parser)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    ImGui::BeginTable("ImportTable", 2, flags, ImVec2(0, 0));

    ImGui::TableSetupColumn("DLL name", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("address", ImGuiTableColumnFlags_WidthFixed, 140.0f);

    ImGui::TableHeadersRow();

    for (int i = 0; i < parser.pe_imports.size(); i++)
    {
        auto &import = parser.pe_imports[i];

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        ImGuiTreeNodeFlags tree_flags =
            ImGuiTreeNodeFlags_SpanFullWidth |
            ImGuiTreeNodeFlags_DefaultOpen;

        bool open = ImGui::TreeNodeEx(
            (void *)(intptr_t)i,
            tree_flags,
            "%s",
            import.dll_name.c_str());

        if (open)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            ImGui::Indent(20.0f);

            RenderThunkTable(import);

            ImGui::Unindent(20.0f);

            ImGui::TreePop();
        }
    }

    ImGui::EndTable();
}

void RenderResourcesTable(PEParser &parser)
{
}

void RenderRelocationsTable(PEParser &parser)
{
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
                std::string file_name = OpenExeFileDialog();

                DWORD parsing_res = parser.from_disk((char*)(file_name.c_str()));

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
                selected_window = Window::General;
            }

            if (ImGui::MenuItem("Exit"))
            {
                PostQuitMessage(0);
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    if (!parser.parsed)
    {
        PrintIntro();
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