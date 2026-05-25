#include "Gui.h"

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

static void RenderSelectedTable(Window selected_window, PEParser &parser)
{
    switch (selected_window)
    {
    case Window::General:
        RenderGeneralTable(parser);
        break;

    case Window::DOSHeader:
        RenderDOSTable(parser);
        break;

    case Window::FileHeader:
        RenderFileTable(parser);
        break;

    case Window::OptionalHeader:
        RenderOptionalTable(parser);
        break;

    case Window::SectionHeaders:
        RenderSectionTable(parser);
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
    
    case Window::Strings:
        RenderStringsTable(parser);
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

    RenderTopBar(parser, pe_file_buffer);

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
    SidebarItem("Strings", Window::Strings, selected_window);

    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("TableView", ImVec2(0, 0), true);

    RenderSelectedTable(selected_window, parser);

    ImGui::EndChild();

    ImGui::SameLine();
    ImGui::BeginChild("HexView", ImVec2(200, 0), true);

    ImGui::EndChild();
}