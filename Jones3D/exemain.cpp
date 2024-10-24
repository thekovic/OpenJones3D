#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <optional>
#include <ranges>
#include <string_view>
#include <windows.h>

#include "sha256.h"

namespace fs = std::filesystem;
constexpr std::string_view Indy3D_v1_0_sha256 = "3fbaf8cd401b4af80967cbe42e3420fb803288b336ebbe72a9a01b6dfd661a53";

bool iequals(const std::string_view& lhs, const std::string_view& rhs)
{
    namespace rvs = std::ranges::views;
    auto to_lower = rvs::transform([](unsigned char c) { return std::tolower(c); });
    return std::ranges::equal(lhs | to_lower, rhs | to_lower);
}

std::optional<std::string> CalcFileSha256(const fs::path& filepath)
{
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if ( !file.is_open() ) {
        return std::nullopt;
    }

    // Read the file into memory
    std::string data{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    file.close();

    SHA256 hasher;
    hasher.update(data.data(), data.size());
    return hasher.hash();
}

bool IsValidFile(const fs::path& filepath, const std::string_view fileSha256)
{
    auto hash = CalcFileSha256(filepath);
    if ( !hash ) {
        return false;
    }
    return iequals(hash.value(), fileSha256);
}

int main(int argc, char** argv)
{
    // Execute Indy3D.exe in suspended mode.
    fs::path exePath = "Indy3D.exe";
    if ( argc > 1 ) {
        exePath = argv[1];
    }

    if ( !fs::exists(exePath) )
    {
        std::fprintf(stderr, "Can't find '%ls' to inject DLL!\n", exePath.c_str());
        MessageBox(NULL, (L"File '" + exePath.wstring() + L"' doesn't exist!").c_str(), L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    if ( !IsValidFile(exePath, Indy3D_v1_0_sha256) )
    {
        std::fprintf(stderr, "Invalid Indy3D exe to inject DLL: %ls.\n", exePath.c_str());
        MessageBox(NULL, L"Only Indy3D.exe version 1.0 is supported!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    fs::path dllPath = "Jones3D.dll";
    if ( !fs::exists(dllPath) )
    {
        std::fprintf(stderr, "Can't find %ls.\n", dllPath.c_str());
        MessageBox(NULL, L"Can't find Jones3D.dll!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    const auto dllPathStr = dllPath.u8string();
    const size_t dllPathSize = dllPathStr.size() * sizeof(decltype(dllPathStr)::value_type);

    STARTUPINFO si = { 0 };
    si.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi = { 0 };
    if ( !CreateProcess(exePath.native().c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi) )
    {
        std::fprintf(stderr, "CreateProcess(\"%ls\") failed; error code = 0x%08X\n", exePath.c_str(), GetLastError());
        const wchar_t* pError = L"Failed to start Indy3D.exe!";
        if ( GetLastError() == ERROR_ELEVATION_REQUIRED ) {
            pError = L"Failed to start Indy3D.exe!\n\nIt looks like administrator permissions are required to run this program?! 🤔";
        }
        MessageBox(NULL, pError, L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    // Allocate a page in the process's address space for the DLL path
    LPSTR aPath = (LPSTR)VirtualAllocEx(pi.hProcess, NULL, dllPathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if ( aPath == NULL )
    {
        std::fprintf(stderr, "VirtualAllocEx failed; error code = 0x%08X\n", GetLastError());
        MessageBox(NULL, L"Failed to inject Jones3D.dll!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    // Write the Jones3D.dll path to the allocated memory
    if ( WriteProcessMemory(pi.hProcess, aPath, dllPathStr.c_str(), dllPathSize, NULL) == 0 )
    {
        std::fprintf(stderr, "WriteProcessMemory failed; error code = 0x%08X\n", GetLastError());
        MessageBox(NULL, L"Failed to inject Jones3D.dll!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    // Inject Jones3D.dll into the address space of the process
    HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, aPath, 0, NULL);
    if ( hThread == NULL )
    {
        std::fprintf(stderr, "CreateRemoteThread failed; error code = 0x%08X\n", GetLastError());
        MessageBox(NULL, L"Failed to inject Jones3D.dll!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    // Wait for DllMain to return
    if ( WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED )
    {
        std::fprintf(stderr, "WaitForSingleObject failed; error code = 0x%08X\n", GetLastError());
        MessageBox(NULL, L"Failed to inject Jones3D.dll!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    CloseHandle(hThread);

    // Resume Indy3D.exe
    if ( ResumeThread(pi.hThread) == -1 )
    {
        std::fprintf(stderr, "ResumeThread failed; error code = 0x%08X\n", GetLastError());
        MessageBox(NULL, L"Failed to inject Jones3D.dll!", L"Jones3D Error", MB_ICONERROR | MB_OK);
        return 1;
    }

    VirtualFreeEx(pi.hProcess, aPath, 0, MEM_RELEASE);
    CloseHandle(pi.hProcess);
    std::printf("%ls successfully injected!\n", dllPath.c_str());
    return 0;
}