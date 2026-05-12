#include <iostream>
#include <string>

#include "gpt_prompt.hpp"

int main()
{
	// Get user input
    std::string prompt;

    std::cout << "Enter prompt: ";
    std::getline(std::cin, prompt);

    try
    {
		// Create GPT prompt handler
        GptPrompt gpt;

        std::string response = gpt.ask(prompt);

        std::cout << "\n===== GPT RESPONSE =====\n";
        std::cout << response << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}