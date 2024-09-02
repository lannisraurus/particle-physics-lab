// Includes
#include "includes.h"

// Main Function
int main(){


    std::vector<double> X = {0.0, 947.7, 1809.1, 2014.7, 4465.0, 7042.0, 7989.7, 8851.1, 9056.7, 11507.0, 13521.7, 15330.8, 16278.5},
                        Y = {152.8, 143.7, 132.1, 129.2, 101.2, 78.4, 70.9, 67.2, 63.9, 50.0, 40.43, 34.98, 31.04},
                        eX,
                        eY = {3.0, 3.1, 2.9, 2.9, 2.7, 1.9, 1.9, 1.5, 1.5, 1.3, 0.98, 0.84, 0.77};

    for(auto& a: X) a = a*0.01;
    for(int i = 0; i < X.size(); i++) eX.push_back(0);

    std::cout << "X size: " << X.size() << ", Y size: " << Y.size() << ", eY size: " << eY.size() << "\n"; 

    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle("");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kGreen+2);
    g->SetLineColor(kGreen+2);
    g->SetLineWidth(1.75);

    g->GetXaxis()->SetTitle("Thickness [kg/m^2]");
    g->GetXaxis()->SetLimits(-20, 180);
    g->GetXaxis()->SetNdivisions(-520);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Intensity [Bq]");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 200);
    g->GetYaxis()->SetNdivisions(-520);

    TF1* f = new TF1("f", "[0]*TMath::Exp(-[1]*x)",0,170);

    f->SetLineColor(kBlue);
    f->SetLineWidth(2);

    f->SetParameters(152,0.01);

    g->Fit("f");

    TPaveText* pt = new TPaveText(100, 120, 180, 190, "user");

    pt->SetTextSize(0.03);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("I = A#upointexp(-#mud)"));
    pt->AddText(Form("A = %.1f %c %.1f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("#mu = (%.1f %c %.1f)#upoint10^{-3}", f->GetParameter(1)*10E3, 0xB1, f->GetParError(1)*10E3));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->AddText(Form("Number of points = %ld", X.size() ));

    
    g->Draw();
    pt->Draw("same");
    
    C->Update();
    C->SaveAs("output/CHUMBO.png");
    C->Clear();


}
