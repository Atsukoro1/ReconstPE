#include "StringsTable.h"

void RenderStringsTable(PEParser& parser)
{
    if (ImGui::BeginTable(
        "StringsTable",
        1,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_ScrollY,
        ImVec2(0, 0)))
    {
        ImGui::TableSetupColumn("String");
        ImGui::TableHeadersRow();

        ImGuiListClipper clipper;
        clipper.Begin(static_cast<int>(parser.strings.size()));

        while (clipper.Step())
        {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();

                ImGui::TextUnformatted(parser.strings[row].c_str());
            }
        }

        ImGui::EndTable();
    }
}