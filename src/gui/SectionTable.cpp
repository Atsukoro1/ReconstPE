#include "SectionTable.h"

void RenderSectionTable(PEParser &parser)
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

    ImGui::EndTable();
}