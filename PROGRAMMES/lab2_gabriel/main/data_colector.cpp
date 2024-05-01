#include "data_colector.h"

void replace_comma_with_period(string &line);
void make_collected_data_document(ofstream &new_notepad, string notepad_name, vector<vector<double>> data);

data_colector::data_colector(string notepad_name) {

    notepad.open(notepad_name);

    while (getline(notepad, line)){

        line_pos += 1;

        replace_comma_with_period(line);

        istringstream iss(line);
        double temp_data;

        if (iss >> temp_data){

            lines_to_colect_pos.push_back(line_pos);

            if (lines_to_colect_pos.size() == 1){

                while (!iss.fail()){

                    cols_numb += 1;
                    iss >> temp_data;
                }
            }
        }
    }

    data.resize(cols_numb);

    for (int i = 0; i < cols_numb; i++){
        
        data[i].resize(lines_to_colect_pos.size());
    }

    notepad.clear();
    notepad.seekg(0);

    for (int i = 0; i <= line_pos; i++){

        getline(notepad, line);

        replace_comma_with_period(line);

        if (lines_to_colect_pos.size() != 0 && colectable_line_numb < lines_to_colect_pos.size() 
        && i == lines_to_colect_pos[colectable_line_numb]){

            istringstream iss(line);
            double temp_data;

            for (int j = 0; j < cols_numb; j++){

                iss >> temp_data;
                data[j][colectable_line_numb] = temp_data;
            }

            colectable_line_numb += 1;
        }
    }

    make_collected_data_document(new_notepad, notepad_name, data);
}

vector<vector<double>> data_colector::get_data() const {

    return data;
}

vector<double> data_colector::get_a_certain_col(int numb) const {

    if (numb > 0 && numb <= data.size()){

        return data[numb - 1];
    }

    else {

        vector<double> empty;

        cout << "An empty vector<double> was returned after calling 'get_a_certain_col(integer)'. Please use an integer between 1 and " << 
        data.size() << " to return a valid column." << endl;

        return empty;
    }
}

double data_colector::get_a_certain_col_max(int numb) const {

    double max_value = 0;

    if (numb > 0 && numb <= data.size()){
        
        max_value = data[numb - 1][0];
        
        for (int i = 1; i < data[numb - 1].size(); i++){

            if (data[numb - 1][i] > max_value){
                
                max_value = data[numb - 1][i];
            }
        }
    }

    else {
        
        cout << "Zero was returned after calling 'get_a_certain_col_max(integer)'. Please use an integer between 1 and " << 
        data.size() << " to get the maximum value from a valid column." << endl;
    }

    return max_value;
}

double data_colector::get_a_certain_col_min(int numb) const {

    double min_value = 0;

    if (numb > 0 && numb <= data.size()){

        min_value = data[numb - 1][0];
        
        for (int i = 1; i < data[numb - 1].size(); i++){

            if (data[numb - 1][i] < min_value){
                
                min_value = data[numb - 1][i];
            }
        }
    }

    else {
        
        cout << "Zero was returned after calling 'get_a_certain_col_min(integer)'. Please use an integer between 1 and " << 
        data.size() << " to get the minimum value from a valid column." << endl;
    }

    return min_value;
}

void replace_comma_with_period(string &line) {

    vector<int> pos;
    int temp_pos = 0;
        
    while (line.find(",", temp_pos) != string::npos){
            
        temp_pos = line.find(",", temp_pos);
        pos.push_back(temp_pos);
        temp_pos += 1;
    }

    for (int i = 0; i < pos.size(); i++){
            
        line.replace(pos[i], 1, ".");
    }
}

void make_collected_data_document(ofstream &new_notepad, string notepad_name, vector<vector<double>> data) {

    string new_name = "new_";

    new_name.append(notepad_name);

    new_notepad.open(new_name);

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
}