#include "ImportTable.h"

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

        ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_SpanFullWidth;

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