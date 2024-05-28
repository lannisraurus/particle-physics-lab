#include "data_colector.cpp"

int main(){
    
    data_colector gamma1("LAB8_CSPB0.ASC");
    vector<double> x = gamma1.get_a_certain_col(1);
    vector<double> y = gamma1.get_a_certain_col(2);
    data_colector gamma2("LAB7_FUNDO.ASC");
    vector<double> x = gamma2.get_a_certain_col(1);
    vector<double> y = gamma2.get_a_certain_col(2);
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){


    }

    return 0;
}