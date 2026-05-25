#include "OptionalTable.h"

void RenderOptionalRow(char *key, char *value)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text(key);
    ImGui::TableNextColumn();
    ImGui::Text(value);
}

void RenderOptionalTable(PEParser &parser)
{
    ImGuiTableFlags flags =
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_SizingStretchProp |
        ImGuiTableFlags_ScrollY;

    if (!ImGui::BeginTable("GeneralTable", 2, flags, ImVec2(0, 0)))
        return;

    ImGui::TableSetupColumn("Field", ImGuiTableColumnFlags_WidthFixed, 180.0f);
    ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed, 160.0f);
    ImGui::TableHeadersRow();

    RenderOptionalRow("Entry point address", Hex(parser.pe_nt_headers->OptionalHeader.AddressOfEntryPoint));
    RenderOptionalRow("Base of code", Hex(parser.pe_nt_headers->OptionalHeader.BaseOfCode));
    RenderOptionalRow("Checksum", Hex(parser.pe_nt_headers->OptionalHeader.CheckSum));
    RenderOptionalRow("DLL characteristics", Hex(parser.pe_nt_headers->OptionalHeader.DllCharacteristics));
    RenderOptionalRow("File alignment", Hex(parser.pe_nt_headers->OptionalHeader.FileAlignment));
    RenderOptionalRow("Image base", Hex(parser.pe_nt_headers->OptionalHeader.ImageBase));
    RenderOptionalRow("Loader flags", Hex(parser.pe_nt_headers->OptionalHeader.LoaderFlags));
    RenderOptionalRow("Magic", Hex(parser.pe_nt_headers->OptionalHeader.Magic));
    RenderOptionalRow("Major image version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorImageVersion));
    RenderOptionalRow("Major linker version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorLinkerVersion));
    RenderOptionalRow("Major OS version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorOperatingSystemVersion));
    RenderOptionalRow("Major subsystem version", Decimal(parser.pe_nt_headers->OptionalHeader.MajorSubsystemVersion));
    RenderOptionalRow("Miner image version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorImageVersion));
    RenderOptionalRow("Minor linker version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorLinkerVersion));
    RenderOptionalRow("Minor operating system version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorOperatingSystemVersion));
    RenderOptionalRow("Minor subsystem version", Decimal(parser.pe_nt_headers->OptionalHeader.MinorSubsystemVersion));
    RenderOptionalRow("Number of RVA and sizes", Decimal(parser.pe_nt_headers->OptionalHeader.NumberOfRvaAndSizes));
    RenderOptionalRow("Section alignment", Hex(parser.pe_nt_headers->OptionalHeader.SectionAlignment));
    RenderOptionalRow("Size of code", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfCode));
    RenderOptionalRow("Size of headers", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfHeaders));
    RenderOptionalRow("Size of heap commit", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfHeapCommit));
    RenderOptionalRow("Size of heap reserve", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfHeapReserve));
    RenderOptionalRow("Size of image", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfImage));
    RenderOptionalRow("Size of initialized data", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfInitializedData));
    RenderOptionalRow("Size of stack commit", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfStackCommit));
    RenderOptionalRow("Size of stack reserve", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfStackReserve));
    RenderOptionalRow("Size of uninitialized data", Decimal(parser.pe_nt_headers->OptionalHeader.SizeOfUninitializedData));
    RenderOptionalRow("Subsystem", Hex(parser.pe_nt_headers->OptionalHeader.Subsystem));
    RenderOptionalRow("Win32 version value", Hex(parser.pe_nt_headers->OptionalHeader.Win32VersionValue));

    ImGui::EndTable();
}