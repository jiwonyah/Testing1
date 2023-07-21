//The objective of the code is for the BLOG POST 3 of MGNT102
//Analysis would be launched after getting text file name from the user

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

//function declaration
void readFile(std::string fileName, std::vector<std::string>& arr1, std::vector<std::string>& arr2, std::vector<std::string>& arr3);

std::vector<std::string> setUnion(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
std::vector<std::string> setIntersection(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
std::vector<std::string> setDifference(const std::vector<std::string>& setA, const std::vector<std::string>& setB);
std::vector<std::string> complement(const std::vector<std::string>& setA, const std::vector<std::string>& setB);

int main(){
    std::string fileName;
    std::vector<std::string> adj_list;
    std::vector<std::string> self_o;        //adjectives known to self
    std::vector<std::string> others_o;      //adjectives known to others

    std::cout << "This program is for getting an analysis of Johari Window." << std::endl;
    readFile(fileName, adj_list, self_o, others_o);
    std::cout << "\n-----------------------------Johari Window-------------------------------" << std::endl;
    std::cout << std::endl;

    //Open
    //the intersection of 'self_o' and 'others_o'
    std::vector<std::string> both_o = setIntersection(self_o, others_o);        //adjectives known to both

    std::cout << "\nOpen (" << both_o.size() << "): ";
    for(const auto& element : both_o){
        std::cout << element << " ";
    }
    std::cout << std::endl;


    //Hidden
    //set difference from 'self_o' to 'both_o'
    std::vector<std::string> only_self_o = setDifference(self_o, both_o);

    std::cout << "\nHidden (" << only_self_o.size() << "): ";
    for(const auto& element : only_self_o){
        std::cout << element << " ";
    }
    std::cout << std::endl;


    //Blind
    //set difference from 'others_o' to 'both_o'
    std::vector<std::string> only_others_o = setDifference(others_o, both_o);

    std::cout << "\nBlind (" << only_others_o.size() << "): ";
    for(const auto& element : only_others_o){
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    //Unknown
    //complement of union of 'self_o' and 'both_o'
    //~(self_o || both_o)
    std::vector<std::string> self_or_others = setUnion(self_o, others_o);
    std::vector<std::string> both_x = complement(adj_list, self_or_others);

    std::cout << "\nUnknown (" << both_x.size() << "): ";
    for(const auto& element : both_x){
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}

//function definition
void readFile(std::string fileName, std::vector<std::string>& adj_list, std::vector<std::string>& self_o, std::vector<std::string>& others_o){
    std::string line;
    std::string section;

    //user input
    std::cout << "Please enter the file name: ";
    std::cin >> fileName;
    std::cout << std::endl;

    std::ifstream file(fileName);               //read the file

    //when the file is opened
    if (file.is_open()){
        while (std::getline(file, line)){

            if(line.empty()){
                continue;       //skip the empty line
            }

            //distinguish the each section
            if(line == "<adjectives>"){
                section = "adjectives";         //the variable section is stored as "adjectives"   
                continue;
            }
            else if(line == "<known to self>"){
                section = "known to self";
                continue;
            }
            else if(line == "<known to others>"){
                section = "known to others";
                continue;
            }

            //using push_back()    
            //allocate the each line as an element of a vector
            if (section == "adjectives"){
                adj_list.push_back(line);
            }
            
            else if (section == "known to self"){
                self_o.push_back(line);
            }

            else if (section == "known to others"){
                others_o.push_back(line);
            }
        }
        file.close();
    }

    //when the file cannot be opened
    else{
        std::cerr << "Cannot open the file" << std::endl;
    }
}

//union
std::vector<std::string> setUnion (const std::vector<std::string>& setA, const std::vector<std::string>& setB){
    std::set<std::string> uniqueSetA(setA.begin(), setA.end());     //avoid redundancy
    std::set<std::string> uniqueSetB(setB.begin(), setB.end());
    std::vector<std::string> result;

    std::set_union(uniqueSetA.begin(), uniqueSetA.end(), uniqueSetB.begin(), uniqueSetB.end(), std::back_inserter(result));
    
    return result;
}

//intersection
std::vector<std::string> setIntersection(const std::vector<std::string>& setA, const std::vector<std::string>& setB){
    std::set<std::string> uniqueSetA(setA.begin(), setA.end());
    std::set<std::string> uniqueSetB(setB.begin(), setB.end());
    std::vector<std::string> result;

    std::set_intersection(uniqueSetA.begin(), uniqueSetA.end(), uniqueSetB.begin(), uniqueSetB.end(), std::back_inserter(result));
    

    return result;
} 

//set difference --> A - B
std::vector<std::string> setDifference(const std::vector<std::string>& setA, const std::vector<std::string>& setB){
    std::set<std::string> uniqueSetA(setA.begin(), setA.end());
    std::set<std::string> uniqueSetB(setB.begin(), setB.end());
    std::vector<std::string> result;

    std::set_difference(uniqueSetA.begin(), uniqueSetA.end(), uniqueSetB.begin(), uniqueSetB.end(), std::back_inserter(result));

    return result;
}

//complementary set
//set A is a subset of set B
std::vector<std::string> complement(const std::vector<std::string>& setA, const std::vector<std::string>& setB){
    std::set<std::string> uniqueSetA(setA.begin(), setA.end());
    std::vector<std::string> result;

    for(const auto& element : uniqueSetA){
        if(std::find(setB.begin(), setB.end(), element) == setB.end()){
                result.push_back(element);
        }
    }
    return result;
}
