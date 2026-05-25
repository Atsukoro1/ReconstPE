#include "FileTable.h"

void RenderFileRow(char *key, char *value)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(key);
    ImGui::TableNextColumn();
    ImGui::Text(value);
}

void RenderFileTable(PEParser& parser)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    if(!ImGui::BeginTable("FileTable", 2, flags, ImVec2(0, 0))) return;

    ImGui::TableSetupColumn("Field", ImGuiTableColumnFlags_WidthFixed, 180.0f);
    ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 160.0f);
    ImGui::TableHeadersRow();

    RenderFileRow("Characteristics", Hex(parser.pe_nt_headers->FileHeader.Characteristics));
    RenderFileRow("Machine", Hex(parser.pe_nt_headers->FileHeader.Machine));
    RenderFileRow("Number of sections", Decimal(parser.pe_nt_headers->FileHeader.NumberOfSections));
    RenderFileRow("Number of symbols", Decimal(parser.pe_nt_headers->FileHeader.NumberOfSymbols));
    RenderFileRow("Pointer to symbol table", Hex(parser.pe_nt_headers->FileHeader.PointerToSymbolTable));
    RenderFileRow("Time Date stamp", Decimal(parser.pe_nt_headers->FileHeader.TimeDateStamp));

    ImGui::EndTable();
}

