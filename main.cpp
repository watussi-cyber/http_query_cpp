#include <windows.h>
#include <wininet.h>
#include <iostream>

#pragma comment(lib, "wininet.lib")

int main() {
    // Initialiser la session WinInet
    HINTERNET hInternet = InternetOpen(L"MyAgent", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        std::cout << "InternetOpen failed\n";
        return 1;
    }

    // Connexion au serveur
    HINTERNET hConnect = InternetConnect(hInternet, L"eobshlal3lh5vri.m.pipedream.net", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        std::cout << "InternetConnect failed\n";
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Préparer la requête HTTP GET
    HINTERNET hRequest = HttpOpenRequest(hConnect, L"GET", L"/", NULL, NULL, NULL, 0, 0);
    if (!hRequest) {
        std::cout << "HttpOpenRequest failed\n";
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Envoyer la requête
    BOOL sent = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
    if (!sent) {
        std::cout << "HttpSendRequest failed\n";
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Lire et afficher la réponse
    char buffer[1024];
    DWORD bytesRead = 0;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead) {
        buffer[bytesRead] = '\0';
        std::cout << buffer;
    }

    // Fermer les handles
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return 0;
}
