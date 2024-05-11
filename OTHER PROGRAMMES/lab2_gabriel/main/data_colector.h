#ifndef __DATA_COLECTOR__
#define __DATA_COLECTOR__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TPaveText.h"
#include "TSystem.h"

using namespace std;

class data_colector {

    public:

        data_colector(string notepad_name);

        vector<vector<double>> get_data() const;
        vector<double> get_a_certain_col(int numb) const;
        double get_a_certain_col_max(int numb) const;
        double get_a_certain_col_min(int numb) const;
        
    private:

        ifstream notepad;
        string line;
        int line_pos = -1;
        int cols_numb = 0;
        vector<int> lines_to_colect_pos;
        vector<vector<double>> data;
        int colectable_line_numb = 0;
        ofstream new_notepad;
};
#endif