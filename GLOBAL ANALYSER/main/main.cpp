// Includes
#include "includes.h"

std::function<void(std::ifstream*)> doNothing = [](std::ifstream *input){std::cout << "This Function is useless.\n";};

// Main Function
int main(){

    // Runtime Variables
    std::ifstream input;
    std::ofstream output;

    // Static Variables
    const std::string dataPath = "../RAW LAB DATA/";
    const std::string savePath = "../ANALYSED DATA/";
    std::map<int,std::string> analysisFunctionDescriptions = {
        {0 , "Do nothing. For debugging."}
    };
    std::map<int,std::function<void(std::ifstream*)>> analysisFunctions = {
        {0 , doNothing}  
    };

    // Input Variables
    std::string fileName = "";
    std::string runAgain = "";
    int analysisFunctionId = 0;

    // Program Runtime
    while(true){

        // Enter File Name
        std::cout << "> Enter file name (in [RAW DATA] folder): ";
        std::cin >> fileName;

        // Open File
        fileName = dataPath+fileName;
        std::cout << "> Opening File located in " << fileName << "\n";
        input.open(fileName);

        if(!input.is_open()){

            std::cout << "> ERROR: Could not open file! Exiting.\n";
            break;
        
        }else{

            // Print Analysis Functions ID's and Descriptions
            std::cout << "\n";
            for(auto& i : analysisFunctionDescriptions){
                std::cout << "(" << i.first << ")" << " " << i.second << "\n";
            }
            std::cout << "\n";

            // Enter Function ID
            std::cout << "> Enter desired data analysis function ID: ";
            std::cin >> analysisFunctionId;
            std::cout << "\n";

            // Pass all the data onto the function
            analysisFunctions[analysisFunctionId](&input);
            std::cout << "\n";

        }

        // Exit Programme OR re-run
        std::cout << "> Finished all operations successfully. Run again? (y/n): ";
        std::cin >> runAgain;
        if(runAgain!="y"){ break; }else{ std::cout << "\n"; }
    }

    std::cout << "> Exiting Programme.\n";
}
