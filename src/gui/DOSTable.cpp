#include "DOSTable.h"

void RenderDOSTableRow(char *key, char *value)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(key);
    ImGui::TableNextColumn();
    ImGui::Text(value);
}

void RenderDOSTable(PEParser &parser)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    if (!ImGui::BeginTable("DOSTable", 2, flags, ImVec2(0, 0)))
        return;

    ImGui::TableSetupColumn("Field", ImGuiTableColumnFlags_WidthFixed, 180.0f);
    ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 160.0f);

    ImGui::TableHeadersRow();

    RenderDOSTableRow("e_cblp", Hex(parser.pe_dos_header->e_cblp));
    RenderDOSTableRow("e_cp", Hex(parser.pe_dos_header->e_cp));
    RenderDOSTableRow("e_cparhdr", Hex(parser.pe_dos_header->e_cparhdr));
    RenderDOSTableRow("e_crlc", Hex(parser.pe_dos_header->e_crlc));
    RenderDOSTableRow("e_cs", Hex(parser.pe_dos_header->e_cs));
    RenderDOSTableRow("e_csum", Hex(parser.pe_dos_header->e_csum));
    RenderDOSTableRow("e_ip", Hex(parser.pe_dos_header->e_ip));
    RenderDOSTableRow("e_lfanew", Hex(parser.pe_dos_header->e_lfanew));
    RenderDOSTableRow("e_lfarlc", Hex(parser.pe_dos_header->e_lfarlc));
    RenderDOSTableRow("e_magic", Hex(parser.pe_dos_header->e_magic));
    RenderDOSTableRow("e_maxalloc", Hex(parser.pe_dos_header->e_maxalloc));
    RenderDOSTableRow("e_minalloc", Hex(parser.pe_dos_header->e_minalloc));
    RenderDOSTableRow("e_oemid", Hex(parser.pe_dos_header->e_oemid));
    RenderDOSTableRow("e_oeminfo", Hex(parser.pe_dos_header->e_oeminfo));
    RenderDOSTableRow("e_ovno", Hex(parser.pe_dos_header->e_ovno));
    RenderDOSTableRow("e_sp", Hex(parser.pe_dos_header->e_sp));
    RenderDOSTableRow("e_ss", Hex(parser.pe_dos_header->e_ss));

    ImGui::EndTable();
}