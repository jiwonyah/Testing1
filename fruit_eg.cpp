#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("fruit_list.txt");
    std::string line;
    std::vector<std::string> fruit_list;
    std::vector<std::string> jiwon_favorites;
    std::vector<std::string> chaewon_favorites;

    std::string section;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue; // 빈 줄은 건너뜁니다.
            }

            if (line == "<Chaewon's favorite>") {
                section = "Chaewon";
                continue;
            } 
            else if (line == "<Jiwon's favorite>") {
                section = "Jiwon";
                continue;
            } 
            else if (line == "<fruit list>") {
                section = "Fruit";
                continue;
            }

            if (section == "Chaewon") {
                chaewon_favorites.push_back(line);
            } else if (section == "Jiwon") {
                jiwon_favorites.push_back(line);
            } else if (section == "Fruit") {
                fruit_list.push_back(line);
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }

    // 각각의 좋아하는 과일 목록과 과일 목록을 출력해보겠습니다.
    std::cout << "Jiwon's favorites: ";
    for (const auto& fruit : jiwon_favorites) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    std::cout << "Chaewon's favorites: ";
    for (const auto& fruit : chaewon_favorites) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    // fruit_list 배열 출력
    std::cout << "Fruit list: ";
    for (const auto& fruit : fruit_list) {
        std::cout << fruit << " ";
    }
    std::cout << std::endl;

    return 0;
}