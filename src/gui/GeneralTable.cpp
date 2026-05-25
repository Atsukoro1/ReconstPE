#include "GeneralTable.h"

void RenderGeneralRow(char *key, char *value)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(key);
    ImGui::TableNextColumn();
    ImGui::Text(value);
}

void RenderGeneralTable(PEParser& parser)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    if(!ImGui::BeginTable("GeneralTable", 2, flags, ImVec2(0, 0))) return;

    ImGui::TableSetupColumn("Field", ImGuiTableColumnFlags_WidthFixed, 180.0f);
    ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 160.0f);
    ImGui::TableHeadersRow();

    RenderGeneralRow("Is 64 bit", (char*)(parser.is_64bit ? "true" : "false"));
    RenderGeneralRow("File path", parser.path);
    RenderGeneralRow("MD5 hash", (char*)parser.md5hash.c_str());

    ImGui::EndTable();
}