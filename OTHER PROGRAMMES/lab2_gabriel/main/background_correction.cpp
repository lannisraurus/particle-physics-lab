#include "data_colector.cpp"

int main(){
    
    string name = "LAB8_CSPB0.ASC";
    data_colector gamma1(name);
    vector<double> x1 = gamma1.get_a_certain_col(1);
    vector<double> y1 = gamma1.get_a_certain_col(2);
    Int_t seconds1;
    Int_t points_numb = x1.size();
    string bg = "LAB7_FUNDO.ASC";
    data_colector gamma2(bg);
    vector<double> x2 = gamma2.get_a_certain_col(1);
    vector<double> y2 = gamma2.get_a_certain_col(2);
    Int_t seconds2;

    

    for (int i = 0; i < points_numb; i++){

        y1[i] = (y1[i] / seconds1 - y2[i] / seconds2) * seconds1;
    }

    ofstream bg_corr_txt;
    string bg_corr_name = "bg_corr_";

    bg_corr_name.append(name);

    bg_corr_txt.open(bg_corr_name);

    for (int i = 0; i < points_numb; i++){

        if (i != points_numb - 1){

            bg_corr_txt << x1[i] << " " << y1[i] << endl;
        }

        else {

            bg_corr_txt << x1[i] << " " << y1[i];
        }
    }

    bg_corr_txt.close();

    return 0;
}