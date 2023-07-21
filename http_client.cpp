#include <iostream>
#include <curl/curl.h>
using namespace std;
// Callback-функція для обробки отриманої відповіді
size_t WriteCallback(void*contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

int main() {
    CURL*curl;
    CURLcode res;
    string response;

    // Ініціалізація бібліотеки cURL
    curl = curl_easy_init();
    if (curl) {
        // Встановлення URL для запиту
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");

        // Налаштування callback-функції для отримання відповіді
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Виконання запиту
        res = curl_easy_perform(curl);

        // Перевірка на помилки
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Виведення відповіді сервера
            cout << "Response:\n" << response << endl;
        }

        // Звільнення ресурсів бібліотеки cURL
        curl_easy_cleanup(curl);
    } else {
        cerr << "Could not initialize cURL" << endl;
    }

    return 0;
}

