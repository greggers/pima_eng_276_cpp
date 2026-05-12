#include "gpt_prompt.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Constructor to initialize API key from environment variable
GptPrompt::GptPrompt()
{
    char* key = nullptr;
    size_t len = 0;

    errno_t err = _dupenv_s(
        &key,
        &len,
        "OPENAI_API_KEY");

    if (err || key == nullptr)
    {
        throw std::runtime_error(
            "OPENAI_API_KEY environment variable not set.");
    }

    apiKey = key;

    free(key);
}

// Callback function for libcurl to write response data
size_t GptPrompt::WriteCallback(
    void* contents,
    size_t size,
    size_t nmemb,
    std::string* output)
{
    size_t totalSize = size * nmemb;

    output->append((char*)contents, totalSize);

    return totalSize;
}

// Function to send prompt to GPT API and receive response
std::string GptPrompt::ask(const std::string& prompt)
{
    CURL* curl = curl_easy_init();

    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL.");
    }

    std::string responseData;

    json requestBody =
    {
        { "model", "gpt-4.1-mini" },
        { "input", prompt }
    };

    std::string requestString = requestBody.dump();

    struct curl_slist* headers = nullptr;

    std::string authHeader =
        "Authorization: Bearer " + apiKey;

    headers = curl_slist_append(
        headers,
        "Content-Type: application/json");

    headers = curl_slist_append(
        headers,
        authHeader.c_str());

    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        "https://api.openai.com/v1/responses");

    curl_easy_setopt(
        curl,
        CURLOPT_HTTPHEADER,
        headers);

    curl_easy_setopt(
        curl,
        CURLOPT_POSTFIELDS,
        requestString.c_str());

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        WriteCallback);

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        &responseData);

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        throw std::runtime_error(
            curl_easy_strerror(result));
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    // Parse JSON response
    json responseJson = json::parse(responseData);

    try
    {
        return responseJson["output"][0]
            ["content"][0]
            ["text"];
    }
    catch (...)
    {
        return "Unable to parse GPT response.\n\nRaw Response:\n" +
            responseData;
    }
}