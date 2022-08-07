#include <iostream>
#include <regex>
#include <iomanip>

std::string loadString() {
    std::string str{};
    for (std::string line; std::getline(std::cin, line);) {
        str += line;
    }
    return str;
}

void findAndPrintUrls(std::string s) {
    const std::regex url_re(R"!!(<\s*a\s+[^>]*href\s*=\s*"(http[s]?://[^"]*)">\s*([^<]*)\s*</a>)!!", std::regex::icase);

    auto match_begin = std::sregex_iterator(s.begin(), s.end(), url_re);
    auto match_end = std::sregex_iterator();
    std::cout << "Links:" << std::endl;
    for (auto i = match_begin; i != match_end; i++) {
        const std::smatch &match = *i;
        std::cout << std::setw(32) << std::left << match[2] << " : " << match[1] << std::endl;
//        std::cout << match[2] << " : " << match[1] << std::endl << std::endl;
    }
}

void findAndPrintEmails(std::string s) {
    const std::regex email_re(R"(\w[\w\._-]*@[\w-]+(?:\.[\w-]+)+)", std::regex::icase);

    auto match_begin = std::sregex_token_iterator(s.begin(), s.end(), email_re, 0);
    auto match_end = std::sregex_token_iterator();
    std::cout << "Emails:" << std::endl;
    for (auto i = match_begin; i != match_end; i++) {
        std::cout << " > " << *i << std::endl;
    }
}

int main() {
    std::string html = loadString();
//    std::cout << html << std::endl;
    findAndPrintUrls(html);
    findAndPrintEmails(html);

    return 0;
}