#include "data_colector.cpp"

int main(){
    
    data_colector gamma1("LAB8_CSPB0.ASC");
    vector<double> x1 = gamma1.get_a_certain_col(1);
    vector<double> y1 = gamma1.get_a_certain_col(2);
    Int_t seconds1;
    data_colector gamma2("LAB7_FUNDO.ASC");
    vector<double> x2 = gamma2.get_a_certain_col(1);
    vector<double> y2 = gamma2.get_a_certain_col(2);
    Int_t seconds2;
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        y1[i] = (y1[i] / seconds1 - y2[i] / seconds2) * seconds1;
    }

    return 0;
}