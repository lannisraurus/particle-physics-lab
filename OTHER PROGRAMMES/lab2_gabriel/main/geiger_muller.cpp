#include "data_colector.cpp"

int main(){
    
    data_colector gm("plateau.txt");
    vector<double> x = gm.get_a_certain_col(1);
    //vector<double> ex = gm.get_a_certain_col(2);
    vector<double> y = gm.get_a_certain_col(2);
    //vector<double> ey = gm.get_a_certain_col(4);
    Int_t points_numb = x.size();
    double* x_arr = &x[0];
    //double* ex_arr = &ex[0];
    double* y_arr = &y[0];
    //double* ey_arr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraph* g = new TGraphErrors(points_numb, x_arr, y_arr);
    TF1* f = new TF1("f", "[a] * x + [b]");

    //f->SetParameter("a");
    //f->SetParameter("b");
    
    g->Draw();
    g->Fit("f");
    C->Update();
    C->SaveAs("gm_fit.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}