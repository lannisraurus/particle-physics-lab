#include "data_colector.cpp"

int main(){
    
    data_colector beta("cal_gamma.txt");
    vector<double> x = beta.get_a_certain_col(1);
    vector<double> ex = beta.get_a_certain_col(2);
    vector<double> y = beta.get_a_certain_col(3);
    vector<double> ey;
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        ey.push_back(0);
    }
    
    return 0;
}