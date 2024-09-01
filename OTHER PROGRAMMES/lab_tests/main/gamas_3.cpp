// Includes
#include "includes.h"

// Main Function
int main(){

    double x, y;
    std::vector<double> X, Y, eX, eY;
    std::ifstream in;

    in.open("input/chumbo.txt");
    while(!in.eof()){

        in >> x >> y;


        X.push_back(x);
        Y.push_back(y);

        eX.push_back( 0 );
        eY.push_back( sqrt(y) );

    }

    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kRed+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1.75);
    g->SetMarkerSize(0.5);
    g->SetMarkerColor(kOrange-3);
    g->SetLineColor(kOrange+7);

    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(0, 1024);
    g->GetXaxis()->SetNdivisions(30);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Counts");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 300);
    g->GetYaxis()->SetNdivisions(-515);

    g->Draw();
    
    C->Update();
    C->SaveAs("output/spectrum_gamas_2.png");
    C->Clear();


}
