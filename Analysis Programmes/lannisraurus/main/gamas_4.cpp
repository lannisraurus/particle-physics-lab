// Includes
#include "includes.h"

// Main Function
int main(){

    std::vector<double> X = {20.304, 436.38, 768.66, 873.29},
                        Y = {32, 662, 1173, 1333},
                        eX = {0.042, 0.15, 0.23, 0.24},
                        eY = {0, 0, 0, 0};
    



    TCanvas* C = new TCanvas("C", "Canvas", 16*150, 9*150);
    TGraphErrors* g = new TGraphErrors(X.size(), X.data(), Y.data(), eX.data(), eY.data());

    g->SetTitle("2nd calibration using Cs-137 and Co-60 peaks");
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kAzure+2);
    g->SetLineColor(kBlue+2);
    g->SetLineWidth(1);
    g->SetMarkerSize(2);

    g->GetXaxis()->SetTitle("Channel");
    g->GetXaxis()->SetLimits(0, 900);
    g->GetXaxis()->SetNdivisions(-518);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetXaxis()->SetTickLength(-0.04);
    g->GetXaxis()->SetLabelOffset(0.033);
    g->GetXaxis()->SetTitleOffset(1.3);

    g->GetYaxis()->SetTitle("Energy [keV]");
    g->GetYaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetRangeUser(0, 1400);
    g->GetYaxis()->SetNdivisions(-514);

    TF1* f = new TF1("f", "[0]*x + [1]", 0, 900);
    f->SetParameters(1.65, 0);

    f->SetLineColor(kRed);
    f->SetLineWidth(2);

    g->Fit("f");

    TPaveText* pt = new TPaveText(20, 900, 350, 1300, "user");

    pt->SetTextSize(0.04);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);

    pt->AddText(Form("Linear Fit: y=mx+b"));
    pt->AddText(Form("m = %.5f %c %.5f", f->GetParameter(0), 0xB1, f->GetParError(0)));
    pt->AddText(Form("b = %.3f %c %.3f", f->GetParameter(1), 0xB1, f->GetParError(1)));
    pt->AddText(Form("#chi^{2} = %.2f", f->GetChisquare()));
    pt->AddText(Form("Number of points = %ld", X.size() ));


    f->Draw();
    g->Draw("AP");
    pt->Draw("same");
    
    C->Update();
    C->SaveAs("output/cal_1_gamas.png");
    C->Clear();


}
