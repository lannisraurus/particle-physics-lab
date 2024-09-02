#include "data_colector.cpp"

int main(){

    /*double x[5] = {1, 2, 3, 4, 5};
    double ex[5] = {0.1, 0.1, 0.1, 0.1, 0.1};
    double y[5] = {1, 2, 3, 4, 5};
    double ey[5] = {0.1, 0.1, 0.1, 0.1, 0.1};

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(5, x, y, ex, ey);
    TF1* f = new TF1("f", "[0] * (1 - (x * 0.01) / TMath::Sqrt(pow(x * 0.01, 2) + pow([1], 2)))");
    TPaveText* pt = new TPaveText(3, 550, 4, 750, "user");

    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");

    C->Update();
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;*/

    /*vector<int> x = {1, 2, 3, 4, 5};
    vector<int> y = {10, 20, 30, 40, 50};
    vector<int> pos_to_erase = {1, 3};
    int counter = 0; 

    cout << pos_to_erase.size() << endl;

    for (int pos : pos_to_erase){

        x.erase(x.begin() + pos - counter);
        y.erase(y.begin() + pos - counter);

        counter += 1; 
    }

    for (int i = 0; i < x.size(); i++){

        cout << x[i] <<  " | " << y[i] << endl;
    }*/

    double x[4] = {216, 217, 218, 219};
    double y[4] = {66, 499, 231, 12};
    int min = x[0];
    int max = x[sizeof(x) / sizeof(x[0]) - 1];
    double counter = 0;

    for (double i : y){

        counter = counter + i;
    }

    cout << "N   " << counter << endl;

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraph* g = new TGraph(sizeof(x) / sizeof(x[0]), x, y);
    TF1* f = new TF1("f", "gaus", min, max);

    //f->SetParameter("mean", 17);
    //f->SetParameter("std_dev", 0.9);

    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Channels");
    g->GetXaxis()->SetLimits(min, max);
    g->GetXaxis()->SetNdivisions(-4);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Absolute frequency");
    g->GetYaxis()->SetRangeUser(0, 600);
    g->GetYaxis()->SetNdivisions(-515);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f", "R");

    C->Update();
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}