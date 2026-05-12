#ifndef GPT_PROMPT_HPP
#define GPT_PROMPT_HPP

#include <string>

// Class to handle GPT prompts and responses
class GptPrompt
{
public:
    GptPrompt();

    std::string ask(const std::string& prompt);

private:
    std::string apiKey;

    static size_t WriteCallback(
        void* contents,
        size_t size,
        size_t nmemb,
        std::string* output);
};

#endif