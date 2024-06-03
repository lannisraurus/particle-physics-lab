#include "data_colector.cpp"

double get_seconds(string file_name);

int main(){
    
    string name = "LAB8_M2.ASC"; // mudar o nome do ficheiro a retirar o fundo
    data_colector gamma1(name);
    vector<double> x1 = gamma1.get_a_certain_col(1);
    vector<double> y1 = gamma1.get_a_certain_col(2);
    double seconds1;
    Int_t points_numb = x1.size();
    string bg = "LAB8_FUNDO2.ASC"; // mudar o nome do ficheiro de fundo
    data_colector gamma2(bg);
    vector<double> y2 = gamma2.get_a_certain_col(2);
    double seconds2;

    seconds1 = get_seconds(name);
    seconds2 = get_seconds(bg);

    cout << "Seconds main file = " << seconds1 << " | Seconds background file = " << seconds2 << endl;

    for (int i = 0; i < points_numb; i++){

        y1[i] = (y1[i] / seconds1 - y2[i] / seconds2) * seconds1;

        if (y1[i] < 0){

            y1[i] = 0;
        }
    }
    
    const char* home_dir = getenv("HOME");
    ofstream bg_corr_txt;
    string bg_corr_name = string(home_dir) + "/github_lfea1/GAMMAS CORR LAB DATA/bg_corr_";

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

    getline(time_finder, first_line);

    istringstream iss(first_line);
    string skip;
    double sec;

    for (int i = 1; i <= 10; i++){

        iss >> skip;
    }

    iss >> sec;

    return sec;
}