// Lors de la compilation, penser à faire appliquer l'option -lcurl
// Sur windows, il faut 1/ Installer MSYS2 2/ Installer : pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-curl 3/ Faire la compilation depuis la console MSYS2

#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        // Définition de l'URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://cyber.moingt.com/titi");

        // Callback pour stocker la réponse
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Définition d’un User-Agent personnalisé
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "MyUserAgent");

        // Exécute la requête
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Erreur curl_easy_perform(): "
                      << curl_easy_strerror(res) << std::endl;
        } else {
            // Récupération du code HTTP
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            std::cout << "HTTP code: " << response_code << std::endl;
            std::cout << "Réponse :" << std::endl;
            std::cout << readBuffer << std::endl;
        }

        // Nettoyage
        curl_easy_cleanup(curl);
    }
    return 0;
}
