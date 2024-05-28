#include "data_colector.cpp"

double get_seconds(string file_name);

int main(){
    
    string name = "LAB8_CSPB0.ASC"; // varia
    data_colector gamma1(name);
    vector<double> x1 = gamma1.get_a_certain_col(1);
    vector<double> y1 = gamma1.get_a_certain_col(2);
    double seconds1;
    Int_t points_numb = x1.size();
    string bg = "LAB7_FUNDO.ASC"; // varia
    data_colector gamma2(bg);
    vector<double> x2 = gamma2.get_a_certain_col(1);
    vector<double> y2 = gamma2.get_a_certain_col(2);
    double seconds2;

    seconds1 = get_seconds(name);
    seconds2 = get_seconds(bg);

    cout << "seconds1 = " << seconds1 << " | " << "seconds2 = " << seconds2 << endl;

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

double get_seconds(string file_name) {

    ifstream time_finder;
    time_finder.open(file_name);
    string first_line;
    istringstream iss(first_line);
    double sec;

    geltine(time_finder, first_line);

    while (iss.eof() == 0){

        iss >> sec;
    }

    return sec;
}