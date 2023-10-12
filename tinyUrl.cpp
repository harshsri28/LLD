#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

class URLShortener
{
private:
    std::unordered_map<std::string, std::string> urlToShort;
    std::unordered_map<std::string, std::string> shortToURL;
    const std::string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int shortURLLength = 6;

public:
    std::string generateShortURL(const std::string &url)
    {
        std::string shortURL = generateRandomShortURL();
        while (shortToURL.find(shortURL) != shortToURL.end())
        {
            shortURL = generateRandomShortURL();
        }

        urlToShort[url] = shortURL;
        shortToURL[shortURL] = url;
        return shortURL;
    }

    std::string getOriginalURL(const std::string &shortURL)
    {
        if (shortToURL.find(shortURL) != shortToURL.end())
        {
            return shortToURL[shortURL];
        }
        return "Short URL not found.";
    }

private:
    std::string generateRandomShortURL()
    {
        std::string shortURL;
        int len = chars.size();
        srand(time(0));
        for (int i = 0; i < shortURLLength; ++i)
        {
            shortURL.push_back(chars[rand() % len]);
        }
        return shortURL;
    }
};

int main()
{
    URLShortener urlShortener;

    std::string longURL1 = "https://www.example.com/page1";
    std::string shortURL1 = urlShortener.generateShortURL(longURL1);
    std::cout << "Generated Short URL: " << shortURL1 << "\n";

    std::string longURL2 = "https://www.example.com/page2";
    std::string shortURL2 = urlShortener.generateShortURL(longURL2);
    std::cout << "Generated Short URL: " << shortURL2 << "\n";

    std::cout << "Original URL for " << shortURL1 << ": " << urlShortener.getOriginalURL(shortURL1) << "\n";
    std::cout << "Original URL for " << shortURL2 << ": " << urlShortener.getOriginalURL(shortURL2) << "\n";

    return 0;
}
