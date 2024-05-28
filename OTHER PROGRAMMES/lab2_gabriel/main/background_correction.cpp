#include "data_colector.cpp"

int main(){
    
    string name = "LAB8_CSPB0.ASC";
    data_colector gamma1(name);
    vector<double> x1 = gamma1.get_a_certain_col(1);
    vector<double> y1 = gamma1.get_a_certain_col(2);
    Int_t seconds1;
    string bg = "LAB7_FUNDO.ASC";
    data_colector gamma2(bg);
    vector<double> x2 = gamma2.get_a_certain_col(1);
    vector<double> y2 = gamma2.get_a_certain_col(2);
    Int_t seconds2;
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        y1[i] = (y1[i] / seconds1 - y2[i] / seconds2) * seconds1;
    }
    
    string bg_corr_name = "bg_corr_";

    bg_corr_name.append(name);

    new_notepad.open(bg_corr_name);

    for (int i = 0; i < data[0].size(); i++){
        
        for (int j = 0; j < data.size(); j++){
            
            if (j == data.size() - 1){
                
                new_notepad << data[j][i];
            }
            
            else {

                new_notepad << data[j][i] << " ";
            }
        }
        
        if (i < data[0].size() - 1){

            new_notepad << endl;
        }
    }

    new_notepad.close();

    return 0;
}