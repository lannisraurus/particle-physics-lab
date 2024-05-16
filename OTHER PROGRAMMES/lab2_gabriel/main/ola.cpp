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

    double x[5] = {15, 16, 17, 18, 19};
    double y[5] = {13, 437, 1424, 542, 17};

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraph* g = new TGraph(5, x, y);
    TF1* f = new TF1("f", "1 / ([std_dev] * TMath::Sqrt(2 * TMath::Pi())) * TMath::Exp(-0.5 * pow((x - [mean]) / [std_dev], 2))");

    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("");
    g->GetXaxis()->SetLimits(15, 19);
    g->GetXaxis()->SetNdivisions(-518);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("");
    g->GetYaxis()->SetRangeUser(0, 1500);
    g->GetYaxis()->SetNdivisions(-510);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");

    C->Update();
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete A;

    return 0;
}